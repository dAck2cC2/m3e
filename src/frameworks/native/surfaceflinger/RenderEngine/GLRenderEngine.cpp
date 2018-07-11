
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "GLRenderEngine.h"
#include "Mesh.h"
#include "Texture.h"

// ---------------------------------------------------------------------------
namespace android {
// ---------------------------------------------------------------------------

	GLRenderEngine::GLRenderEngine()
	{
	};

	GLRenderEngine::~GLRenderEngine()
	{
	};

	void GLRenderEngine::bindImageAsFramebuffer(EGLImageKHR image,
		uint32_t* texName, uint32_t* fbName, uint32_t* status)
	{
	};

	void GLRenderEngine::unbindFramebuffer(uint32_t texName, uint32_t fbName)
	{
	};

	void GLRenderEngine::setViewportAndProjection(size_t vpw, size_t vph,
		Rect sourceCrop, size_t hwh, bool yswap,
		Transform::orientation_flags rotation)
	{
	};

	void GLRenderEngine::setupLayerBlending(bool premultipliedAlpha, bool opaque,
		int alpha)
	{
	};

	void GLRenderEngine::setupDimLayerBlending(int alpha)
	{
	};

	 void GLRenderEngine::setupLayerTexturing(const Texture& texture)
	 {
	 };
 
	 void GLRenderEngine::setupLayerBlackedOut()
	 {
	 };

	 void GLRenderEngine::setupFillWithColor(float r, float g, float b, float a)
	 {
	 };

	 mat4 GLRenderEngine::setupColorTransform(const mat4& colorTransform)
	 {
		 mat4 oldTransform;
		 return oldTransform;
	 };

	 void GLRenderEngine::disableTexturing()
	 {
	 };

	 void GLRenderEngine::disableBlending()
	 {
	 };

	 void GLRenderEngine::drawMesh(const Mesh& mesh)
	 {
	 };

	 size_t GLRenderEngine::getMaxTextureSize() const
	 {
		 return 0;
	 };

	 size_t GLRenderEngine::getMaxViewportDims() const
	 {
		 return 0;
	 };

// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------
