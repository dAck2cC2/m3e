//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// DisplayWGL.h: WGL implementation of egl::Display

#include "libANGLE/renderer/gl/wgl/DisplayWGL.h"

//#include "libANGLE/Config.h"
#include "libANGLE/Display.h"
#include "libANGLE/Surface.h"
#include "libANGLE/renderer/gl/renderergl_utils.h"
#include "libANGLE/renderer/gl/FunctionsGL.h"
#include "libANGLE/renderer/gl/wgl/FunctionsWGL.h"
#include "libANGLE/renderer/gl/wgl/PbufferSurfaceWGL.h"
#include "libANGLE/renderer/gl/wgl/WindowSurfaceWGL.h"
#include "libANGLE/renderer/gl/wgl/wgl_utils.h"

namespace rx
{
	class FunctionsGLWindows : public FunctionsGL
	{
	public:
		FunctionsGLWindows(HMODULE openGLModule, PFNWGLGETPROCADDRESSPROC getProcAddressWGL)
			: mOpenGLModule(openGLModule),
			mGetProcAddressWGL(getProcAddressWGL)
		{
			ASSERT(mOpenGLModule);
			ASSERT(mGetProcAddressWGL);
		}

		~FunctionsGLWindows() override {}

	private:
		void *loadProcAddress(const std::string &function) const override
		{
			void *proc = reinterpret_cast<void*>(mGetProcAddressWGL(function.c_str()));
			if (!proc)
			{
				proc = reinterpret_cast<void*>(GetProcAddress(mOpenGLModule, function.c_str()));
			}
			return proc;
		}

		HMODULE mOpenGLModule;
		PFNWGLGETPROCADDRESSPROC mGetProcAddressWGL;
	};

	DisplayWGL::DisplayWGL(const egl::DisplayState &state)
	    : DisplayGL(state),
		  mCurrentDC(nullptr),
		  mOpenGLModule(nullptr),
		  mFunctionsWGL(nullptr),
		  mFunctionsGL(nullptr),
		  mHasWGLCreateContextRobustness(false),
		  mHasRobustness(false),
		  mWindowClass(0),
		  mWindow(nullptr),
		  mDeviceContext(nullptr),
		  mPixelFormat(0),
		  mWGLContext(nullptr),
		  mDisplay(nullptr)
	{
	}

	DisplayWGL::~DisplayWGL()
	{
	}

