
project(SDL C)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sdl/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/)

add_definitions(-DHAVE_EXPAT_CONFIG_H)
add_definitions(-DHAVE_ACOS)
add_definitions(-DHAVE_ASIN)
add_definitions(-DHAVE_ATAN)
add_definitions(-DHAVE_ATAN2)
add_definitions(-DHAVE_CEIL)
add_definitions(-DHAVE_COPYSIGN)
add_definitions(-DHAVE_COS)
add_definitions(-DHAVE_COSF)
add_definitions(-DHAVE_FABS)
add_definitions(-DHAVE_FLOOR)
add_definitions(-DHAVE_LOG)
add_definitions(-DHAVE_POW)
add_definitions(-DHAVE_SCALBN)
add_definitions(-DHAVE_SIN)
add_definitions(-DHAVE_SINF)
add_definitions(-DHAVE_SQRT)
add_definitions(-DHAVE_SQRTF)
add_definitions(-DHAVE_TAN)
add_definitions(-DHAVE_TANF)
add_definitions(-DSDL_HAPTIC_DISABLED=1)
add_definitions(-DSDL_JOYSTICK_DISABLED=1)
add_definitions(-DUSING_PREMAKE_CONFIG_H)

file(GLOB SDL_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/include/*.h
)

set(SDL_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/SDL.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/SDL_assert.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/SDL_error.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/SDL_hints.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/SDL_log.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/atomic/SDL_atomic.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/atomic/SDL_spinlock.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_audio.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_audiocvt.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_audiodev.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_audiotypecvt.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_mixer.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/SDL_wave.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/cpuinfo/SDL_cpuinfo.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/dynapi/SDL_dynapi.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_clipboardevents.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_dropevents.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_events.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_gesture.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_keyboard.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_mouse.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_quit.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_touch.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/events/SDL_windowevents.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/file/SDL_rwops.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/haptic/SDL_haptic.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/haptic/dummy/SDL_syshaptic.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/joystick/SDL_gamecontroller.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/joystick/SDL_joystick.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/joystick/dummy/SDL_sysjoystick.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/power/SDL_power.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/SDL_render.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/SDL_yuv_sw.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_blendfillrect.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_blendline.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_blendpoint.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_drawline.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_drawpoint.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_render_sw.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/software/SDL_rotate.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_getenv.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_iconv.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_malloc.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_qsort.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_stdlib.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/stdlib/SDL_string.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/thread/SDL_thread.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/timer/SDL_timer.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_RLEaccel.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_0.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_1.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_A.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_N.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_auto.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_copy.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_blit_slow.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_bmp.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_clipboard.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_egl.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_fillrect.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_pixels.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_rect.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_shape.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_stretch.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_surface.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/SDL_video.c 
)

if(APPLE)

find_library(COCOA_LIBRARY Cocoa)
list(APPEND SDL_DEPLIB ${COCOA_LIBRARY})

find_library(COREAUDIO CoreAudio)
list(APPEND SDL_DEPLIB ${COREAUDIO})

find_library(COREVIDEO CoreVideo)
list(APPEND SDL_DEPLIB ${COREVIDEO})

#find_library(AUDIOTOOLBOX AudioToolbox)
#list(APPEND SDL_DEPLIB ${AUDIOTOOLBOX})

find_library(AUDIOTOOLBOX Foundation)
list(APPEND SDL_DEPLIB ${AUDIOTOOLBOX})

find_library(IOKIT IOKit)
list(APPEND SDL_DEPLIB ${IOKIT})


#set(SDL_DEPLIB ${SDL_DEPLIB} 
#Cocoa.framework
#Foundation.framework
#IOKit.framework
#QuartzCore.framework
#)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/premake/Xcode/Xcode4)

add_definitions(-DSDL_FILESYSTEM_COCOA=1)
add_definitions(-DSDL_VIDEO_DRIVER_COCOA=1)
add_definitions(-DSDL_VIDEO_OPENGL=1)
add_definitions(-DSDL_VIDEO_RENDER_OGL=1)
add_definitions(-DSDL_VIDEO_OPENGL_CGL=1)

set(SDL_SOURCE_FILES ${SDL_SOURCE_FILES}
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/file/cocoa/SDL_rwopsbundlesupport.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/filesystem/cocoa/SDL_sysfilesystem.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/opengl/SDL_render_gl.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/render/opengl/SDL_shaders_gl.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoaclipboard.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoaevents.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoakeyboard.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoamessagebox.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoamodes.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoamouse.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoamousetap.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoaopengl.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoashape.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoavideo.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/cocoa/SDL_cocoawindow.m
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/dummy/SDL_nullvideo.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/dummy/SDL_nullframebuffer.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/video/dummy/SDL_nullevents.c 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/coreaudio/SDL_coreaudio.m 
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/disk/SDL_diskaudio.c
${M3E_SOURCE_DIR}/${EXT_PATH}/sdl/src/audio/dummy/SDL_dummyaudio.c
)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(sdl SHARED ${SDL_SOURCE_FILES} ${SDL_HEADER_FILES})
target_link_libraries(sdl ${SDL_DEPLIB})
