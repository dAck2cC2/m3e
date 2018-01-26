
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cutils/stdatomic.h>
#include <cutils/properties.h>

#include "bionic_macros.h"
#include "bionic_lock.h"

#define PROPERTY_FILE  "property_contexts"

#if defined(_MSC_VER)
// MSVC apparently doesn't have C's getline
// This is a poor man's implementation of it using fgets.
// See the man page at
// http://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html
size_t getline(char** buf, size_t* bufLen, FILE* f)
{
	if (buf == nullptr || bufLen == nullptr)
	{
		errno = EINVAL;
		return -1;
	}

	if (fgets(*buf, *bufLen, f) != *buf)
		return -1;

	while (true)
	{
		const size_t amountRead = strlen(*buf);
		// If the length of the string is less than the whole buffer
		// (minus the last space for \0) or the last character is a newline,
		// we win. Done.
		if (amountRead != *bufLen - 1 || (*buf)[amountRead - 1] == '\n')
			return amountRead;

		// We didn't have enought room, expand with realloc.

		// First make sure we can.

		// If we can't take any more, give up.
		if (*bufLen == SSIZE_MAX)
		{
			errno = EOVERFLOW;
			return -1;
		}

		// If the MSB of bufLen is 1, doubling will overflow.
		const bool willOverflow = (*bufLen >> (sizeof(size_t) * 8 - 1)) == 1;
		const size_t newSize = willOverflow ? SSIZE_MAX : *bufLen * 2;

		char* newBuf = static_cast<char*>(realloc(*buf, newSize));
		if (newBuf == nullptr)
		{
			errno = ENOMEM;
			return -1;
		}
		// We succeeded in expanding.
		*buf = newBuf;
		*bufLen = newSize;
		// Keep reading where we left off
		char* const resumePoint = *buf + amountRead;
		if (fgets(resumePoint, *bufLen - amountRead, f) != resumePoint)
			return -1;
	}
}
#endif // _MSC_VER

struct prop_info;

static size_t pa_data_size;

/*
* Properties are stored in a hybrid trie/binary tree structure.
* Each property's name is delimited at '.' characters, and the tokens are put
* into a trie structure.  Siblings at each level of the trie are stored in a
* binary tree.  For instance, "ro.secure"="1" could be stored as follows:
*
* +-----+   children    +----+   children    +--------+
* |     |-------------->| ro |-------------->| secure |
* +-----+               +----+               +--------+
*                       /    \                /   |
*                 left /      \ right   left /    |  prop   +===========+
*                     v        v            v     +-------->| ro.secure |
*                  +-----+   +-----+     +-----+            +-----------+
*                  | net |   | sys |     | com |            |     1     |
*                  +-----+   +-----+     +-----+            +===========+
*/

// Represents a node in the trie.
struct prop_bt {
	uint8_t namelen;
	uint8_t reserved[3];

	// The property trie is updated only by the init process (single threaded) which provides
	// property service. And it can be read by multiple threads at the same time.
	// As the property trie is not protected by locks, we use atomic_uint_least32_t types for the
	// left, right, children "pointers" in the trie node. To make sure readers who see the
	// change of "pointers" can also notice the change of prop_bt structure contents pointed by
	// the "pointers", we always use release-consume ordering pair when accessing these "pointers".

	// prop "points" to prop_info structure if there is a propery associated with the trie node.
	// Its situation is similar to the left, right, children "pointers". So we use
	// atomic_uint_least32_t and release-consume ordering to protect it as well.

	// We should also avoid rereading these fields redundantly, since not
	// all processor implementations ensure that multiple loads from the
	// same field are carried out in the right order.
	atomic_uint_least32_t prop;

	atomic_uint_least32_t left;
	atomic_uint_least32_t right;

	atomic_uint_least32_t children;

	char name[0];

	prop_bt(const char *name, const uint8_t name_length) {
		this->namelen = name_length;
		memcpy(this->name, name, name_length);
		this->name[name_length] = '\0';
	}

private:
	DISALLOW_COPY_AND_ASSIGN(prop_bt);
};

class prop_area {
public:

	prop_area(const uint32_t magic, const uint32_t version) :
		magic_(magic), version_(version) {
		atomic_init(&serial_, 0);
		memset(reserved_, 0, sizeof(reserved_));
		// Allocate enough space for the root node.
		bytes_used_ = sizeof(prop_bt);
	}

