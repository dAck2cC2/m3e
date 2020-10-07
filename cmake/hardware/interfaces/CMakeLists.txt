project(INTERFACES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/interfaces)
    message( FATAL_ERROR "Please firstly execute cmake of ${M3E_SOURCE_DIR}/tool which will download the source code")
endif()

include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
hidl
)

###############################################################################
# define
if(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS}) 
elseif(MSVC)
    add_definitions(-DNOMINMAX=1)
endif()

set( HEADER_PATH ${HIDL_ROOT_PATH}/hardware/interfaces/ )
set( SOURCE_PATH ${HIDL_ROOT_PATH}/hardware/interfaces/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/configstore/utils/include/configstore/*.h
${HEADER_PATH}/audio/common/all-versions/default/include/*.h
${HEADER_PATH}/audio/common/all-versions/util/include/*.h
${HEADER_PATH}/audio/common/2.0/default/*.h
${HEADER_PATH}/audio/common/4.0/default/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/configstore/utils/ConfigStoreUtils.cpp
${SOURCE_PATH}/audio/common/2.0/default/HidlUtils.cpp
)

###############################################################################
# generate hidl interfaces
if(MSVC)
    add_definitions(-DEXPORT_HARDWARE=__declspec\(dllexport\))
endif()

set(HIDL_MODULES
android.hardware.cas@1.0
android.hardware.cas.native@1.0
android.hardware.configstore@1.0
android.hardware.configstore@1.1
android.hardware.graphics.allocator@2.0
android.hardware.graphics.mapper@2.0
android.hardware.graphics.mapper@2.1
android.hardware.graphics.common@1.0
android.hardware.graphics.common@1.1
android.hardware.graphics.composer@2.1
android.hardware.graphics.composer@2.2
android.hardware.audio@2.0
android.hardware.audio@4.0
android.hardware.audio.effect@2.0
android.hardware.audio.effect@4.0
android.hardware.audio.common@2.0
android.hardware.audio.common@4.0
android.hardware.media@1.0
android.hardware.media.omx@1.0
android.hardware.media.bufferpool@1.0
android.hardware.graphics.bufferqueue@1.0
)

foreach(module ${HIDL_MODULES})
    ADD_HIDL_SOURCE(${module})
endforeach()

###############################################################################
# generate hardware.google.media.c2@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/hardware/google/media/c2/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0")
endif()

file(GLOB HARDWARE_GOOGLE_MEDIA_C2_10_SOURCES
${TMP_PATH}/${HIDL_HEADER_PATH}/hardware/google/media/c2/1.0/*.h
)
list(APPEND HARDWARE_GOOGLE_MEDIA_C2_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/ComponentAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/ComponentStoreAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/ComponentInterfaceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/ComponentListenerAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/ConfigurableAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/InputSurfaceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0/InputSurfaceConnectionAll.cpp
)
source_group(hardware.google.media.c2@1.0 FILES ${HARDWARE_GOOGLE_MEDIA_C2_10_SOURCES})

if (NOT MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HARDWARE_GOOGLE_MEDIA_C2_10_SOURCES})
endif()

#add_custom_command(
#    OUTPUT "${HARDWARE_GOOGLE_MEDIA_C2_SOURCES}"
#    COMMAND "${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headres -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0"
#    COMMAND "${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0"
#    DEPENDS "${BIN_HIDL_GEN}" 
#    VERBATIM
#)

###############################################################################
# target files
set(LIB_TYPE SHARED)
ADD_LIB(interfaces)
