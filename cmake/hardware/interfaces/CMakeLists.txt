project(INTERFACES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
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

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )
set( INTERMEDIATE_PATH ${M3E_SOURCE_DIR}/src/intermediate/hardware/interfaces/ )


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/configstore/utils/include/configstore/*.h
${INTERMEDIATE_PATH}/cas/1.0/android.hardware.cas@1.0_genc++_headers/gen/android/hardware/cas/1.0/*.h
${INTERMEDIATE_PATH}/cas/native/1.0/android.hardware.cas.native@1.0_genc++_headers/gen/android/hardware/cas/native/1.0/*.h
${INTERMEDIATE_PATH}/configstore/1.0/android.hardware.configstore@1.0_genc++_headers/gen/android/hardware/configstore/1.0/*.h
${INTERMEDIATE_PATH}/configstore/1.1/android.hardware.configstore@1.1_genc++_headers/gen/android/hardware/configstore/1.1/*.h
${INTERMEDIATE_PATH}/graphics/allocator/2.0/android.hardware.graphics.allocator@2.0_genc++_headers/gen/android/hardware/graphics/allocator/2.0/*.h
${INTERMEDIATE_PATH}/graphics/mapper/2.0/android.hardware.graphics.mapper@2.0_genc++_headers/gen/android/hardware/graphics/mapper/2.0/*.h
${INTERMEDIATE_PATH}/graphics/mapper/2.1/android.hardware.graphics.mapper@2.1_genc++_headers/gen/android/hardware/graphics/mapper/2.1/*.h
${INTERMEDIATE_PATH}/graphics/common/1.0/android.hardware.graphics.common@1.0_genc++_headers/gen/android/hardware/graphics/common/1.0/*.h
${INTERMEDIATE_PATH}/graphics/common/1.1/android.hardware.graphics.common@1.1_genc++_headers/gen/android/hardware/graphics/common/1.1/*.h
${INTERMEDIATE_PATH}/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++_headers/gen/android/hardware/graphics/composer/2.1/*.h
${INTERMEDIATE_PATH}/graphics/composer/2.2/android.hardware.graphics.composer@2.2_genc++_headers/gen/android/hardware/graphics/composer/2.2/*.h
${INTERMEDIATE_PATH}/media/1.0/android.hardware.media@1.0_genc++_headers/gen/android/hardware/media/1.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/configstore/utils/ConfigStoreUtils.cpp

${INTERMEDIATE_PATH}/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++/gen/android/hardware/graphics/composer/2.1/ComposerCallbackAll.cpp
${INTERMEDIATE_PATH}/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++/gen/android/hardware/graphics/composer/2.1/ComposerAll.cpp
${INTERMEDIATE_PATH}/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++/gen/android/hardware/graphics/composer/2.1/ComposerClientAll.cpp

${SOURCE_PATH}/audio/common/2.0/default/HidlUtils.cpp
${INTERMEDIATE_PATH}/audio/2.0/android.hardware.audio@2.0_genc++/gen/android/hardware/audio/2.0/PrimaryDeviceAll.cpp
${INTERMEDIATE_PATH}/audio/2.0/android.hardware.audio@2.0_genc++/gen/android/hardware/audio/2.0/DeviceAll.cpp
${INTERMEDIATE_PATH}/audio/2.0/android.hardware.audio@2.0_genc++/gen/android/hardware/audio/2.0/DevicesFactoryAll.cpp
${INTERMEDIATE_PATH}/audio/2.0/android.hardware.audio@2.0_genc++/gen/android/hardware/audio/2.0/StreamOutCallbackAll.cpp
${INTERMEDIATE_PATH}/audio/effect/2.0/android.hardware.audio.effect@2.0_genc++/gen/android/hardware/audio/effect/2.0/EffectsFactoryAll.cpp
)

###############################################################################
# generate intermediate path
if(NOT EXISTS ${TMP_PATH})
    exec_program("mkdir ${TMP_PATH}")
endif()
if(NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH})
    exec_program("mkdir ${HIDL_HEADER_PATH}" ${TMP_PATH})
endif()
if(NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH})
    exec_program("mkdir ${HIDL_SOURCE_PATH}" ${TMP_PATH})
endif()

###############################################################################
# generate android.hardware.media.omx@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/omx/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.media.omx@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.media.omx@1.0")
endif()

file(GLOB ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/omx/1.0/*.h
)
list(APPEND ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxNodeAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxBufferSourceAll.cpp
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/omx/1.0/OmxStoreAll.cpp
)
source_group(android.hardware.media.omx@1.0 FILES ${ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HARDWARE_MEDIA_OMX_10_SOURCES})

###############################################################################
# generate android.hardware.media.bufferpool@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hardware/media/bufferpool/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.media.bufferpool@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/media/bufferpool/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.media.bufferpool@1.0")
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
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hardware.graphics.bufferqueue@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hardware/graphics/bufferqueue/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hardware.graphics.bufferqueue@1.0")
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
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/hardware/google/media/c2/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0")
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
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HARDWARE_GOOGLE_MEDIA_C2_10_SOURCES})

#add_custom_command(
#    OUTPUT "${HARDWARE_GOOGLE_MEDIA_C2_SOURCES}"
#    COMMAND "${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headres -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0"
#    COMMAND "${BIN_HIDL_GEN} -p ${M3E_SOURCE_DIR}/src -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources -r hardware.google:hardware/google/interfaces hardware.google.media.c2@1.0"
#    DEPENDS "${BIN_HIDL_GEN}" 
#    VERBATIM
#)


ADD_LIB(interfaces)