	const prop_info *find(const char *name);
	bool add(const char *name, unsigned int namelen,
		const char *value, unsigned int valuelen);

	bool foreach(void(*propfn)(const prop_info *pi, void *cookie), void *cookie);

	atomic_uint_least32_t *serial() { return &serial_; }
	uint32_t magic() const { return magic_; }
	uint32_t version() const { return version_; }

private:
	void *allocate_obj(const size_t size, uint_least32_t *const off);
	prop_bt *new_prop_bt(const char *name, uint8_t namelen, uint_least32_t *const off);
	prop_info *new_prop_info(const char *name, uint8_t namelen,
		const char *value, uint8_t valuelen,
		uint_least32_t *const off);
	void *to_prop_obj(uint_least32_t off);
	prop_bt *to_prop_bt(atomic_uint_least32_t *off_p);
	prop_info *to_prop_info(atomic_uint_least32_t *off_p);

	prop_bt *root_node();

	prop_bt *find_prop_bt(prop_bt *const bt, const char *name,
		uint8_t namelen, bool alloc_if_needed);

	const prop_info *find_property(prop_bt *const trie, const char *name,
		uint8_t namelen, const char *value,
		uint8_t valuelen, bool alloc_if_needed);

	bool foreach_property(prop_bt *const trie,
		void(*propfn)(const prop_info *pi, void *cookie),
		void *cookie);

	uint32_t bytes_used_;
	atomic_uint_least32_t serial_;
	uint32_t magic_;
	uint32_t version_;
	uint32_t reserved_[28];
	char data_[0];

	DISALLOW_COPY_AND_ASSIGN(prop_area);
};

struct prop_info {
	atomic_uint_least32_t serial;
	char value[PROP_VALUE_MAX];
	char name[0];

	prop_info(const char *name, const uint8_t namelen, const char *value,
		const uint8_t valuelen) {
		memcpy(this->name, name, namelen);
		this->name[namelen] = '\0';
		atomic_init(&this->serial, valuelen << 24);
		memcpy(this->value, value, valuelen);
		this->value[valuelen] = '\0';
	}
private:
	DISALLOW_COPY_AND_ASSIGN(prop_info);
};

void *prop_area::allocate_obj(const size_t size, uint_least32_t *const off)
{
	const size_t aligned = BIONIC_ALIGN(size, sizeof(uint_least32_t));
	if (bytes_used_ + aligned > pa_data_size) {
		return NULL;
	}

	*off = bytes_used_;
	bytes_used_ += aligned;
	return data_ + *off;
}

prop_bt *prop_area::new_prop_bt(const char *name, uint8_t namelen, uint_least32_t *const off)
{
	uint_least32_t new_offset;
	void *const p = allocate_obj(sizeof(prop_bt) + namelen + 1, &new_offset);
	if (p != NULL) {
		prop_bt* bt = new(p) prop_bt(name, namelen);
		*off = new_offset;
		return bt;
	}

	return NULL;
}

prop_info *prop_area::new_prop_info(const char *name, uint8_t namelen,
	const char *value, uint8_t valuelen, uint_least32_t *const off)
{
	uint_least32_t new_offset;
	void* const p = allocate_obj(sizeof(prop_info) + namelen + 1, &new_offset);
	if (p != NULL) {
		prop_info* info = new(p) prop_info(name, namelen, value, valuelen);
		*off = new_offset;
		return info;
	}

	return NULL;
}

void *prop_area::to_prop_obj(uint_least32_t off)
{
	if (off > pa_data_size)
		return NULL;

	return (data_ + off);
}

inline prop_bt *prop_area::to_prop_bt(atomic_uint_least32_t* off_p) {
	uint_least32_t off = atomic_load_explicit(off_p, memory_order_consume);
	return reinterpret_cast<prop_bt*>(to_prop_obj(off));
}

inline prop_info *prop_area::to_prop_info(atomic_uint_least32_t* off_p) {
	uint_least32_t off = atomic_load_explicit(off_p, memory_order_consume);
	return reinterpret_cast<prop_info*>(to_prop_obj(off));
}

inline prop_bt *prop_area::root_node()
{
	return reinterpret_cast<prop_bt*>(to_prop_obj(0));
}

