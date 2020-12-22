
project(BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(${PROJECT_NAME}_DEPLIB
utils
log
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

OPTION( BINDER_ENABLE_LOCAL
  "Set to ON to enable local binder implementation"
  ON
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/binder/*.h
${HEADER_PATH}/private/binder/*.h
${HEADER_PATH}/binder/local/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/ActivityManager.cpp 
${SOURCE_PATH}/AppOpsManager.cpp 
${SOURCE_PATH}/Binder.cpp 
${SOURCE_PATH}/BpBinder.cpp 
${SOURCE_PATH}/BufferedTextOutput.cpp 
${SOURCE_PATH}/Debug.cpp 
${SOURCE_PATH}/IActivityManager.cpp 
${SOURCE_PATH}/IAppOpsCallback.cpp 
${SOURCE_PATH}/IAppOpsService.cpp 
${SOURCE_PATH}/IBatteryStats.cpp 
${SOURCE_PATH}/IInterface.cpp 
${SOURCE_PATH}/IMediaResourceMonitor.cpp 
#{SOURCE_PATH}/IMemory.cpp 
${SOURCE_PATH}/IPCThreadState.cpp 
${SOURCE_PATH}/IPermissionController.cpp 
#${SOURCE_PATH}/IProcessInfoService.cpp 
${SOURCE_PATH}/IResultReceiver.cpp 
${SOURCE_PATH}/IServiceManager.cpp 
${SOURCE_PATH}/IShellCallback.cpp 
${SOURCE_PATH}/IUidObserver.cpp 
${SOURCE_PATH}/MemoryBase.cpp 
${SOURCE_PATH}/MemoryDealer.cpp 
#${SOURCE_PATH}/MemoryHeapBase.cpp 
${SOURCE_PATH}/Parcel.cpp 
${SOURCE_PATH}/ParcelFileDescriptor.cpp
${SOURCE_PATH}/PermissionCache.cpp 
${SOURCE_PATH}/PermissionController.cpp 
${SOURCE_PATH}/PersistableBundle.cpp 
#${SOURCE_PATH}/ProcessInfoService.cpp 
#${SOURCE_PATH}/ProcessState.cpp 
${SOURCE_PATH}/Static.cpp 
${SOURCE_PATH}/Status.cpp 
${SOURCE_PATH}/TextOutput.cpp 
#${SOURCE_PATH}/IpPrefix.cpp 
${SOURCE_PATH}/Value.cpp 
)

if (BINDER_ENABLE_LOCAL)
    add_definitions(-DBINDER_LOCAL=1)
    file(GLOB BINDER_LOCAL_SRC ${SOURCE_PATH}/local/*.cpp)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${BINDER_LOCAL_SRC})
endif ()

# target files
ADD_SHARED_LIB(binder)

#set(ENABLE_TEST true)
if(ENABLE_TEST)
    add_subdirectory(test)
endif()
