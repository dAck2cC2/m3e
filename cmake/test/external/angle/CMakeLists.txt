
# demo program

project(TEST_ANGLE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif(MSVC)
    add_definitions(-DNOMINMAX=1)
endif()

set(DEMO_DEPLIBS 
angle
angle_util
)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src/)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util)

ADD_DEMO(angle_WindowTest 
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/WindowTest/WindowTest.cpp
)
ADD_DEMO(angle_hello_triangle
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/hello_triangle/HelloTriangle.cpp
)
ADD_DEMO(angle_multi_window
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multi_window/MultiWindow.cpp
)

ADD_DEMO(angle_mip_map_2d
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/mip_map_2d/MipMap2D.cpp
)
ADD_DEMO(angle_multi_texture
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
#${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/tga_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multi_texture/MultiTexture.cpp
)
add_custom_command(TARGET test_angle_multi_texture POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multi_texture/*.tga $<TARGET_FILE_DIR:test_angle_multi_texture>
)
ADD_DEMO(angle_multiple_draw_buffers
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multiple_draw_buffers/MultipleDrawBuffers.cpp
)
add_custom_command(TARGET test_angle_multiple_draw_buffers POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multiple_draw_buffers/*.glsl $<TARGET_FILE_DIR:test_angle_multiple_draw_buffers>
)
ADD_DEMO(angle_multiview
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/multiview/Multiview.cpp
)
ADD_DEMO(angle_particle_system
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/tga_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/particle_system/ParticleSystem.cpp
)
add_custom_command(TARGET test_angle_particle_system POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/particle_system/*.tga $<TARGET_FILE_DIR:test_angle_particle_system>
)
ADD_DEMO(angle_post_sub_buffer
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/post_sub_buffer/PostSubBuffer.cpp
)
ADD_DEMO(angle_simple_instancing
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/simple_instancing/SimpleInstancing.cpp
)
ADD_DEMO(angle_simple_texture_2d
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/simple_texture_2d/SimpleTexture2D.cpp
)
ADD_DEMO(angle_simple_texture_cubemap
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/simple_texture_cubemap/SimpleTextureCubemap.cpp
)
ADD_DEMO(angle_simple_vertex_shader
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/simple_vertex_shader/SimpleVertexShader.cpp
)
ADD_DEMO(angle_stencil_operations
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/stencil_operations/StencilOperations.cpp
)
ADD_DEMO(angle_tex_redef_microbench
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/tex_redef_microbench/TexRedefMicroBench.cpp
)
ADD_DEMO(angle_texture_wrap
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/texture_utils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/texture_wrap/TextureWrap.cpp
)
ADD_DEMO(angle_tri_fan_microbench
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/sample_util/SampleApplication.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/angle/samples/tri_fan_microbench/TriFanMicroBench.cpp
)