static int cmp_prop_name(const char *one, uint8_t one_len, const char *two,
	uint8_t two_len)
{
	if (one_len < two_len)
		return -1;
	else if (one_len > two_len)
		return 1;
	else
		return strncmp(one, two, one_len);
}

prop_bt *prop_area::find_prop_bt(prop_bt *const bt, const char *name,
	uint8_t namelen, bool alloc_if_needed)
{

	prop_bt* current = bt;
	while (true) {
		if (!current) {
			return NULL;
		}

		const int ret = cmp_prop_name(name, namelen, current->name, current->namelen);
		if (ret == 0) {
			return current;
		}

		if (ret < 0) {
			uint_least32_t left_offset = atomic_load_explicit(&current->left, memory_order_relaxed);
			if (left_offset != 0) {
				current = to_prop_bt(&current->left);
			}
			else {
				if (!alloc_if_needed) {
					return NULL;
				}

				uint_least32_t new_offset;
				prop_bt* new_bt = new_prop_bt(name, namelen, &new_offset);
				if (new_bt) {
					atomic_store_explicit(&current->left, new_offset, memory_order_release);
				}
				return new_bt;
			}
		}
		else {
			uint_least32_t right_offset = atomic_load_explicit(&current->right, memory_order_relaxed);
			if (right_offset != 0) {
				current = to_prop_bt(&current->right);
			}
			else {
				if (!alloc_if_needed) {
					return NULL;
				}

				uint_least32_t new_offset;
				prop_bt* new_bt = new_prop_bt(name, namelen, &new_offset);
				if (new_bt) {
					atomic_store_explicit(&current->right, new_offset, memory_order_release);
				}
				return new_bt;
			}
		}
	}
}

const prop_info *prop_area::find_property(prop_bt *const trie, const char *name,
	uint8_t namelen, const char *value, uint8_t valuelen,
	bool alloc_if_needed)
{
	if (!trie) return NULL;

	const char *remaining_name = name;
	prop_bt* current = trie;
	while (true) {
		const char *sep = strchr(remaining_name, '.');
		const bool want_subtree = (sep != NULL);
		const uint8_t substr_size = (want_subtree) ?
			sep - remaining_name : strlen(remaining_name);

		if (!substr_size) {
			return NULL;
		}

		prop_bt* root = NULL;
		uint_least32_t children_offset = atomic_load_explicit(&current->children, memory_order_relaxed);
		if (children_offset != 0) {
			root = to_prop_bt(&current->children);
		}
		else if (alloc_if_needed) {
			uint_least32_t new_offset;
			root = new_prop_bt(remaining_name, substr_size, &new_offset);
			if (root) {
				atomic_store_explicit(&current->children, new_offset, memory_order_release);
			}
		}

		if (!root) {
			return NULL;
		}

		current = find_prop_bt(root, remaining_name, substr_size, alloc_if_needed);
		if (!current) {
			return NULL;
		}

		if (!want_subtree)
			break;

		remaining_name = sep + 1;
	}

	uint_least32_t prop_offset = atomic_load_explicit(&current->prop, memory_order_relaxed);
	if (prop_offset != 0) {
		return to_prop_info(&current->prop);
	}
	else if (alloc_if_needed) {
		uint_least32_t new_offset;
		prop_info* new_info = new_prop_info(name, namelen, value, valuelen, &new_offset);
		if (new_info) {
			atomic_store_explicit(&current->prop, new_offset, memory_order_release);
		}

		return new_info;
	}
	else {
		return NULL;
	}
}

bool prop_area::foreach_property(prop_bt *const trie,
	void(*propfn)(const prop_info *pi, void *cookie), void *cookie)
{
	if (!trie)
		return false;

	uint_least32_t left_offset = atomic_load_explicit(&trie->left, memory_order_relaxed);
	if (left_offset != 0) {
		const int err = foreach_property(to_prop_bt(&trie->left), propfn, cookie);
		if (err < 0)
			return false;
	}
	uint_least32_t prop_offset = atomic_load_explicit(&trie->prop, memory_order_relaxed);
	if (prop_offset != 0) {
		prop_info *info = to_prop_info(&trie->prop);
		if (!info)
			return false;
		propfn(info, cookie);
	}
	uint_least32_t children_offset = atomic_load_explicit(&trie->children, memory_order_relaxed);
	if (children_offset != 0) {
		const int err = foreach_property(to_prop_bt(&trie->children), propfn, cookie);
		if (err < 0)
			return false;
	}
	uint_least32_t right_offset = atomic_load_explicit(&trie->right, memory_order_relaxed);
	if (right_offset != 0) {
		const int err = foreach_property(to_prop_bt(&trie->right), propfn, cookie);
		if (err < 0)
			return false;
	}

	return true;
}

