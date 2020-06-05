
#include "libgen.h"

#if defined _WIN32 || defined __WIN32__ || defined __EMX__ || defined __DJGPP__
/* Win32, OS/2, DOS */
# define HAS_DEVICE(P) \
((((P)[0] >= 'A' && (P)[0] <= 'Z') || ((P)[0] >= 'a' && (P)[0] <= 'z')) \
&& (P)[1] == ':')
# define FILESYSTEM_PREFIX_LEN(P) (HAS_DEVICE (P) ? 2 : 0)
# define ISSLASH(C) ((C) == '/' || (C) == '\\')
# define SLASH '\\'
#endif

#ifndef FILESYSTEM_PREFIX_LEN
# define FILESYSTEM_PREFIX_LEN(Filename) 0
#endif

#ifndef ISSLASH
# define ISSLASH(C) ((C) == '/')
#endif

#ifndef NULL
# define NULL ((void*)0)
#endif

char* strrchr64(char* source, int c)
{
	if (!source) return NULL;

	char* last_find = NULL;

	// move to end
	while (*source) {
		if (*source == c) {
			last_find = source;
		}
		source++;
	}

	return last_find;
}

char *
basename(char *name)
{
	char const *base = name += FILESYSTEM_PREFIX_LEN(name);
	int all_slashes = 1;
	char const *p;

	if (ISSLASH(name[strlen(name) - 1])) {
		name[strlen(name) - 1] = '\0';
	}

	for (p = name; *p; p++)
	{
		if (ISSLASH(*p) /* && (*(p+1)) */ )
			base = p + 1;
		else
			all_slashes = 0;
	}

	/* If NAME is all slashes, arrange to return `/'. */
	if (*base == '\0' && ISSLASH(*name) && all_slashes)
		--base;

	/* Make sure the last byte is not a slash. */
	//assert(all_slashes || !ISSLASH(*(p - 1)));

	return (char *)base;
}

char *
dirname(char *path)
{
	static const char dot[] = ".";
	char *last_slash = NULL;
_FIND:
	/* Find last '/'.  */
	last_slash = path != NULL ? strrchr64(path, SLASH) : NULL;

	if (last_slash == path) {
		/* The last slash is the first character in the string.  We have to
		   return "/".  */
		++last_slash;
	}
	else if (last_slash != NULL && last_slash[1] == '\0') {
		/* The '/' is the last character, we have to look further.  */
		/* last_slash = memchr(path, SLASH, last_slash - path); */
		last_slash[0] = '\0';
		goto _FIND;
	}

	if (last_slash != NULL)
		/* Terminate the path.  */
		last_slash[0] = '\0';
	else
		/* This assignment is ill-designed but the XPG specs require to
		   return a string containing "." in any case no directory part is
		   found and so a static and constant string is required.  */
		path = (char *)dot;

	return path;
}
