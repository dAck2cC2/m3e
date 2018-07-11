#ifndef __glplatform_h_
#define __glplatform_h_

#include <KHR/khrplatform.h>

#if defined(_WIN32)
#	include <GL/GL.h>
#	include <GL/GLU.h>
#elif defined(__APPLE__)
#   include <OpenGL/gl.h>
#else
#   error "Unknow platform for OpenGL"
#endif 

#endif /* __glplatform_h_ */