	egl::Error DisplayWGL::initialize(egl::Display *display)
	{
		mDisplay = display;

		mOpenGLModule = LoadLibraryA("opengl32.dll");
		if (!mOpenGLModule)
		{
			return egl::EglNotInitialized() << "Failed to load OpenGL library.";
		}

		mFunctionsWGL = new FunctionsWGL();
		mFunctionsWGL->initialize(mOpenGLModule, nullptr);

		// WGL can't grab extensions until it creates a context because it needs to load the driver's DLLs first.
		// Create a dummy context to load the driver and determine which GL versions are available.

		// Work around compile error from not defining "UNICODE" while Chromium does
		const LPSTR idcArrow = MAKEINTRESOURCEA(32512);

		std::ostringstream stream;
		stream << "ANGLE DisplayWGL " << std::internal << std::setw(10) << std::setfill('0') << mDisplay
			<< " Intermediate Window Class";
		std::string className = stream.str();

		WNDCLASSA intermediateClassDesc = { 0 };
		intermediateClassDesc.style = CS_OWNDC;
		intermediateClassDesc.lpfnWndProc = DefWindowProc;
		intermediateClassDesc.cbClsExtra = 0;
		intermediateClassDesc.cbWndExtra = 0;
		intermediateClassDesc.hInstance = GetModuleHandle(nullptr);
		intermediateClassDesc.hIcon = nullptr;
		intermediateClassDesc.hCursor = LoadCursorA(nullptr, idcArrow);
		intermediateClassDesc.hbrBackground = 0;
		intermediateClassDesc.lpszMenuName = nullptr;
		intermediateClassDesc.lpszClassName = className.c_str();
		mWindowClass = RegisterClassA(&intermediateClassDesc);
		if (!mWindowClass)
		{
			return egl::EglNotInitialized() << "Failed to register intermediate OpenGL window class.";
		}

		HWND dummyWindow = CreateWindowExA(0,
			reinterpret_cast<const char *>(mWindowClass),
			"ANGLE Dummy Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			nullptr,
			nullptr);
		if (!dummyWindow)
		{
			return egl::EglNotInitialized() << "Failed to create dummy OpenGL window.";
		}

		HDC dummyDeviceContext = GetDC(dummyWindow);
		if (!dummyDeviceContext)
		{
			return egl::EglNotInitialized()
				<< "Failed to get the device context of the dummy OpenGL window.";
		}

		const PIXELFORMATDESCRIPTOR pixelFormatDescriptor = wgl::GetDefaultPixelFormatDescriptor();

		int dummyPixelFormat = ChoosePixelFormat(dummyDeviceContext, &pixelFormatDescriptor);
		if (dummyPixelFormat == 0)
		{
			return egl::EglNotInitialized()
				<< "Could not find a compatible pixel format for the dummy OpenGL window.";
		}

		if (!SetPixelFormat(dummyDeviceContext, dummyPixelFormat, &pixelFormatDescriptor))
		{
			return egl::EglNotInitialized()
				<< "Failed to set the pixel format on the intermediate OpenGL window.";
		}

		HGLRC dummyWGLContext = mFunctionsWGL->createContext(dummyDeviceContext);
		if (!dummyDeviceContext)
		{
			return egl::EglNotInitialized()
				<< "Failed to create a WGL context for the dummy OpenGL window.";
		}

		if (!mFunctionsWGL->makeCurrent(dummyDeviceContext, dummyWGLContext))
		{
			return egl::EglNotInitialized() << "Failed to make the dummy WGL context current.";
		}


		// Reinitialize the wgl functions to grab the extensions
		mFunctionsWGL->initialize(mOpenGLModule, dummyDeviceContext);

		mHasWGLCreateContextRobustness =
			mFunctionsWGL->hasExtension("WGL_ARB_create_context_robustness");

		// Destroy the dummy window and context
		mFunctionsWGL->makeCurrent(dummyDeviceContext, nullptr);
		mFunctionsWGL->deleteContext(dummyWGLContext);
		ReleaseDC(dummyWindow, dummyDeviceContext);
		DestroyWindow(dummyWindow);

		const egl::AttributeMap &displayAttributes = display->getAttributeMap();
		EGLint requestedDisplayType = static_cast<EGLint>(displayAttributes.get(
			EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE));
		if (requestedDisplayType == EGL_PLATFORM_ANGLE_TYPE_OPENGLES_ANGLE &&
			!mFunctionsWGL->hasExtension("WGL_EXT_create_context_es2_profile") &&
			!mFunctionsWGL->hasExtension("WGL_EXT_create_context_es_profile"))
		{
			return egl::EglNotInitialized() << "Cannot create an OpenGL ES platform on Windows without "
				"the WGL_EXT_create_context_es(2)_profile extension.";
		}
#if 1
		// Create the real intermediate context and windows
		mWindow = CreateWindowExA(0,
			reinterpret_cast<const char *>(mWindowClass),
			"ANGLE Intermediate Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			nullptr,
			nullptr);
		if (!mWindow)
		{
			return egl::EglNotInitialized() << "Failed to create intermediate OpenGL window.";
		}

		mDeviceContext = GetDC(mWindow);
		if (!mDeviceContext)
		{
			return egl::EglNotInitialized()
				<< "Failed to get the device context of the intermediate OpenGL window.";
		}

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
				<< "Failed to set the pixel format on the intermediate OpenGL window.";
		}

		if (mFunctionsWGL->createContextAttribsARB)
		{

			mWGLContext = initializeContextAttribs(displayAttributes);
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

		if (!mFunctionsWGL->makeCurrent(mDeviceContext, mWGLContext))
		{
			return egl::EglNotInitialized() << "Failed to make the intermediate WGL context current.";
		}
		mCurrentDC = mDeviceContext;

		mFunctionsGL = new FunctionsGLWindows(mOpenGLModule, mFunctionsWGL->getProcAddress);
		mFunctionsGL->initialize(displayAttributes);

		mHasRobustness = mFunctionsGL->getGraphicsResetStatus != nullptr;
		if (mHasWGLCreateContextRobustness != mHasRobustness)
		{
			WARN() << "WGL_ARB_create_context_robustness exists but unable to OpenGL context with "
				"robustness.";
		}
#endif
		/*
		// Intel OpenGL ES drivers are not currently supported due to bugs in the driver and ANGLE
		VendorID vendor = GetVendorID(mFunctionsGL);
		if (requestedDisplayType == EGL_PLATFORM_ANGLE_TYPE_OPENGLES_ANGLE && IsIntel(vendor))
		{
			return egl::EglNotInitialized() << "Intel OpenGL ES drivers are not supported.";
		}
		*/

		return DisplayGL::initialize(display);
	}

