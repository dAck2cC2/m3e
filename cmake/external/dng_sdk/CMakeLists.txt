# dng_sdk
project(DNG_SDK)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/dng_sdk/include.cmake)

GET_ANDROID_MODULE(dng_sdk)

include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg-turbo/include.cmake)

set(DNG_DEPLIB
zlib
${JPEG_LIBRARIES}
)

add_definitions(-DqDNGThreadSafe=1)
add_definitions(-DqDNGUseLibJPEG=1)
add_definitions(-DqDNGUseXMP=0)
add_definitions(-DqDNGValidate=0)
add_definitions(-DqDNGValidateTarget=1)

if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND DNG_DEPLIB ${APPKIT_LIBRARY})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/dng_sdk/source )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/dng_sdk/source )

file(GLOB DNG_HEADER_FILES
${HEADER_PATH}/*.h
)

set(DNG_SOURCE_FILES
${SOURCE_PATH}/dng_1d_function.cpp 
${SOURCE_PATH}/dng_1d_table.cpp 
${SOURCE_PATH}/dng_abort_sniffer.cpp 
${SOURCE_PATH}/dng_area_task.cpp 
${SOURCE_PATH}/dng_bad_pixels.cpp 
${SOURCE_PATH}/dng_bottlenecks.cpp 
${SOURCE_PATH}/dng_camera_profile.cpp 
${SOURCE_PATH}/dng_color_space.cpp 
${SOURCE_PATH}/dng_color_spec.cpp 
${SOURCE_PATH}/dng_date_time.cpp 
${SOURCE_PATH}/dng_exceptions.cpp 
${SOURCE_PATH}/dng_exif.cpp 
${SOURCE_PATH}/dng_file_stream.cpp 
${SOURCE_PATH}/dng_filter_task.cpp 
${SOURCE_PATH}/dng_fingerprint.cpp 
${SOURCE_PATH}/dng_gain_map.cpp 
${SOURCE_PATH}/dng_globals.cpp 
${SOURCE_PATH}/dng_host.cpp 
${SOURCE_PATH}/dng_hue_sat_map.cpp 
${SOURCE_PATH}/dng_ifd.cpp 
${SOURCE_PATH}/dng_image.cpp 
${SOURCE_PATH}/dng_image_writer.cpp 
${SOURCE_PATH}/dng_info.cpp 
${SOURCE_PATH}/dng_iptc.cpp 
${SOURCE_PATH}/dng_jpeg_image.cpp 
${SOURCE_PATH}/dng_jpeg_memory_source.cpp 
${SOURCE_PATH}/dng_lens_correction.cpp 
${SOURCE_PATH}/dng_linearization_info.cpp 
${SOURCE_PATH}/dng_lossless_jpeg.cpp 
${SOURCE_PATH}/dng_matrix.cpp 
${SOURCE_PATH}/dng_memory.cpp 
${SOURCE_PATH}/dng_memory_stream.cpp 
${SOURCE_PATH}/dng_misc_opcodes.cpp 
${SOURCE_PATH}/dng_mosaic_info.cpp 
${SOURCE_PATH}/dng_mutex.cpp 
${SOURCE_PATH}/dng_negative.cpp 
${SOURCE_PATH}/dng_opcode_list.cpp 
${SOURCE_PATH}/dng_opcodes.cpp 
${SOURCE_PATH}/dng_orientation.cpp 
${SOURCE_PATH}/dng_parse_utils.cpp 
${SOURCE_PATH}/dng_pixel_buffer.cpp 
${SOURCE_PATH}/dng_point.cpp 
${SOURCE_PATH}/dng_preview.cpp 
${SOURCE_PATH}/dng_pthread.cpp 
${SOURCE_PATH}/dng_rational.cpp 
${SOURCE_PATH}/dng_read_image.cpp 
${SOURCE_PATH}/dng_rect.cpp 
${SOURCE_PATH}/dng_ref_counted_block.cpp 
${SOURCE_PATH}/dng_reference.cpp 
${SOURCE_PATH}/dng_render.cpp 
${SOURCE_PATH}/dng_resample.cpp 
${SOURCE_PATH}/dng_safe_arithmetic.cpp 
${SOURCE_PATH}/dng_shared.cpp 
${SOURCE_PATH}/dng_simple_image.cpp 
${SOURCE_PATH}/dng_spline.cpp 
${SOURCE_PATH}/dng_stream.cpp 
${SOURCE_PATH}/dng_string.cpp 
${SOURCE_PATH}/dng_string_list.cpp 
${SOURCE_PATH}/dng_tag_types.cpp 
${SOURCE_PATH}/dng_temperature.cpp 
${SOURCE_PATH}/dng_tile_iterator.cpp 
${SOURCE_PATH}/dng_tone_curve.cpp 
${SOURCE_PATH}/dng_utils.cpp 
${SOURCE_PATH}/dng_xy_coord.cpp 
${SOURCE_PATH}/dng_xmp.cpp
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(dng_sdk ${LIB_TYPE} ${DNG_SOURCE_FILES} ${DNG_HEADER_FILES})
target_link_libraries(dng_sdk ${DNG_DEPLIB})