const prop_info *prop_area::find(const char *name) {
	return find_property(root_node(), name, strlen(name), nullptr, 0, false);
}

bool prop_area::add(const char *name, unsigned int namelen,
	const char *value, unsigned int valuelen) {
	return find_property(root_node(), name, namelen, value, valuelen, true);
}

bool prop_area::foreach(void(*propfn)(const prop_info* pi, void* cookie), void* cookie) {
	return foreach_property(root_node(), propfn, cookie);
}


class context_node {
public:
	context_node(context_node* next, const char* context, prop_area* pa)
		: next(next), context_(strdup(context)), pa_(pa), no_access_(false) {
		lock_.init(false);
	}
	~context_node() {
		unmap();
		free(context_);
	}
	bool open(bool access_rw, bool* fsetxattr_failed);
	bool check_access_and_open();
	void reset_access();

	const char* context() const { return context_; }
	prop_area* pa() { return pa_; }

	context_node* next;

private:
	bool check_access();
	void unmap();

	Lock lock_;
	char* context_;
	prop_area* pa_;
	bool no_access_;
};

struct prefix_node {
	prefix_node(struct prefix_node* next, const char* prefix, context_node* context)
		: prefix(strdup(prefix)), prefix_len(strlen(prefix)), context(context), next(next) {
	}
	~prefix_node() {
		free(prefix);
	}
	char* prefix;
	const size_t prefix_len;
	context_node* context;
	struct prefix_node* next;
};

template <typename List, typename... Args>
static inline void list_add(List** list, Args... args) {
	*list = new List(*list, args...);
}

static void list_add_after_len(prefix_node** list, const char* prefix, context_node* context) {
	size_t prefix_len = strlen(prefix);

	auto next_list = list;

	while (*next_list) {
		if ((*next_list)->prefix_len < prefix_len || (*next_list)->prefix[0] == '*') {
			list_add(next_list, prefix, context);
			return;
		}
		next_list = &(*next_list)->next;
	}
	list_add(next_list, prefix, context);
}

template <typename List, typename Func>
static void list_foreach(List* list, Func func) {
	while (list) {
		func(list);
		list = list->next;
	}
}

template <typename List, typename Func>
static List* list_find(List* list, Func func) {
	while (list) {
		if (func(list)) {
			return list;
		}
		list = list->next;
	}
	return nullptr;
}

template <typename List>
static void list_free(List** list) {
	while (*list) {
		auto old_list = *list;
		*list = old_list->next;
		delete old_list;
	}
}

static prefix_node* prefixes = nullptr;
static context_node* contexts = nullptr;

#if 0
/*
* pthread_mutex_lock() calls into system_properties in the case of contention.
* This creates a risk of dead lock if any system_properties functions
* use pthread locks after system_property initialization.
*
* For this reason, the below three functions use a bionic Lock and static
* allocation of memory for each filename.
*/

bool context_node::open(bool access_rw, bool* fsetxattr_failed) {
	lock_.lock();
	if (pa_) {
		lock_.unlock();
		return true;
	}

	char filename[PROP_FILENAME_MAX];
	int len = __libc_format_buffer(filename, sizeof(filename), "%s/%s",
		property_filename, context_);
	if (len < 0 || len > PROP_FILENAME_MAX) {
		lock_.unlock();
		return false;
	}

	if (access_rw) {
		pa_ = map_prop_area_rw(filename, context_, fsetxattr_failed);
	}
	else {
		pa_ = map_prop_area(filename, false);
	}
	lock_.unlock();
	return pa_;
}

bool context_node::check_access_and_open() {
	if (!pa_ && !no_access_) {
		if (!check_access() || !open(false, nullptr)) {
			no_access_ = true;
		}
	}
	return pa_;
}

void context_node::reset_access() {
	if (!check_access()) {
		unmap();
		no_access_ = true;
	}
	else {
		no_access_ = false;
	}
}