	void DisplayWGL::terminate()
	{
		DisplayGL::terminate();

		mFunctionsWGL->makeCurrent(mDeviceContext, nullptr);
		mCurrentDC = nullptr;
		mFunctionsWGL->deleteContext(mWGLContext);
		mWGLContext = nullptr;

		ReleaseDC(mWindow, mDeviceContext);
		mDeviceContext = nullptr;

		DestroyWindow(mWindow);
		mWindow = nullptr;

		UnregisterClassA(reinterpret_cast<const char *>(mWindowClass), nullptr);
		mWindowClass = NULL;

		SafeDelete(mFunctionsWGL);
		SafeDelete(mFunctionsGL);

		FreeLibrary(mOpenGLModule);
		mOpenGLModule = nullptr;

		return;
	}

	egl::Error DisplayWGL::makeCurrent(egl::Surface *drawSurface,
		egl::Surface *readSurface,
		gl::Context *context)
	{
		/*
		if (drawSurface)
		{
			SurfaceWGL *drawSurfaceWGL = GetImplAs<SurfaceWGL>(drawSurface);
			HDC dc = drawSurfaceWGL->getDC();
			if (dc != mCurrentDC)
			{
				if (!mFunctionsWGL->makeCurrent(dc, mWGLContext))
				{
					// TODO(geofflang): What error type here?
					return egl::EglContextLost() << "Failed to make the WGL context current.";
				}
				mCurrentDC = dc;
			}
		}
		*/

		return DisplayGL::makeCurrent(drawSurface, readSurface, context);
	}

