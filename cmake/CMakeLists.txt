
if(CFG_NO_DEFAULT)
  if(CFG_ENABLE_CORE)
    set(ENABLE_CORE  "TRUE")

  elseif(CFG_ENABLE_NATIVE)
    set(ENABLE_CORE    "TRUE")
    set(ENABLE_NATIVE  "TRUE")
  
  elseif (CFG_ENABLE_AV_UTILS)
    set(ENABLE_CORE       "TRUE")  
    set(ENABLE_NATIVE     "TRUE")
    set(ENABLE_DESKTOP_GL  "TRUE") 
    #set(ENABLE_ANGLE      "TRUE")
	  set(ENABLE_AV_UTILS   "TRUE")
    set(ENABLE_HARDWARE   "TRUE") 
  
  elseif(CFG_ENABLE_AV_BASE)
    set(ENABLE_CORE      "TRUE")  
    set(ENABLE_NATIVE    "TRUE")
 	  set(ENABLE_AV_UTILS  "TRUE") 
    set(ENABLE_AV_BASE   "TRUE")   
 
  elseif(CFG_ENABLE_AV_CODEC)
    set(ENABLE_CORE      "TRUE")  
    set(ENABLE_NATIVE    "TRUE")

	set(ENABLE_AV_UTILS    "TRUE")      
    set(ENABLE_AV_BASE   "TRUE")    
    set(ENABLE_AV_CODEC  "TRUE")

  elseif(CFG_ENABLE_APP)
    set(ENABLE_APP  "TRUE")
  elseif(CFG_ENABLE_SKIA)
    set(ENABLE_SKIA  "TRUE")
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
  set(ENABLE_AV_UTILS  "TRUE")  
  set(ENABLE_AV_BASE   "TRUE")
  set(ENABLE_APP       "TRUE")  
#  set(ENABLE_TEST  "TRUE")
endif(CFG_NO_DEFAULT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# create hte folder for building result
if(NOT EXISTS ${BUILD_PATH})
  message(STATUS "Create\t${BUILD_PATH}")
  exec_program("mkdir ${BUILD_PATH}")
endif()

# the subdirectory
add_subdirectory(external)
add_subdirectory(frameworks)

if(ENABLE_CORE)
  add_subdirectory(core)
endif(ENABLE_CORE)

if(ENABLE_HARDWARE)
  add_subdirectory(hardware)
endif(ENABLE_HARDWARE)

if(ENABLE_AV_BASE)
  #add_subdirectory(media)
  #add_subdirectory(audio)
endif(ENABLE_AV_BASE)

if(ENABLE_APP)
  #add_subdirectory(engine)
  #add_subdirectory(m3ecmd)
  #add_subdirectory(app)
endif(ENABLE_APP)

if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