bool context_node::check_access() {
	char filename[PROP_FILENAME_MAX];
	int len = __libc_format_buffer(filename, sizeof(filename), "%s/%s",
		property_filename, context_);
	if (len < 0 || len > PROP_FILENAME_MAX) {
		return false;
	}

	return access(filename, R_OK) == 0;
}

void context_node::unmap() {
	if (!pa_) {
		return;
	}

	munmap(pa_, pa_size);
	if (pa_ == __system_property_area__) {
		__system_property_area__ = nullptr;
	}
	pa_ = nullptr;
}
#endif

/*
* The below two functions are duplicated from label_support.c in libselinux.
* TODO: Find a location suitable for these functions such that both libc and
* libselinux can share a common source file.
*/

/*
* The read_spec_entries and read_spec_entry functions may be used to
* replace sscanf to read entries from spec files. The file and
* property services now use these.
*/

/* Read an entry from a spec file (e.g. file_contexts) */
static inline int read_spec_entry(char **entry, char **ptr, int *len)
{
	*entry = NULL;
	char *tmp_buf = NULL;

	while (isspace(**ptr) && **ptr != '\0')
		(*ptr)++;

	tmp_buf = *ptr;
	*len = 0;

	while (!isspace(**ptr) && **ptr != '\0') {
		(*ptr)++;
		(*len)++;
	}

	if (*len) {
#if defined(_MSC_VER)
		*entry = strdup(tmp_buf);
#else  // _MSC_VER
		*entry = strndup(tmp_buf, *len);
#endif // _MSC_VER
		if (!*entry)
			return -1;
	}

	return 0;
}

/*
* line_buf - Buffer containing the spec entries .
* num_args - The number of spec parameter entries to process.
* ...      - A 'char **spec_entry' for each parameter.
* returns  - The number of items processed.
*
* This function calls read_spec_entry() to do the actual string processing.
*/
static int read_spec_entries(char *line_buf, int num_args, ...)
{
	char **spec_entry, *buf_p;
	int len, rc, items, entry_len = 0;
	va_list ap;

	len = strlen(line_buf);
	if (line_buf[len - 1] == '\n')
		line_buf[len - 1] = '\0';
	else
		/* Handle case if line not \n terminated by bumping
		* the len for the check below (as the line is NUL
		* terminated by getline(3)) */
		len++;

	buf_p = line_buf;
	while (isspace(*buf_p))
		buf_p++;

	/* Skip comment lines and empty lines. */
	if (*buf_p == '#' || *buf_p == '\0')
		return 0;

	/* Process the spec file entries */
	va_start(ap, num_args);

	items = 0;
	while (items < num_args) {
		spec_entry = va_arg(ap, char **);

		if (len - 1 == buf_p - line_buf) {
			va_end(ap);
			return items;
		}

		rc = read_spec_entry(spec_entry, &buf_p, &entry_len);
		if (rc < 0) {
			va_end(ap);
			return rc;
		}
		if (entry_len)
			items++;
	}
	va_end(ap);
	return items;
}

static bool initialize_properties() {
	FILE* file = fopen(PROPERTY_FILE, "re");

	if (!file) {
		return false;
	}

	char* buffer = nullptr;
	size_t line_len;
	char* prop_prefix = nullptr;
	char* context = nullptr;

	while (getline(&buffer, &line_len, file) > 0) {
		int items = read_spec_entries(buffer, 2, &prop_prefix, &context);
		if (items <= 0) {
			continue;
		}
		if (items == 1) {
			free(prop_prefix);
			continue;
		}
		/*
		* init uses ctl.* properties as an IPC mechanism and does not write them
		* to a property file, therefore we do not need to create property files
		* to store them.
		*/
		if (!strncmp(prop_prefix, "ctl.", 4)) {
			free(prop_prefix);
			free(context);
			continue;
		}

		auto old_context = list_find(
			contexts, [context](context_node* l) { return !strcmp(l->context(), context); });
		if (old_context) {
			list_add_after_len(&prefixes, prop_prefix, old_context);
		}
		else {
			list_add(&contexts, context, nullptr);
			list_add_after_len(&prefixes, prop_prefix, contexts);
		}
		free(prop_prefix);
		free(context);
	}

	free(buffer);
	fclose(file);
	return true;
}
