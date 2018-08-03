//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// WindowSurfaceWGL.cpp: WGL implementation of egl::Surface for windows

#include "libANGLE/renderer/gl/wgl/WindowSurfaceWGL.h"

#include "common/debug.h"
#include "libANGLE/Error.h"
//#include "libANGLE/renderer/gl/RendererGL.h"
#include "libANGLE/renderer/gl/wgl/FunctionsWGL.h"
#include "libANGLE/renderer/gl/wgl/wgl_utils.h"

namespace rx
{

WindowSurfaceWGL::WindowSurfaceWGL(const egl::SurfaceState &state,
                                   RendererGL *renderer,
                                   EGLNativeWindowType window,
                                   int pixelFormat,
                                   const FunctionsWGL *functions,
                                   EGLint orientation)
    : SurfaceWGL(state, renderer),
      mPixelFormat(pixelFormat),
      mWindow(window),
      mDeviceContext(nullptr),
	  mWGLContext(nullptr),
      mFunctionsWGL(functions),
      mSwapBehavior(0)
{
    // EGL_ANGLE_surface_orientation is not supported for regular WGL window surfaces
    ASSERT(orientation == 0);
}

WindowSurfaceWGL::~WindowSurfaceWGL()
{
    ReleaseDC(mWindow, mDeviceContext);
    mDeviceContext = nullptr;
}

egl::Error WindowSurfaceWGL::initialize(const egl::Display *display)
{
    mDeviceContext = GetDC(mWindow);
    if (!mDeviceContext)
    {
        return egl::EglBadNativeWindow()
               << "Failed to get the device context from the native window, "
               << gl::FmtErr(GetLastError());
    }

#if 1
	// Require that the pixel format for this window has not been set yet or is equal to the Display's pixel format.
	int windowPixelFormat = GetPixelFormat(mDeviceContext);
	if (windowPixelFormat == 0)
	{
		PIXELFORMATDESCRIPTOR pixelFormatDescriptor = wgl::GetDefaultPixelFormatDescriptor();
		if (mFunctionsWGL->choosePixelFormatARB)
		{
			std::vector<int> attribs = wgl::GetDefaultPixelFormatAttributes(false);

			UINT matchingFormats = 0;
			mFunctionsWGL->choosePixelFormatARB(mDeviceContext, &attribs[0], nullptr, 1u, &mPixelFormat,
				&matchingFormats);
		}

		if (mPixelFormat == 0)
		{
			mPixelFormat = ChoosePixelFormat(mDeviceContext, &pixelFormatDescriptor);
		}

		if (mPixelFormat == 0)
		{
			return egl::EglNotInitialized()
				<< "Could not find a compatible pixel format for the intermediate OpenGL window.";
		}

		if (!SetPixelFormat(mDeviceContext, mPixelFormat, &pixelFormatDescriptor))
		{
			return egl::EglNotInitialized()
				<< "Failed to set the pixel format on the device context, "
				<< gl::FmtErr(GetLastError());
		}

		if (!DescribePixelFormat(mDeviceContext, mPixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor))
		{
			return egl::EglBadNativeWindow()
				<< "Failed to DescribePixelFormat, " << gl::FmtErr(GetLastError());
		}
    }
    else if (windowPixelFormat != mPixelFormat)
    {
        return egl::EglNotInitialized()
               << "Pixel format of the NativeWindow and NativeDisplayType must match.";
    }

    // Check for the swap behavior of this pixel format
    switch (
        wgl::QueryWGLFormatAttrib(mDeviceContext, mPixelFormat, WGL_SWAP_METHOD_ARB, mFunctionsWGL))
    {
        case WGL_SWAP_COPY_ARB:
            mSwapBehavior = EGL_BUFFER_PRESERVED;
            break;

        case WGL_SWAP_EXCHANGE_ARB:
        case WGL_SWAP_UNDEFINED_ARB:
        default:
            mSwapBehavior = EGL_BUFFER_DESTROYED;
            break;
    }

	// If wglCreateContextAttribsARB is unavailable or failed, try the standard wglCreateContext
	if (!mWGLContext)
	{
		// Don't have control over GL versions
		mWGLContext = mFunctionsWGL->createContext(mDeviceContext);
	}

	if (!mWGLContext)
	{
		return egl::EglNotInitialized()
			<< "Failed to create a WGL context for the intermediate OpenGL window.";
	}
#else
	// Require that the pixel format for this window has not been set yet or is equal to the Display's pixel format.
	int windowPixelFormat = GetPixelFormat(mDeviceContext);
	if (windowPixelFormat == 0)
	{
		PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };
		if (!DescribePixelFormat(mDeviceContext, mPixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor))
		{
			return egl::EglBadNativeWindow()
				<< "Failed to DescribePixelFormat, " << gl::FmtErr(GetLastError());
		}

		if (!SetPixelFormat(mDeviceContext, mPixelFormat, &pixelFormatDescriptor))
		{
			return egl::EglNotInitialized()
				<< "Failed to set the pixel format on the device context, "
				<< gl::FmtErr(GetLastError());
		}
	}
	else if (windowPixelFormat != mPixelFormat)
	{
		return egl::EglNotInitialized()
			<< "Pixel format of the NativeWindow and NativeDisplayType must match.";
}