	egl::ConfigSet DisplayWGL::generateConfigs()
	{
		egl::ConfigSet configs;

		int minSwapInterval = 1;
		int maxSwapInterval = 1;
		if (mFunctionsWGL->swapIntervalEXT)
		{
			// No defined maximum swap interval in WGL_EXT_swap_control, use a reasonable number
			minSwapInterval = 0;
			maxSwapInterval = 8;
		}

		const gl::Version &maxVersion = getMaxSupportedESVersion();
		ASSERT(maxVersion >= gl::Version(2, 0));
		bool supportsES3 = maxVersion >= gl::Version(3, 0);

		PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
		DescribePixelFormat(mDeviceContext, mPixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);

		auto getAttrib = [this](int attrib)
		{
			return wgl::QueryWGLFormatAttrib(mDeviceContext, mPixelFormat, attrib, mFunctionsWGL);
		};

		const EGLint optimalSurfaceOrientation = 0;
			//mUseDXGISwapChains ? EGL_SURFACE_ORIENTATION_INVERT_Y_ANGLE : 0;

		egl::Config config;
		config.renderTargetFormat = GL_RGBA8; // TODO: use the bit counts to determine the format
		config.depthStencilFormat = GL_DEPTH24_STENCIL8; // TODO: use the bit counts to determine the format
		config.bufferSize = pixelFormatDescriptor.cColorBits;
		config.redSize = pixelFormatDescriptor.cRedBits;
		config.greenSize = pixelFormatDescriptor.cGreenBits;
		config.blueSize = pixelFormatDescriptor.cBlueBits;
		config.luminanceSize = 0;
		config.alphaSize = pixelFormatDescriptor.cAlphaBits;
		config.alphaMaskSize = 0;
		config.bindToTextureRGB = (getAttrib(WGL_BIND_TO_TEXTURE_RGB_ARB) == TRUE);
		config.bindToTextureRGBA = (getAttrib(WGL_BIND_TO_TEXTURE_RGBA_ARB) == TRUE);
		config.colorBufferType = EGL_RGB_BUFFER;
		config.configCaveat = EGL_NONE;
		config.conformant = EGL_OPENGL_ES2_BIT | (supportsES3 ? EGL_OPENGL_ES3_BIT_KHR : 0);
		config.depthSize = pixelFormatDescriptor.cDepthBits;
		config.level = 0;
		config.matchNativePixmap = EGL_NONE;
		config.maxPBufferWidth = getAttrib(WGL_MAX_PBUFFER_WIDTH_ARB);
		config.maxPBufferHeight = getAttrib(WGL_MAX_PBUFFER_HEIGHT_ARB);
		config.maxPBufferPixels = getAttrib(WGL_MAX_PBUFFER_PIXELS_ARB);
		config.maxSwapInterval = maxSwapInterval;
		config.minSwapInterval = minSwapInterval;
		config.nativeRenderable = EGL_TRUE; // Direct rendering
		config.nativeVisualID = 0;
		config.nativeVisualType = EGL_NONE;
		config.renderableType = EGL_OPENGL_ES2_BIT | (supportsES3 ? EGL_OPENGL_ES3_BIT_KHR : 0);
		config.sampleBuffers = 0; // FIXME: enumerate multi-sampling
		config.samples = 0;
		config.stencilSize = pixelFormatDescriptor.cStencilBits;
		config.surfaceType =
			((pixelFormatDescriptor.dwFlags & PFD_DRAW_TO_WINDOW) ? EGL_WINDOW_BIT : 0) |
			((getAttrib(WGL_DRAW_TO_PBUFFER_ARB) == TRUE) ? EGL_PBUFFER_BIT : 0) |
			((getAttrib(WGL_SWAP_METHOD_ARB) == WGL_SWAP_COPY_ARB) ? EGL_SWAP_BEHAVIOR_PRESERVED_BIT
				: 0);
		config.optimalOrientation = optimalSurfaceOrientation;
#ifdef EGL_EXT_pixel_format_float
		config.colorComponentType = EGL_COLOR_COMPONENT_TYPE_FIXED_EXT;
#endif 
		config.transparentType = EGL_NONE;
		config.transparentRedValue = 0;
		config.transparentGreenValue = 0;
		config.transparentBlueValue = 0;

		configs.add(config);

		return configs;
	}

	bool DisplayWGL::testDeviceLost()
	{
		return false;
	}

	egl::Error DisplayWGL::restoreLostDevice(const egl::Display *display)
	{
		return egl::EglBadDisplay();
	}

	bool DisplayWGL::isValidNativeWindow(EGLNativeWindowType window) const
	{
		return (IsWindow(window) == TRUE);
	}

	egl::Error DisplayWGL::validateClientBuffer(const egl::Config *configuration,
		EGLenum buftype,
		EGLClientBuffer clientBuffer,
		const egl::AttributeMap &attribs) const
	{
		return egl::EglBadDisplay();
	}

	DeviceImpl *DisplayWGL::createDevice()
	{
		UNREACHABLE();
		return nullptr;
	}

	std::string DisplayWGL::getVendorString() const
	{
		//UNIMPLEMENTED();
		return "";
	}

	const FunctionsGL *DisplayWGL::getFunctionsGL() const
	{
		return mFunctionsGL;
	}

	egl::Error DisplayWGL::waitClient(const gl::Context *context) const
	{
		// Unimplemented as this is not needed for WGL
		return egl::NoError();
	}

	egl::Error DisplayWGL::waitNative(const gl::Context *context, EGLint engine) const
	{
		// Unimplemented as this is not needed for WGL
		return egl::NoError();
	}

	void DisplayWGL::generateExtensions(egl::DisplayExtensions *outExtensions) const
	{
	}

	void DisplayWGL::generateCaps(egl::Caps *outCaps) const
	{
		outCaps->textureNPOT = true;
	}

	SurfaceImpl * DisplayWGL::createWindowSurface(const egl::SurfaceState &state,
		EGLNativeWindowType window,
		const egl::AttributeMap &attribs)
	{
		EGLint orientation = 0; // static_cast<EGLint>(attribs.get(EGL_SURFACE_ORIENTATION_ANGLE, 0));
		return new WindowSurfaceWGL(state, getRenderer(), window, mPixelFormat, mFunctionsWGL,
			orientation);
	}

