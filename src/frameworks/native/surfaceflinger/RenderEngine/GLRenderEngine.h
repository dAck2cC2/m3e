#ifndef SF_GLRENDERENGINE_H_
#define SF_GLRENDERENGINE_H_

#include <stdint.h>
#include <sys/types.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "RenderEngine.h"

// ---------------------------------------------------------------------------
namespace android {
// ---------------------------------------------------------------------------

	class GLRenderEngine : public RenderEngine 
	{
		virtual void bindImageAsFramebuffer(EGLImageKHR image,
			uint32_t* texName, uint32_t* fbName, uint32_t* status);
		virtual void unbindFramebuffer(uint32_t texName, uint32_t fbName);

	public:
		GLRenderEngine();

	protected:
		virtual ~GLRenderEngine();

		virtual void setViewportAndProjection(size_t vpw, size_t vph,
			Rect sourceCrop, size_t hwh, bool yswap,
			Transform::orientation_flags rotation);
#ifdef USE_HWC2
		virtual void setupLayerBlending(bool premultipliedAlpha, bool opaque,
			float alpha) override;
		virtual void setupDimLayerBlending(float alpha) override;
#else
		virtual void setupLayerBlending(bool premultipliedAlpha, bool opaque,
			int alpha);
		virtual void setupDimLayerBlending(int alpha);
#endif
		virtual void setupLayerTexturing(const Texture& texture);
		virtual void setupLayerBlackedOut();
		virtual void setupFillWithColor(float r, float g, float b, float a);
		virtual mat4 setupColorTransform(const mat4& colorTransform);
		virtual void disableTexturing();
		virtual void disableBlending();

		virtual void drawMesh(const Mesh& mesh);

		virtual size_t getMaxTextureSize() const;
		virtual size_t getMaxViewportDims() const;
	};

// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------

#endif // SF_GLRENDERENGINE_H_
