project(INTERFACES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/interfaces)
    message( FATAL_ERROR "Please firstly execute cmake of ${M3E_SOURCE_DIR}/tool which will download the source code")
endif()

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
# generate android.hardware.cas@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/cas/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.cas@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/cas/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.cas@1.0")
endif()

file(GLOB ANDROID_HARDWARE_CAS_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/cas/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_CAS_10_SOURCES
)
source_group(android.hardware.cas@1.0 FILES ${ANDROID_HARDWARE_CAS_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_CAS_10_SOURCES})

###############################################################################
# generate android.hardware.cas.native@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/cas/native/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.cas.native@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/cas/native/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.cas.native@1.0")
endif()

file(GLOB ANDROID_HARDWARE_CAS_NATIVE_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/cas/native/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_CAS_NATIVE_10_SOURCES
)
source_group(android.hardware.cas.native@1.0 FILES ${ANDROID_HARDWARE_CAS_NATIVE_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_CAS_NATIVE_10_SOURCES})

###############################################################################
# generate android.hardware.configstore@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/configstore/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.configstore@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/configstore/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.configstore@1.0")
endif()

file(GLOB ANDROID_HARDWARE_CONFIGSTORE_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/configstore/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_CONFIGSTORE_10_SOURCES
)
source_group(android.hardware.configstore@1.0 FILES ${ANDROID_HARDWARE_CONFIGSTORE_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_CONFIGSTORE_10_SOURCES})

###############################################################################
# generate android.hardware.configstore@1.1
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/configstore/1.1)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.configstore@1.1")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/configstore/1.1)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.configstore@1.1")
endif()

