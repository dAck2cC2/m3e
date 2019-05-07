
add_subdirectory(openslesut)
add_subdirectory(opensles_helper)
add_subdirectory(wilhelm)
add_subdirectory(opensles)
add_subdirectory(openmaxal)

set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
