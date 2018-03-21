
project(ANGLE)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
message(STATUS "Download\t angel")
exec_program("git clone https://github.com/google/angle.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git reset --hard b2c60b1a195049ede3f3d28a81cb1ff35929f88b" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

add_definitions(-DLIBANGLE_IMPLEMENTATION)