	SurfaceImpl * DisplayWGL::createPbufferSurface(const egl::SurfaceState &state,
		const egl::AttributeMap &attribs)
	{
		EGLint width = static_cast<EGLint>(attribs.get(EGL_WIDTH, 0));
		EGLint height = static_cast<EGLint>(attribs.get(EGL_HEIGHT, 0));
		bool largest = (attribs.get(EGL_LARGEST_PBUFFER, EGL_FALSE) == EGL_TRUE);
		EGLenum textureFormat = static_cast<EGLenum>(attribs.get(EGL_TEXTURE_FORMAT, EGL_NO_TEXTURE));
		EGLenum textureTarget = static_cast<EGLenum>(attribs.get(EGL_TEXTURE_TARGET, EGL_NO_TEXTURE));

		return new PbufferSurfaceWGL(state, getRenderer(), width, height, textureFormat, textureTarget,
			largest, mPixelFormat, mDeviceContext, mFunctionsWGL);
	}

	SurfaceImpl * DisplayWGL::createPbufferFromClientBuffer(const egl::SurfaceState &state,
		EGLenum buftype,
		EGLClientBuffer clientBuffer,
		const egl::AttributeMap &attribs)
	{
		return NULL;
	}

	SurfaceImpl * DisplayWGL::createPixmapSurface(const egl::SurfaceState &state,
		NativePixmapType nativePixmap,
		const egl::AttributeMap &attribs)
	{
		return NULL;
	}

	HGLRC DisplayWGL::initializeContextAttribs(const egl::AttributeMap &eglAttributes) const
	{
		EGLint requestedDisplayType = static_cast<EGLint>(
			eglAttributes.get(EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE));

		// Create a context of the requested version, if any.
		gl::Version requestedVersion(static_cast<EGLint>(eglAttributes.get(
			EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE, EGL_DONT_CARE)),
			static_cast<EGLint>(eglAttributes.get(
				EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE, EGL_DONT_CARE)));
		if (static_cast<EGLint>(requestedVersion.major) != EGL_DONT_CARE &&
			static_cast<EGLint>(requestedVersion.minor) != EGL_DONT_CARE)
		{
			int profileMask = 0;
			if (requestedDisplayType != EGL_PLATFORM_ANGLE_TYPE_OPENGLES_ANGLE &&
				requestedVersion >= gl::Version(3, 2))
			{
				profileMask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
			}
			return createContextAttribs(requestedVersion, profileMask);
		}
		
		// Try all the GL version in order as a workaround for Mesa context creation where the driver
		// doesn't automatically return the highest version available.
		for (const auto &info : GenerateContextCreationToTry(requestedDisplayType, false))
		{
			int profileFlag = 0;
			if (info.type == ContextCreationTry::Type::DESKTOP_CORE)
			{
				profileFlag |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
				profileFlag |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
			}
			else if (info.type == ContextCreationTry::Type::ES)
			{
				profileFlag |= WGL_CONTEXT_ES_PROFILE_BIT_EXT;
			}

			HGLRC context = createContextAttribs(info.version, profileFlag);
			if (context != nullptr)
			{
				return context;
			}
		}
		
		return nullptr;
	}

	HGLRC DisplayWGL::createContextAttribs(const gl::Version &version, int profileMask) const
	{
		std::vector<int> attribs;

		if (mHasWGLCreateContextRobustness)
		{
			attribs.push_back(WGL_CONTEXT_FLAGS_ARB);
			attribs.push_back(WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB);
			attribs.push_back(WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB);
			attribs.push_back(WGL_LOSE_CONTEXT_ON_RESET_ARB);
		}

		attribs.push_back(WGL_CONTEXT_MAJOR_VERSION_ARB);
		attribs.push_back(version.major);

		attribs.push_back(WGL_CONTEXT_MINOR_VERSION_ARB);
		attribs.push_back(version.minor);

		if (profileMask != 0)
		{
			attribs.push_back(WGL_CONTEXT_PROFILE_MASK_ARB);
			attribs.push_back(profileMask);
		}

		attribs.push_back(0);
		attribs.push_back(0);

		return mFunctionsWGL->createContextAttribsARB(mDeviceContext, nullptr, &attribs[0]);
	}
};