file(GLOB ANDROID_HARDWARE_CONFIGSTORE_11_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/configstore/1.1/*.h
)
list(APPEND ANDROID_HARDWARE_CONFIGSTORE_11_SOURCES
)
source_group(android.hardware.configstore@1.1 FILES ${ANDROID_HARDWARE_CONFIGSTORE_11_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_CONFIGSTORE_11_SOURCES})

###############################################################################
# generate android.hardware.graphics.allocator@2.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/allocator/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.allocator@2.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/allocator/2.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.allocator@2.0")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_20_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/allocator/2.0/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_20_SOURCES
)
source_group(android.hardware.graphics.allocator@2.0 FILES ${ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_20_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_ALLOCATOR_20_SOURCES})

###############################################################################
# generate android.hardware.graphics.mapper@2.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/mapper/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.mapper@2.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/mapper/2.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.mapper@2.0")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_MAPPER_20_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/mapper/2.0/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_MAPPER_20_SOURCES
)
source_group(android.hardware.graphics.mapper@2.0 FILES ${ANDROID_HARDWARE_GRAPHICS_MAPPER_20_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_MAPPER_20_SOURCES})

###############################################################################
# generate android.hardware.graphics.mapper@2.1
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/mapper/2.1)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.mapper@2.1")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/mapper/2.1)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.mapper@2.1")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_MAPPER_21_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/mapper/2.1/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_MAPPER_21_SOURCES
)
source_group(android.hardware.graphics.mapper@2.1 FILES ${ANDROID_HARDWARE_GRAPHICS_MAPPER_21_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_MAPPER_21_SOURCES})

###############################################################################
# generate android.hardware.graphics.common@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/common/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.common@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/common/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.common@1.0")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_COMMON_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/common/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_COMMON_10_SOURCES
)
source_group(android.hardware.graphics.common@1.0 FILES ${ANDROID_HARDWARE_GRAPHICS_COMMON_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_COMMON_10_SOURCES})

###############################################################################
# generate android.hardware.graphics.common@1.1
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/common/1.1)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.common@1.1")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/common/1.1)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.common@1.1")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_COMMON_11_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/common/1.1/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_COMMON_11_SOURCES
)
source_group(android.hardware.graphics.common@1.1 FILES ${ANDROID_HARDWARE_GRAPHICS_COMMON_11_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_COMMON_11_SOURCES})

###############################################################################
# generate android.hardware.graphics.composer@2.1
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/composer/2.1)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.composer@2.1")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/composer/2.1)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.composer@2.1")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_COMPOSER_21_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/composer/2.1/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_COMPOSER_21_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/composer/2.1/ComposerCallbackAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/composer/2.1/ComposerAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/composer/2.1/ComposerClientAll.cpp
)
source_group(android.hardware.graphics.composer@2.1 FILES ${ANDROID_HARDWARE_GRAPHICS_COMPOSER_21_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_COMPOSER_21_SOURCES})

###############################################################################
# generate android.hardware.graphics.composer@2.2
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/composer/2.2)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.composer@2.2")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/composer/2.2)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.composer@2.2")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_COMPOSER_22_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/composer/2.2/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_COMPOSER_22_SOURCES
)
source_group(android.hardware.graphics.composer@2.2 FILES ${ANDROID_HARDWARE_GRAPHICS_COMPOSER_22_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_COMPOSER_22_SOURCES})

###############################################################################
# generate android.hardware.audio@2.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio@2.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio@2.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_20_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/2.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_20_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/2.0/PrimaryDeviceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/2.0/DeviceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/2.0/DevicesFactoryAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/2.0/StreamOutCallbackAll.cpp
)
source_group(android.hardware.audio@2.0 FILES ${ANDROID_HARDWARE_AUDIO_20_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_20_SOURCES})

###############################################################################
# generate android.hardware.audio@4.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/4.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio@4.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/4.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio@4.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_40_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/4.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_40_SOURCES
)
source_group(android.hardware.audio@4.0 FILES ${ANDROID_HARDWARE_AUDIO_40_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_40_SOURCES})

###############################################################################
# generate android.hardware.audio.effect@2.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/effect/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio.effect@2.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/effect/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio.effect@2.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_EFFECT_20_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/effect/2.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_EFFECT_20_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/effect/2.0/EffectsFactoryAll.cpp
)
source_group(android.hardware.audio.effect@2.0 FILES ${ANDROID_HARDWARE_AUDIO_EFFECT_20_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_EFFECT_20_SOURCES})

###############################################################################
# generate android.hardware.audio.effect@4.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/effect/4.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio.effect@4.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/effect/4.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio.effect@4.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_EFFECT_40_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/effect/4.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_EFFECT_40_SOURCES
)
source_group(android.hardware.audio.effect@2.0 FILES ${ANDROID_HARDWARE_AUDIO_EFFECT_40_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_EFFECT_40_SOURCES})

###############################################################################
# generate android.hardware.audio.common@2.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/common/2.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio.common@2.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/common/2.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio.common@2.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_COMMON_20_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/common/2.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_COMMON_20_SOURCES
)
source_group(android.hardware.audio.common@2.0 FILES ${ANDROID_HARDWARE_AUDIO_COMMON_20_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_COMMON_20_SOURCES})

###############################################################################
# generate android.hardware.audio.common@4.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/common/4.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.audio.common@4.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/audio/common/4.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.audio.common@4.0")
endif()

file(GLOB ANDROID_HARDWARE_AUDIO_COMMON_40_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/audio/common/4.0/*.h
)
list(APPEND ANDROID_HARDWARE_AUDIO_COMMON_40_SOURCES
)
source_group(android.hardware.audio.common@4.0 FILES ${ANDROID_HARDWARE_AUDIO_COMMON_40_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_AUDIO_COMMON_40_SOURCES})

###############################################################################
# generate android.hardware.media@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.media@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.media@1.0")
endif()

file(GLOB ANDROID_HARDWARE_MEDIA_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_MEDIA_10_SOURCES
)
source_group(android.hardware.media@1.0 FILES ${ANDROID_HARDWARE_MEDIA_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_MEDIA_10_SOURCES})

###############################################################################
# generate android.hardware.media.omx@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/omx/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.media.omx@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.media.omx@1.0")
endif()

file(GLOB ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/omx/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxNodeAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxBufferSourceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxStoreAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxAll.cpp
)
source_group(android.hardware.media.omx@1.0 FILES ${ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES})

###############################################################################
# generate android.hardware.media.bufferpool@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/bufferpool/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.media.bufferpool@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/bufferpool/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.media.bufferpool@1.0")
endif()

file(GLOB ANDROID_HARDWARE_MEDIA_BUFFERPOOL_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/bufferpool/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_MEDIA_BUFFERPOOL_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/bufferpool/1.0/ClientManagerAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/bufferpool/1.0/AccessorAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/bufferpool/1.0/ConnectionAll.cpp
)
source_group(android.hardware.media.bufferpool@1.0 FILES ${ANDROID_HARDWARE_MEDIA_BUFFERPOOL_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_MEDIA_BUFFERPOOL_10_SOURCES})

###############################################################################
# generate android.hardware.graphics.bufferqueue@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/bufferqueue/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.bufferqueue@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/bufferqueue/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.bufferqueue@1.0")
endif()

file(GLOB ANDROID_HARDWARE_GRAPHICS_BUFFERQUEUE_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/graphics/bufferqueue/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_GRAPHICS_BUFFERQUEUE_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/bufferqueue/1.0/GraphicBufferProducerAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/bufferqueue/1.0/ProducerListenerAll.cpp
)
source_group(android.hardware.graphics.bufferqueue@1.0 FILES ${ANDROID_HARDWARE_GRAPHICS_BUFFERQUEUE_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_GRAPHICS_BUFFERQUEUE_10_SOURCES})

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


ADD_LIB(interfaces)
