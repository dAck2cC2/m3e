
#ifndef _DEBUGGERD_TEST_SYS_SYSTEM_PROPERTIES_H
#define _DEBUGGERD_TEST_SYS_SYSTEM_PROPERTIES_H

// This is just enough to get the property code to compile on
// the host.

#define PROP_NAME_MAX   PROPERTY_KEY_MAX
#define PROP_VALUE_MAX  PROPERTY_VALUE_MAX

#ifdef __cplusplus
extern "C" {
#endif

struct prop_info;
    
int __system_property_set(const char *key, const char *value);
int __system_property_get(const char *key, char *value);
int __system_property_read(const struct prop_info* info, char* name, char* value);
int __system_property_foreach(void (*callback)(const struct prop_info* pi, void* cookie), void* cookie);
    
#ifdef __cplusplus
}
#endif

#endif // _DEBUGGERD_TEST_SYS_SYSTEM_PROPERTIES_H
