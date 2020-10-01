
if(CFG_NO_DEFAULT)
  if(CFG_ENABLE_CORE)
    set(ENABLE_CORE  "TRUE")

  elseif(CFG_ENABLE_NATIVE)
    set(ENABLE_CORE    "TRUE")
    set(ENABLE_NATIVE  "TRUE")
  
  elseif (CFG_ENABLE_AV_UTILS)
    set(ENABLE_CORE       "TRUE")  
    set(ENABLE_NATIVE     "TRUE")

    #set(ENABLE_DESKTOP_GL  "TRUE") 
    set(ENABLE_ANGLE      "TRUE")
    set(ENABLE_HARDWARE   "TRUE")
    set(ENABLE_AV_UTILS   "TRUE") 
  
  elseif(CFG_ENABLE_AV_BASE)
    set(ENABLE_CORE      "TRUE")  
    set(ENABLE_NATIVE    "TRUE")
    set(ENABLE_ANGLE      "TRUE")
    set(ENABLE_HARDWARE   "TRUE") 
    set(ENABLE_AV_UTILS  "TRUE") 
     
    set(ENABLE_AV_BASE   "TRUE")   
 
  elseif(CFG_ENABLE_TOOL_GEN)
    set(ENABLE_CORE      "TRUE")
    set(ENABLE_HIDL_GEN  "TRUE")

  elseif(CFG_ENABLE_AV_CODEC)
    set(ENABLE_CORE      "TRUE")  
    set(ENABLE_NATIVE    "TRUE")
    set(ENABLE_ANGLE      "TRUE")
    set(ENABLE_HARDWARE   "TRUE") 
	  set(ENABLE_AV_UTILS    "TRUE")      
    set(ENABLE_AV_BASE   "TRUE")  

    set(ENABLE_AV_CODEC  "TRUE")

  elseif(CFG_ENABLE_APP)
    set(ENABLE_APP  "TRUE")
  elseif(CFG_ENABLE_SKIA_CHROME)
    set(ENABLE_SKIA_CHROME  "TRUE")
  elseif(CFG_ENABLE_GLUT)
    set(ENABLE_GLUT  "TRUE")
  elseif(CFG_ENABLE_ANGLE)
    set(ENABLE_ANGLE "TRUE")
  elseif(CFG_ENABLE_WXWIDGETS)
    set(ENABLE_WXWIDGETS "TRUE")
  endif()

  if(CFG_ENABLE_TEST)
    set(ENABLE_TEST  "TRUE")
  endif(CFG_ENABLE_TEST)

else(CFG_NO_DEFAULT)
  set(ENABLE_CORE      "TRUE")
  set(ENABLE_NATIVE    "TRUE")
  set(ENABLE_SURFACE_FLINGER  "TRUE")
  set(ENABLE_AV_UTILS  "TRUE")  
  set(ENABLE_ANDROID_GL     "TRUE")
  set(ENABLE_ANGLE     "TRUE")
  set(ENABLE_HARDWARE  "TRUE")
  set(ENABLE_AV_BASE   "TRUE") 
  set(ENABLE_AV_CODEC  "TRUE")
  set(ENABLE_RAYLIB    "TRUE")
  set(ENABLE_GLFW      "TRUE")
  #set(ENABLE_APP       "TRUE")  
  #set(ENABLE_TEST      "TRUE")
endif(CFG_NO_DEFAULT)

if (ENABLE_ANGLE)
	set(CMAKE_MODULE_PATH ${M3E_SOURCE_DIR}/cmake/tool)
	find_package(OpenGLES2)
	if (OPENGLES2_FOUND)
	  	set(ENABLE_ANGLE "FALSE")
	endif(OPENGLES2_FOUND)
endif(ENABLE_ANGLE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# create the folder for building result
if(NOT EXISTS ${BUILD_PATH})
  message(STATUS "Create\t${BUILD_PATH}")
  exec_program("mkdir ${BUILD_PATH}")
endif()

# create and generate project for building tool
if(NOT EXISTS ${M3E_SOURCE_DIR}/tool)
  if(APPLE)
    set(ARG_GENERATE  "-G Xcode")
  else()
    set(ARG_GENERATE  "")
  endif()

  exec_program("mkdir tool" ${M3E_SOURCE_DIR})
  exec_program("cmake ${ARG_GENERATE} -C ${M3E_SOURCE_DIR}/cmake/config/tool_gen.cmake .." ${M3E_SOURCE_DIR}/tool)
endif()

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
if(NOT EXISTS ${TMP_PATH}/${AIDL_HEADER_PATH})
    exec_program("mkdir ${AIDL_HEADER_PATH}" ${TMP_PATH})
endif()
if(NOT EXISTS ${TMP_PATH}/${AIDL_SOURCE_PATH})
    exec_program("mkdir ${AIDL_SOURCE_PATH}" ${TMP_PATH})
endif()

# create the configure header file
#if(NOT EXISTS ${M3E_CFG_PATH})
#  message(STATUS "Create\t${M3E_CFG_PATH}")
#  exec_program("mkdir ${M3E_CFG_PATH}")
#endif()
#configure_file(${M3E_SOURCE_DIR}/cmake/config/config.h.in ${M3E_CFG_PATH}/m3e_config.h)

# the subdirectory
add_subdirectory(external)

if(ENABLE_NATIVE)
  if(NOT EXISTS ${BIN_HIDL_GEN})
    message( FATAL_ERROR "Please firstly build ${M3E_SOURCE_DIR}/tool " )
  endif()

  add_subdirectory(frameworks)
  add_subdirectory(system)
endif(ENABLE_NATIVE)

if(ENABLE_CORE)
  add_subdirectory(core)
endif(ENABLE_CORE)

if(ENABLE_HARDWARE)
  add_subdirectory(hardware)
endif(ENABLE_HARDWARE)

if(ENABLE_APP)
  #add_subdirectory(engine)
  #add_subdirectory(m3ecmd)
  #add_subdirectory(app)
endif(ENABLE_APP)
