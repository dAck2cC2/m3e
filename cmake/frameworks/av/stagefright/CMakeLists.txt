
project(STAGEFRIGHT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaplayerservice/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/xmlparser/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonivox/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/vpx/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/boringssl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
binder
audioclient
media
stagefright_foundation
drmframework
)

# define
if(APPLE OR CYGWIN)
    #add_definitions(-DO_LARGEFILE=0)
    #add_definitions(-Dlseek64=lseek)
    add_definitions(-Wno-enum-compare)
endif()

if(CYGWIN)
    add_definitions(-D_GNU_SOURCE)
elseif(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-Dstrncasecmp=strncmp)
    add_definitions(-Dstrcasecmp=strcmp)
    add_definitions(-Dlstat=_stat)
    add_definitions(-Dstat=_stat)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

# include files
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/openmax)
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/netd/include)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/ )

# include files
include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

###############################################################################
# libstagefright_esds
set(${PROJECT_NAME}_HEADER_FILES )
set(${PROJECT_NAME}_SOURCE_FILES )

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/ESDS.cpp
)
ADD_LIB(stagefright_esds)

###############################################################################
# libstagefright_metadatautils
set(${PROJECT_NAME}_HEADER_FILES )
set(${PROJECT_NAME}_SOURCE_FILES )

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/MetaDataUtils.cpp
)
ADD_LIB(stagefright_metadatautils)

###############################################################################
# libstagefright_codecbase
set(${PROJECT_NAME}_HEADER_FILES )
set(${PROJECT_NAME}_SOURCE_FILES )

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/CodecBase.cpp
${SOURCE_PATH}/FrameRenderTracker.cpp
${SOURCE_PATH}/MediaCodecListWriter.cpp
)
ADD_LIB(stagefright_codecbase)

###############################################################################
# libstagefright
set(${PROJECT_NAME}_HEADER_FILES )
set(${PROJECT_NAME}_SOURCE_FILES )