	// Check for the swap behavior of this pixel format
	switch (
		wgl::QueryWGLFormatAttrib(mDeviceContext, mPixelFormat, WGL_SWAP_METHOD_ARB, mFunctionsWGL))
	{
	case WGL_SWAP_COPY_ARB:
		mSwapBehavior = EGL_BUFFER_PRESERVED;
		break;

	case WGL_SWAP_EXCHANGE_ARB:
	case WGL_SWAP_UNDEFINED_ARB:
	default:
		mSwapBehavior = EGL_BUFFER_DESTROYED;
		break;
	}

#endif

    return egl::NoError();
}

egl::Error WindowSurfaceWGL::makeCurrent()
{
	if (!mWGLContext)
	{
		return egl::EglNotInitialized()
			<< "Failed to create a WGL context for the intermediate OpenGL window.";
	}

	if (!mFunctionsWGL->makeCurrent(mDeviceContext, mWGLContext))
	{
		return egl::EglNotInitialized() << "Failed to make the intermediate WGL context current.";
	}

    return egl::NoError();
}

egl::Error WindowSurfaceWGL::unMakeCurrent()
{
	if (!mFunctionsWGL->makeCurrent(mDeviceContext, nullptr))
	{
		return egl::EglNotInitialized() << "Failed to make the intermediate WGL context current.";
	}

	return egl::NoError();
}

egl::Error WindowSurfaceWGL::swap(const gl::Context *context)
{
    if (!mFunctionsWGL->swapBuffers(mDeviceContext))
    {
        // TODO: What error type here?
        return egl::EglContextLost() << "Failed to swap buffers on the child window.";
    }

    return egl::NoError();
}

egl::Error WindowSurfaceWGL::postSubBuffer(const gl::Context *context,
                                           EGLint x,
                                           EGLint y,
                                           EGLint width,
                                           EGLint height)
{
    UNIMPLEMENTED();
    return egl::NoError();
}

egl::Error WindowSurfaceWGL::querySurfacePointerANGLE(EGLint attribute, void **value)
{
    *value = nullptr;
    return egl::NoError();
}

egl::Error WindowSurfaceWGL::bindTexImage(gl::Texture *texture, EGLint buffer)
{
    UNIMPLEMENTED();
    return egl::NoError();
}

egl::Error WindowSurfaceWGL::releaseTexImage(EGLint buffer)
{
    UNIMPLEMENTED();
    return egl::NoError();
}

void WindowSurfaceWGL::setSwapInterval(EGLint interval)
{
    if (mFunctionsWGL->swapIntervalEXT)
    {
        mFunctionsWGL->swapIntervalEXT(interval);
    }
}

EGLint WindowSurfaceWGL::getWidth() const
{
    RECT rect;
    if (!GetClientRect(mWindow, &rect))
    {
        return 0;
    }
    return rect.right - rect.left;
}

EGLint WindowSurfaceWGL::getHeight() const
{
    RECT rect;
    if (!GetClientRect(mWindow, &rect))
    {
        return 0;
    }
    return rect.bottom - rect.top;
}

EGLint WindowSurfaceWGL::isPostSubBufferSupported() const
{
    // PostSubBuffer extension not exposed on WGL.
    UNIMPLEMENTED();
    return EGL_FALSE;
}

EGLint WindowSurfaceWGL::getSwapBehavior() const
{
    return mSwapBehavior;
}

HDC WindowSurfaceWGL::getDC() const
{
    return mDeviceContext;
}
}