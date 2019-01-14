
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#include <cutils/stdatomic.h>
#else
#include <stdatomic.h>
#endif

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include "sys/_system_properties.h"
#include "sys/bionic_macros.h"
#include "sys/bionic_lock.h"

#define PROPERTY_SIZE  (64)
#define PROPERTY_FILE  "property_contexts"

#define SERIAL_DIRTY(serial) ((serial)&1)
#define SERIAL_VALUE_LEN(serial) ((serial) >> 24)

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
};

static prop_bt* prop_bt_new(void* p, const char *name, const uint8_t name_length) {
    prop_bt* thiz = reinterpret_cast<prop_bt*>(p);
    thiz->namelen = name_length;
    memcpy(thiz->name, name, name_length);
    thiz->name[name_length] = '\0';
    return thiz;
};

struct prop_info {
    atomic_uint_least32_t serial;
    char value[PROP_VALUE_MAX];
    char name[0];
};

static prop_info* prop_info_new(void * p, const char *name, const uint8_t namelen, const char *value,
                                const uint8_t valuelen) {
    prop_info* thiz = reinterpret_cast<prop_info*>(p);
    memcpy(thiz->name, name, namelen);
    thiz->name[namelen] = '\0';
    atomic_init(&thiz->serial, valuelen << 24);
    memcpy(thiz->value, value, valuelen);
    thiz->value[valuelen] = '\0';
    
    return thiz;
};

static const size_t pa_data_size = BIONIC_ALIGN(sizeof(prop_info) * PROPERTY_SIZE, sizeof(uint_least32_t));

class prop_area {
public:
	prop_area(const uint32_t magic, const uint32_t version) :
		magic_(magic), version_(version) {
		atomic_init(&serial_, 0);
		memset(reserved_, 0, sizeof(reserved_));
		// Allocate enough space for the root node.
		bytes_used_ = sizeof(prop_bt);
        data_ = new char[pa_data_size];
        memset(data_, 0x00, pa_data_size);
	}
    
    ~prop_area() {
        delete [] data_;
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

    prop_info *find_property(prop_bt *const trie, const char *name,
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
	char* data_;

	DISALLOW_COPY_AND_ASSIGN(prop_area);
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
		prop_bt* bt = prop_bt_new(p, name, namelen);
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
		prop_info* info = prop_info_new(p, name, namelen, value, valuelen);
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

prop_info *prop_area::find_property(prop_bt *const trie, const char *name,
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
    prop_info * info = find_property(root_node(), name, namelen, value, valuelen, true);
    if (info) {
        const int ret = cmp_prop_name(value, valuelen, info->value, strlen(info->value));
        if (ret != 0) {
            memcpy(info->value, value, valuelen);
            info->value[valuelen] = '\0';
        }
        return true;
    } else {
        return false;
    }
}

bool prop_area::foreach(void(*propfn)(const prop_info* pi, void* cookie), void* cookie) {
	return foreach_property(root_node(), propfn, cookie);
}

static const char* EMPTY_PROPERTY = "";

static BionicLock _lock;
static prop_area  _property(sizeof(prop_bt), sizeof(prop_info));

int __system_property_set(const char *key, const char *value)
{
    if (!key) {
        return -1;
    }
    
    _lock.lock();
    
    bool result = false;
    if (value) {
        if (strlen(value) < PROP_VALUE_MAX) {
            result = _property.add(key, strlen(key), value, strlen(value));
        }
    } else {
        result = _property.add(key, strlen(key), EMPTY_PROPERTY, strlen(EMPTY_PROPERTY));
    }
    
    _lock.unlock();
    
    return (result ? 0 : -2);
}

int __system_property_get(const char *key, char *value)
{
    if (!key || !value) {
        return 0;
    }
    
    _lock.lock();
    
    int len = 0;
    const prop_info* info = _property.find(key);
    if (info) {
        strncpy(value, info->value, PROP_VALUE_MAX);
        len = strlen(value);
    }
    
    _lock.unlock();
    
    return len;
}

// The C11 standard doesn't allow atomic loads from const fields,
// though C++11 does.  Fudge it until standards get straightened out.
static inline uint_least32_t load_const_atomic(const atomic_uint_least32_t* s, memory_order mo) {
	atomic_uint_least32_t* non_const_s = const_cast<atomic_uint_least32_t*>(s);
	return atomic_load_explicit(non_const_s, mo);
}

int __system_property_read(const prop_info* info, char* name, char* value)
{
    if (!info || !name || !value) {
        return -1;
    }
    
    _lock.lock();
    
    strncpy(name,  info->name,  PROP_NAME_MAX);
    strncpy(value, info->value, PROP_VALUE_MAX);
    
    _lock.unlock();

    return 0;
}

int __system_property_foreach(void (*callback)(const struct prop_info* pi, void* cookie), void* cookie)
{
    
    if (!callback || !cookie) {
        return -1;
    }
    
    _lock.lock();
    
    bool result = _property.foreach(callback, cookie);
    
    _lock.unlock();
    
    return (result ? 0 : -2);
}

unsigned int __system_property_area_serial()
{
	return *(_property.serial());
}

unsigned int __system_property_serial(const struct prop_info* info)
{
	if (!info) {
		return 0;
	}

	_lock.lock();

	unsigned int serial = info->serial;

	_lock.unlock();

	return (serial);
}

const struct prop_info* __system_property_find(const char *key)
{
	if (!key) {
		return NULL;
	}

	_lock.lock();
	
	const prop_info* info = _property.find(key);

	_lock.unlock();

	return (prop_info*)(info);
}

void __system_property_read_callback(const prop_info* pi,
	void(*callback)(void* cookie,
		const char* name,
		const char* value,
		uint32_t serial),
	void* cookie) {
	while (true) {
		uint32_t serial = __system_property_serial(pi);  // acquire semantics
		size_t len = SERIAL_VALUE_LEN(serial);
		char* value_buf = new char[len + 1];

		memcpy(value_buf, pi->value, len);
		value_buf[len] = '\0';

		// TODO: see todo in __system_property_read function
		atomic_thread_fence(memory_order_acquire);
		if (serial == load_const_atomic(&(pi->serial), memory_order_relaxed)) {
			callback(cookie, pi->name, value_buf, serial);
			delete[] value_buf;
			return;
		}
	}
}
