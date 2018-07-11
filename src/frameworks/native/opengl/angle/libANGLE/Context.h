#ifndef LIBANGLE_CONTEXT_H_
#define LIBANGLE_CONTEXT_H_

#include "common/angleutils.h"
#include "libANGLE/Caps.h"

namespace rx
{
	class ContextImpl;
	class EGLImplFactory;
}

namespace egl
{
	class AttributeMap;
	class Surface;
	struct Config;
	class Thread;
	class Display;
}

namespace gl
{

	class TextureManager;
	class MemoryProgramCache;

class Context final : angle::NonCopyable
{
public:
	Context(rx::EGLImplFactory *implFactory,
		const egl::Config *config,
		const Context *shareContext,
		TextureManager *shareTextures,
		MemoryProgramCache *memoryProgramCache,
		const egl::AttributeMap &attribs,
		const egl::DisplayExtensions &displayExtensions);
	~Context();

	egl::Error makeCurrent(egl::Display *display, egl::Surface *surface);
	egl::Error releaseSurface(const egl::Display *display);

	egl::Display *getCurrentDisplay() const { return mCurrentDisplay; }
	egl::Surface *getCurrentDrawSurface() const { return mCurrentSurface; }
	egl::Surface *getCurrentReadSurface() const { return mCurrentSurface; }

private:
	egl::Surface *mCurrentSurface;
	egl::Display *mCurrentDisplay;
};

}  // namespace gl

#endif // LIBANGLE_CONTEXT_H_