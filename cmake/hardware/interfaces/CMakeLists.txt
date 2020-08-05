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
${INTERMEDIATE_PATH}/graphics/bufferqueue/1.0/android.hardware.graphics.bufferqueue@1.0_genc++_headers/gen/android/hardware/graphics/bufferqueue/1.0/*.h
${INTERMEDIATE_PATH}/graphics/composer/2.1/android.hardware.graphics.composer@2.1_genc++_headers/gen/android/hardware/graphics/composer/2.1/*.h
${INTERMEDIATE_PATH}/graphics/composer/2.2/android.hardware.graphics.composer@2.2_genc++_headers/gen/android/hardware/graphics/composer/2.2/*.h
${INTERMEDIATE_PATH}/media/1.0/android.hardware.media@1.0_genc++_headers/gen/android/hardware/media/1.0/*.h
${INTERMEDIATE_PATH}/media/omx/1.0/android.hardware.media.omx@1.0_genc++_headers/gen/android/hardware/media/omx/1.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/configstore/utils/ConfigStoreUtils.cpp
${INTERMEDIATE_PATH}/media/omx/1.0/android.hardware.media.omx@1.0_genc++/gen/android/hardware/media/omx/1.0/OmxNodeAll.cpp
${INTERMEDIATE_PATH}/media/omx/1.0/android.hardware.media.omx@1.0_genc++/gen/android/hardware/media/omx/1.0/OmxBufferSourceAll.cpp
${INTERMEDIATE_PATH}/graphics/bufferqueue/1.0/android.hardware.graphics.bufferqueue@1.0_genc++/gen/android/hardware/graphics/bufferqueue/1.0/ProducerListenerAll.cpp
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

ADD_LIB(interfaces)
