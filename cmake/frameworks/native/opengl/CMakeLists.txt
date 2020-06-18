
if (ENABLE_DESKTOP_GL)
    add_subdirectory(desktop)
elseif (ENABLE_ANDROID_GL)
    add_subdirectory(android)
endif()

#set(ENABLE_TEST true)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