file(GLOB STAGEFRIGHT_HEADER_FILES 
${HEADER_PATH}/media/stagefright/*.h 
${HEADER_PATH}/*.h 
${SOURCE_PATH}/*.h 
)
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/ACodec.cpp
${SOURCE_PATH}/ACodecBufferChannel.cpp
${SOURCE_PATH}/AACWriter.cpp
${SOURCE_PATH}/AMRWriter.cpp
${SOURCE_PATH}/AudioPlayer.cpp
${SOURCE_PATH}/AudioPresentationInfo.cpp
${SOURCE_PATH}/AudioSource.cpp
${SOURCE_PATH}/BufferImpl.cpp
${SOURCE_PATH}/CallbackDataSource.cpp
${SOURCE_PATH}/CallbackMediaSource.cpp
#${SOURCE_PATH}/CameraSource.cpp
#${SOURCE_PATH}/CameraSourceTimeLapse.cpp
${SOURCE_PATH}/DataConverter.cpp
${SOURCE_PATH}/DataSourceFactory.cpp
${SOURCE_PATH}/DataURISource.cpp
${SOURCE_PATH}/FileSource.cpp
${SOURCE_PATH}/FrameDecoder.cpp
${SOURCE_PATH}/HTTPBase.cpp
${SOURCE_PATH}/HevcUtils.cpp
${SOURCE_PATH}/InterfaceUtils.cpp
${SOURCE_PATH}/JPEGSource.cpp
${SOURCE_PATH}/MPEG2TSWriter.cpp
${SOURCE_PATH}/MPEG4Writer.cpp
${SOURCE_PATH}/MediaAdapter.cpp
${SOURCE_PATH}/MediaClock.cpp
${SOURCE_PATH}/MediaCodec.cpp
${SOURCE_PATH}/MediaCodecList.cpp
${SOURCE_PATH}/MediaCodecListOverrides.cpp
${SOURCE_PATH}/MediaCodecSource.cpp
${SOURCE_PATH}/MediaExtractorFactory.cpp
${SOURCE_PATH}/MediaSync.cpp
${SOURCE_PATH}/http/MediaHTTP.cpp
${SOURCE_PATH}/MediaMuxer.cpp
${SOURCE_PATH}/NuCachedSource2.cpp
${SOURCE_PATH}/NuMediaExtractor.cpp
${SOURCE_PATH}/OMXClient.cpp
${SOURCE_PATH}/OmxInfoBuilder.cpp
${SOURCE_PATH}/RemoteMediaExtractor.cpp
${SOURCE_PATH}/RemoteMediaSource.cpp
${SOURCE_PATH}/SimpleDecodingSource.cpp
${SOURCE_PATH}/SkipCutBuffer.cpp
${SOURCE_PATH}/StagefrightMediaScanner.cpp
${SOURCE_PATH}/StagefrightMetadataRetriever.cpp
${SOURCE_PATH}/StagefrightPluginLoader.cpp
${SOURCE_PATH}/SurfaceUtils.cpp
${SOURCE_PATH}/Utils.cpp
${SOURCE_PATH}/ThrottledSource.cpp
${SOURCE_PATH}/VideoFrameScheduler.cpp
)
list(APPEND STAGEFRIGHT_DEPLIB
expat
stagefright_esds
stagefright_metadatautils
stagefright_codecbase
stagefright_mediafilter
stagefright_omx
stagefright_color_conversion
stagefright_id3
stagefright_mpeg2support
stagefright_webm
FLAC 
vorbisidec
#stagefright_matroska
webm
mediametrics
ziparchive
mediaextractor
#interfaces
hidl
)
set(LIB_NAME stagefright)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${STAGEFRIGHT_SOURCE_FILES} ${STAGEFRIGHT_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory 
$<TARGET_FILE_DIR:${LIB_NAME}>/etc/
)

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/data/ $<TARGET_FILE_DIR:${LIB_NAME}>/etc/
)

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${M3E_SOURCE_DIR}/src/device/media_codecs.xml $<TARGET_FILE_DIR:${LIB_NAME}>/etc/
) 

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${M3E_SOURCE_DIR}/src/device/media_codecs_performance.xml $<TARGET_FILE_DIR:${LIB_NAME}>/etc/
) 


# codec selector
if(ENABLE_AV_CODEC)
    #message(STATUS "ENABLE_AV_CODEC:${ENABLE_AV_CODEC}")

    include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/external/flac/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/external/tremolo/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/foundation/include/media/stagefright)
    include_directories(AFTER ${SOURCE_PATH}/mpeg2ts) 
    if(APPLE OR MSVC)
        include_directories(AFTER ${GENERIC_PATH}) 
    endif()


    list(APPEND STAGEFRIGHT_SOURCE_FILES 
    ${SOURCE_PATH}/MediaCodecSource.cpp  
    ${SOURCE_PATH}/SimpleDecodingSource.cpp
    ${SOURCE_PATH}/MediaCodecListOverrides.cpp
    ${SOURCE_PATH}/MediaCodecList.cpp
    ${SOURCE_PATH}/CodecBase.cpp
    ${SOURCE_PATH}/MediaCodec.cpp
    ${SOURCE_PATH}/SurfaceUtils.cpp
    ${SOURCE_PATH}/ACodec.cpp
    ${SOURCE_PATH}/DataConverter.cpp
    ${SOURCE_PATH}/OMXClient.cpp
    ${SOURCE_PATH}/SkipCutBuffer.cpp
    ${SOURCE_PATH}/FrameRenderTracker.cpp
    ${SOURCE_PATH}/AMRWriter.cpp
    ${SOURCE_PATH}/NuMediaExtractor.cpp
    ${SOURCE_PATH}/AMRExtractor.cpp 
    ${SOURCE_PATH}/MP3Extractor.cpp
    ${SOURCE_PATH}/VBRISeeker.cpp
    ${SOURCE_PATH}/XINGSeeker.cpp
    ${SOURCE_PATH}/MPEG4Extractor.cpp
    ${SOURCE_PATH}/SampleTable.cpp
    ${SOURCE_PATH}/SampleIterator.cpp
    ${SOURCE_PATH}/FLACExtractor.cpp
    ${SOURCE_PATH}/OggExtractor.cpp
    ${SOURCE_PATH}/MidiExtractor.cpp
    ${SOURCE_PATH}/AACExtractor.cpp
    ${SOURCE_PATH}/MediaExtractor.cpp
    ${SOURCE_PATH}/BufferImpl.cpp
    ${SOURCE_PATH}/ACodecBufferChannel.cpp
    ${SOURCE_PATH}/OmxInfoBuilder.cpp
    ${SOURCE_PATH}/MediaClock.cpp
    ${SOURCE_PATH}/VideoFrameScheduler.cpp
    #${SOURCE_PATH}/StagefrightMetadataRetriever.cpp
    ${SOURCE_PATH}/MediaMuxer.cpp
    ${SOURCE_PATH}/MediaAdapter.cpp
    ${SOURCE_PATH}/MPEG4Writer.cpp
    )

    list(REMOVE_ITEM STAGEFRIGHT_SOURCE_FILES
    ${SOURCE_PATH}/MediaExtractor_legacy.cpp
    )

    if (MSVC)
        #add_definitions(-DNOMINMAX=1)
        add_definitions(-D__unused= )
        add_definitions(-Dstrcasestr=strstr)
    elseif(LINUX)
        add_definitions(-D__unused= )
    endif() 
endif(ENABLE_AV_CODEC)

# target files
#set(LIB_NAME stagefright)
#set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
#add_library(${LIB_NAME} SHARED ${STAGEFRIGHT_SOURCE_FILES} ${STAGEFRIGHT_HEADER_FILES})
#target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})

# sub module
add_subdirectory(codecs) 
add_subdirectory(colorconversion)
add_subdirectory(filters)
add_subdirectory(flac)
#foundation
#add_subdirectory(http) 
#add_subdirectory(httplive) 
add_subdirectory(id3) 
add_subdirectory(mpeg2ts) 
#add_subdirectory(omx) 
#add_subdirectory(rtsp) 
#tests
add_subdirectory(timedtext)
add_subdirectory(webm)
add_subdirectory(xmlparser)

add_subdirectory(bqhelper)
