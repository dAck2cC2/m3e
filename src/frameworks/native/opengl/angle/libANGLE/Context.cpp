
#include "libANGLE/Context.h"
#include "libANGLE/Surface.h"
#include "libANGLE/Error.h"

namespace gl
{

	Context::Context(rx::EGLImplFactory *implFactory,
		const egl::Config *config,
		const Context *shareContext,
		TextureManager *shareTextures,
		MemoryProgramCache *memoryProgramCache,
		const egl::AttributeMap &attribs,
		const egl::DisplayExtensions &displayExtensions)
		:
		mCurrentSurface(static_cast<egl::Surface *>(EGL_NO_SURFACE)),
		mCurrentDisplay(static_cast<egl::Display *>(EGL_NO_DISPLAY))
	{

	}

	Context::~Context()
	{

	}

	egl::Error Context::makeCurrent(egl::Display *display, egl::Surface *surface)
	{
		mCurrentDisplay = display;

		if (surface != nullptr)
		{
			ANGLE_TRY(surface->setIsCurrent(this, true));
			mCurrentSurface = surface;
		}

		return egl::NoError();
	}

	egl::Error Context::releaseSurface(const egl::Display *display)
	{
		if (mCurrentSurface)
		{
			ANGLE_TRY(mCurrentSurface->setIsCurrent(this, false));
			mCurrentSurface = nullptr;
		}

		return egl::NoError();
	}
}  // namespace gl
