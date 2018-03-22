#ifndef _MSC_VER // [
#error "Use this header only with Microsoft Visual C++ compilers!"
#endif // _MSC_VER ]

#include "libANGLE/renderer/Format.h"

#include "image_util/copyimage.h"
#include "image_util/generatemip.h"
#include "image_util/loadimage.h"

namespace angle
{

static constexpr rx::FastCopyFunctionMap::Entry BGRAEntry = {GL_RGBA, GL_UNSIGNED_BYTE,
                                                             CopyBGRA8ToRGBA8};
static constexpr rx::FastCopyFunctionMap BGRACopyFunctions = {&BGRAEntry, 1};
static constexpr rx::FastCopyFunctionMap NoCopyFunctions;

inline void GenerateMip_A16F(size_t sourceWidth, size_t sourceHeight, size_t sourceDepth,
	const uint8_t *sourceData, size_t sourceRowPitch, size_t sourceDepthPitch,
	uint8_t *destData, size_t destRowPitch, size_t destDepthPitch) {
	return GenerateMip<A16F>(sourceWidth, sourceHeight, sourceDepth,
		sourceData,  sourceRowPitch,  sourceDepthPitch,
		 destData,  destRowPitch,  destDepthPitch);
}

constexpr Format g_formatInfoTable[] = {
    // clang-format off
    { Format::ID::NONE, GL_NONE, GL_NONE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_NONE, 0, 0, 0, 0, 0, 0 },
};

#if 0
constexpr Format g_formatInfoTable[] = {
    // clang-format off
    { Format::ID::NONE, GL_NONE, GL_NONE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_NONE, 0, 0, 0, 0, 0, 0 },
    { Format::ID::A16_FLOAT, GL_ALPHA16F_EXT, GL_ALPHA16F_EXT, GenerateMip_A16F, NoCopyFunctions, ReadColor<A16F, GLfloat>, WriteColor<A16F, GLfloat>, GL_FLOAT, 0, 0, 0, 16, 0, 0 },
    { Format::ID::A1R5G5B5_UNORM, GL_A1RGB5_ANGLEX, GL_A1RGB5_ANGLEX, GenerateMip<A1R5G5B5>, NoCopyFunctions, ReadColor<A1R5G5B5, GLfloat>, WriteColor<A1R5G5B5, GLfloat>, GL_UNSIGNED_NORMALIZED, 5, 5, 5, 1, 0, 0 },
    { Format::ID::A32_FLOAT, GL_ALPHA32F_EXT, GL_ALPHA32F_EXT, GenerateMip<A32F>, NoCopyFunctions, ReadColor<A32F, GLfloat>, WriteColor<A32F, GLfloat>, GL_FLOAT, 0, 0, 0, 32, 0, 0 },
    { Format::ID::A8_UNORM, GL_ALPHA8_EXT, GL_ALPHA8_EXT, GenerateMip<A8>, NoCopyFunctions, ReadColor<A8, GLfloat>, WriteColor<A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 8, 0, 0 },
    { Format::ID::ASTC_10x10_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x10_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_10x10_KHR, GL_COMPRESSED_RGBA_ASTC_10x10_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x5_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x5_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_10x5_KHR, GL_COMPRESSED_RGBA_ASTC_10x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x6_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x6_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_10x6_KHR, GL_COMPRESSED_RGBA_ASTC_10x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x8_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_10x8_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_10x8_KHR, GL_COMPRESSED_RGBA_ASTC_10x8_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_12x10_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_12x10_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_12x10_KHR, GL_COMPRESSED_RGBA_ASTC_12x10_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_12x12_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_12x12_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_12x12_KHR, GL_COMPRESSED_RGBA_ASTC_12x12_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_4x4_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_4x4_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_4x4_KHR, GL_COMPRESSED_RGBA_ASTC_4x4_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_5x4_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_5x4_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_5x4_KHR, GL_COMPRESSED_RGBA_ASTC_5x4_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_5x5_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_5x5_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_5x5_KHR, GL_COMPRESSED_RGBA_ASTC_5x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_6x5_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_6x5_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_6x5_KHR, GL_COMPRESSED_RGBA_ASTC_6x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_6x6_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_6x6_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_6x6_KHR, GL_COMPRESSED_RGBA_ASTC_6x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x5_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x5_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_8x5_KHR, GL_COMPRESSED_RGBA_ASTC_8x5_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x6_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x6_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_8x6_KHR, GL_COMPRESSED_RGBA_ASTC_8x6_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x8_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::ASTC_8x8_UNORM_BLOCK, GL_COMPRESSED_RGBA_ASTC_8x8_KHR, GL_COMPRESSED_RGBA_ASTC_8x8_KHR, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::B4G4R4A4_UNORM, GL_BGRA4_ANGLEX, GL_RGBA4, GenerateMip<A4R4G4B4>, NoCopyFunctions, ReadColor<A4R4G4B4, GLfloat>, WriteColor<A4R4G4B4, GLfloat>, GL_UNSIGNED_NORMALIZED, 4, 4, 4, 4, 0, 0 },
    { Format::ID::B5G5R5A1_UNORM, GL_BGR5_A1_ANGLEX, GL_RGB5_A1, GenerateMip<A1R5G5B5>, NoCopyFunctions, ReadColor<A1R5G5B5, GLfloat>, WriteColor<A1R5G5B5, GLfloat>, GL_UNSIGNED_NORMALIZED, 5, 5, 5, 1, 0, 0 },
    { Format::ID::B5G6R5_UNORM, GL_BGR565_ANGLEX, GL_RGB565, GenerateMip<B5G6R5>, NoCopyFunctions, ReadColor<B5G6R5, GLfloat>, WriteColor<B5G6R5, GLfloat>, GL_UNSIGNED_NORMALIZED, 5, 6, 5, 0, 0, 0 },
    { Format::ID::B8G8R8A8_TYPELESS, GL_BGRA8_EXT, GL_BGRA8_EXT, GenerateMip<B8G8R8A8>, NoCopyFunctions, ReadColor<B8G8R8A8, GLfloat>, WriteColor<B8G8R8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::B8G8R8A8_TYPELESS_SRGB, GL_BGRA8_SRGB_ANGLEX, GL_BGRA8_SRGB_ANGLEX, GenerateMip<B8G8R8A8>, NoCopyFunctions, ReadColor<B8G8R8A8, GLfloat>, WriteColor<B8G8R8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::B8G8R8A8_UNORM, GL_BGRA8_EXT, GL_BGRA8_EXT, GenerateMip<B8G8R8A8>, BGRACopyFunctions, ReadColor<B8G8R8A8, GLfloat>, WriteColor<B8G8R8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::B8G8R8A8_UNORM_SRGB, GL_BGRA8_SRGB_ANGLEX, GL_BGRA8_SRGB_ANGLEX, GenerateMip<B8G8R8A8>, NoCopyFunctions, ReadColor<B8G8R8A8, GLfloat>, WriteColor<B8G8R8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::B8G8R8X8_UNORM, GL_BGRA8_EXT, GL_BGRA8_EXT, GenerateMip<B8G8R8X8>, NoCopyFunctions, ReadColor<B8G8R8X8, GLfloat>, WriteColor<B8G8R8X8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::BC1_RGBA_UNORM_BLOCK, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC1_RGBA_UNORM_SRGB_BLOCK, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC1_RGB_UNORM_BLOCK, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC1_RGB_UNORM_SRGB_BLOCK, GL_COMPRESSED_SRGB_S3TC_DXT1_EXT, GL_COMPRESSED_SRGB_S3TC_DXT1_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC2_RGBA_UNORM_BLOCK, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC2_RGBA_UNORM_SRGB_BLOCK, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC3_RGBA_UNORM_BLOCK, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::BC3_RGBA_UNORM_SRGB_BLOCK, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::D16_UNORM, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT16, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 16, 0 },
    { Format::ID::D24_UNORM, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT24, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 24, 0 },
    { Format::ID::D24_UNORM_S8_UINT, GL_DEPTH24_STENCIL8, GL_DEPTH24_STENCIL8, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 24, 8 },
    { Format::ID::D32_FLOAT, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT32F, nullptr, NoCopyFunctions, nullptr, nullptr, GL_FLOAT, 0, 0, 0, 0, 32, 0 },
    { Format::ID::D32_FLOAT_S8X24_UINT, GL_DEPTH32F_STENCIL8, GL_DEPTH32F_STENCIL8, nullptr, NoCopyFunctions, nullptr, nullptr, GL_FLOAT, 0, 0, 0, 0, 32, 8 },
    { Format::ID::D32_UNORM, GL_DEPTH_COMPONENT32_OES, GL_DEPTH_COMPONENT32_OES, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 32, 0 },
    { Format::ID::EAC_R11G11_SNORM_BLOCK, GL_COMPRESSED_SIGNED_RG11_EAC, GL_COMPRESSED_SIGNED_RG11_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_SIGNED_NORMALIZED, 11, 11, 0, 0, 0, 0 },
    { Format::ID::EAC_R11G11_UNORM_BLOCK, GL_COMPRESSED_RG11_EAC, GL_COMPRESSED_RG11_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 11, 11, 0, 0, 0, 0 },
    { Format::ID::EAC_R11_SNORM_BLOCK, GL_COMPRESSED_SIGNED_R11_EAC, GL_COMPRESSED_SIGNED_R11_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_SIGNED_NORMALIZED, 11, 0, 0, 0, 0, 0 },
    { Format::ID::EAC_R11_UNORM_BLOCK, GL_COMPRESSED_R11_EAC, GL_COMPRESSED_R11_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 11, 0, 0, 0, 0, 0 },
    { Format::ID::ETC1_LOSSY_DECODE_R8G8B8_UNORM_BLOCK, GL_ETC1_RGB8_LOSSY_DECODE_ANGLE, GL_ETC1_RGB8_LOSSY_DECODE_ANGLE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::ETC1_R8G8B8_UNORM_BLOCK, GL_ETC1_RGB8_OES, GL_ETC1_RGB8_OES, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::ETC2_R8G8B8A1_SRGB_BLOCK, GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 1, 0, 0 },
    { Format::ID::ETC2_R8G8B8A1_UNORM_BLOCK, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 1, 0, 0 },
    { Format::ID::ETC2_R8G8B8A8_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::ETC2_R8G8B8A8_UNORM_BLOCK, GL_COMPRESSED_RGBA8_ETC2_EAC, GL_COMPRESSED_RGBA8_ETC2_EAC, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::ETC2_R8G8B8_SRGB_BLOCK, GL_COMPRESSED_SRGB8_ETC2, GL_COMPRESSED_SRGB8_ETC2, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::ETC2_R8G8B8_UNORM_BLOCK, GL_COMPRESSED_RGB8_ETC2, GL_COMPRESSED_RGB8_ETC2, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::L16A16_FLOAT, GL_LUMINANCE_ALPHA16F_EXT, GL_LUMINANCE_ALPHA16F_EXT, GenerateMip<L16A16F>, NoCopyFunctions, ReadColor<L16A16F, GLfloat>, WriteColor<L16A16F, GLfloat>, GL_FLOAT, 0, 0, 0, 16, 0, 0 },
    { Format::ID::L16_FLOAT, GL_LUMINANCE16F_EXT, GL_LUMINANCE16F_EXT, GenerateMip<L16F>, NoCopyFunctions, ReadColor<L16F, GLfloat>, WriteColor<L16F, GLfloat>, GL_FLOAT, 0, 0, 0, 0, 0, 0 },
    { Format::ID::L32A32_FLOAT, GL_LUMINANCE_ALPHA32F_EXT, GL_LUMINANCE_ALPHA32F_EXT, GenerateMip<L32A32F>, NoCopyFunctions, ReadColor<L32A32F, GLfloat>, WriteColor<L32A32F, GLfloat>, GL_FLOAT, 0, 0, 0, 32, 0, 0 },
    { Format::ID::L32_FLOAT, GL_LUMINANCE32F_EXT, GL_LUMINANCE32F_EXT, GenerateMip<L32F>, NoCopyFunctions, ReadColor<L32F, GLfloat>, WriteColor<L32F, GLfloat>, GL_FLOAT, 0, 0, 0, 0, 0, 0 },
    { Format::ID::L8A8_UNORM, GL_LUMINANCE8_ALPHA8_EXT, GL_LUMINANCE8_ALPHA8_EXT, GenerateMip<L8A8>, NoCopyFunctions, ReadColor<L8A8, GLfloat>, WriteColor<L8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 8, 0, 0 },
    { Format::ID::L8_UNORM, GL_LUMINANCE8_EXT, GL_LUMINANCE8_EXT, GenerateMip<L8>, NoCopyFunctions, ReadColor<L8, GLfloat>, WriteColor<L8, GLfloat>, GL_UNSIGNED_NORMALIZED, 0, 0, 0, 0, 0, 0 },
    { Format::ID::R10G10B10A2_UINT, GL_RGB10_A2UI, GL_RGB10_A2UI, GenerateMip<R10G10B10A2>, NoCopyFunctions, ReadColor<R10G10B10A2, GLuint>, WriteColor<R10G10B10A2, GLuint>, GL_UNSIGNED_INT, 10, 10, 10, 2, 0, 0 },
    { Format::ID::R10G10B10A2_UNORM, GL_RGB10_A2, GL_RGB10_A2, GenerateMip<R10G10B10A2>, NoCopyFunctions, ReadColor<R10G10B10A2, GLfloat>, WriteColor<R10G10B10A2, GLfloat>, GL_UNSIGNED_NORMALIZED, 10, 10, 10, 2, 0, 0 },
    { Format::ID::R11G11B10_FLOAT, GL_R11F_G11F_B10F, GL_R11F_G11F_B10F, GenerateMip<R11G11B10F>, NoCopyFunctions, ReadColor<R11G11B10F, GLfloat>, WriteColor<R11G11B10F, GLfloat>, GL_FLOAT, 11, 11, 10, 0, 0, 0 },
    { Format::ID::R16G16B16A16_FLOAT, GL_RGBA16F, GL_RGBA16F, GenerateMip<R16G16B16A16F>, NoCopyFunctions, ReadColor<R16G16B16A16F, GLfloat>, WriteColor<R16G16B16A16F, GLfloat>, GL_FLOAT, 16, 16, 16, 16, 0, 0 },
    { Format::ID::R16G16B16A16_SINT, GL_RGBA16I, GL_RGBA16I, GenerateMip<R16G16B16A16S>, NoCopyFunctions, ReadColor<R16G16B16A16S, GLint>, WriteColor<R16G16B16A16S, GLint>, GL_INT, 16, 16, 16, 16, 0, 0 },
    { Format::ID::R16G16B16A16_SNORM, GL_RGBA16_SNORM_EXT, GL_RGBA16_SNORM_EXT, GenerateMip<R16G16B16A16S>, NoCopyFunctions, ReadColor<R16G16B16A16S, GLfloat>, WriteColor<R16G16B16A16S, GLfloat>, GL_SIGNED_NORMALIZED, 16, 16, 16, 16, 0, 0 },
    { Format::ID::R16G16B16A16_UINT, GL_RGBA16UI, GL_RGBA16UI, GenerateMip<R16G16B16A16>, NoCopyFunctions, ReadColor<R16G16B16A16, GLuint>, WriteColor<R16G16B16A16, GLuint>, GL_UNSIGNED_INT, 16, 16, 16, 16, 0, 0 },
    { Format::ID::R16G16B16A16_UNORM, GL_RGBA16_EXT, GL_RGBA16_EXT, GenerateMip<R16G16B16A16>, NoCopyFunctions, ReadColor<R16G16B16A16, GLfloat>, WriteColor<R16G16B16A16, GLfloat>, GL_UNSIGNED_NORMALIZED, 16, 16, 16, 16, 0, 0 },
    { Format::ID::R16G16B16_FLOAT, GL_RGB16F, GL_RGB16F, GenerateMip<R16G16B16F>, NoCopyFunctions, ReadColor<R16G16B16F, GLfloat>, WriteColor<R16G16B16F, GLfloat>, GL_FLOAT, 16, 16, 16, 0, 0, 0 },
    { Format::ID::R16G16B16_SINT, GL_RGB16I, GL_RGB16I, GenerateMip<R16G16B16S>, NoCopyFunctions, ReadColor<R16G16B16S, GLint>, WriteColor<R16G16B16S, GLint>, GL_INT, 16, 16, 16, 0, 0, 0 },
    { Format::ID::R16G16B16_SNORM, GL_RGB16_SNORM_EXT, GL_RGB16_SNORM_EXT, GenerateMip<R16G16B16S>, NoCopyFunctions, ReadColor<R16G16B16S, GLfloat>, WriteColor<R16G16B16S, GLfloat>, GL_SIGNED_NORMALIZED, 16, 16, 16, 0, 0, 0 },
    { Format::ID::R16G16B16_UINT, GL_RGB16UI, GL_RGB16UI, GenerateMip<R16G16B16>, NoCopyFunctions, ReadColor<R16G16B16, GLuint>, WriteColor<R16G16B16, GLuint>, GL_UNSIGNED_INT, 16, 16, 16, 0, 0, 0 },
    { Format::ID::R16G16B16_UNORM, GL_RGB16_EXT, GL_RGB16_EXT, GenerateMip<R16G16B16>, NoCopyFunctions, ReadColor<R16G16B16, GLfloat>, WriteColor<R16G16B16, GLfloat>, GL_UNSIGNED_NORMALIZED, 16, 16, 16, 0, 0, 0 },
    { Format::ID::R16G16_FLOAT, GL_RG16F, GL_RG16F, GenerateMip<R16G16F>, NoCopyFunctions, ReadColor<R16G16F, GLfloat>, WriteColor<R16G16F, GLfloat>, GL_FLOAT, 16, 16, 0, 0, 0, 0 },
    { Format::ID::R16G16_SINT, GL_RG16I, GL_RG16I, GenerateMip<R16G16S>, NoCopyFunctions, ReadColor<R16G16S, GLint>, WriteColor<R16G16S, GLint>, GL_INT, 16, 16, 0, 0, 0, 0 },
    { Format::ID::R16G16_SNORM, GL_RG16_SNORM_EXT, GL_RG16_SNORM_EXT, GenerateMip<R16G16S>, NoCopyFunctions, ReadColor<R16G16S, GLfloat>, WriteColor<R16G16S, GLfloat>, GL_SIGNED_NORMALIZED, 16, 16, 0, 0, 0, 0 },
    { Format::ID::R16G16_UINT, GL_RG16UI, GL_RG16UI, GenerateMip<R16G16>, NoCopyFunctions, ReadColor<R16G16, GLuint>, WriteColor<R16G16, GLuint>, GL_UNSIGNED_INT, 16, 16, 0, 0, 0, 0 },
    { Format::ID::R16G16_UNORM, GL_RG16_EXT, GL_RG16_EXT, GenerateMip<R16G16>, NoCopyFunctions, ReadColor<R16G16, GLfloat>, WriteColor<R16G16, GLfloat>, GL_UNSIGNED_NORMALIZED, 16, 16, 0, 0, 0, 0 },
    { Format::ID::R16_FLOAT, GL_R16F, GL_R16F, GenerateMip<R16F>, NoCopyFunctions, ReadColor<R16F, GLfloat>, WriteColor<R16F, GLfloat>, GL_FLOAT, 16, 0, 0, 0, 0, 0 },
    { Format::ID::R16_SINT, GL_R16I, GL_R16I, GenerateMip<R16S>, NoCopyFunctions, ReadColor<R16S, GLint>, WriteColor<R16S, GLint>, GL_INT, 16, 0, 0, 0, 0, 0 },
    { Format::ID::R16_SNORM, GL_R16_SNORM_EXT, GL_R16_SNORM_EXT, GenerateMip<R16S>, NoCopyFunctions, ReadColor<R16S, GLfloat>, WriteColor<R16S, GLfloat>, GL_SIGNED_NORMALIZED, 16, 0, 0, 0, 0, 0 },
    { Format::ID::R16_UINT, GL_R16UI, GL_R16UI, GenerateMip<R16>, NoCopyFunctions, ReadColor<R16, GLuint>, WriteColor<R16, GLuint>, GL_UNSIGNED_INT, 16, 0, 0, 0, 0, 0 },
    { Format::ID::R16_UNORM, GL_R16_EXT, GL_R16_EXT, GenerateMip<R16>, NoCopyFunctions, ReadColor<R16, GLfloat>, WriteColor<R16, GLfloat>, GL_UNSIGNED_NORMALIZED, 16, 0, 0, 0, 0, 0 },
    { Format::ID::R32G32B32A32_FLOAT, GL_RGBA32F, GL_RGBA32F, GenerateMip<R32G32B32A32F>, NoCopyFunctions, ReadColor<R32G32B32A32F, GLfloat>, WriteColor<R32G32B32A32F, GLfloat>, GL_FLOAT, 32, 32, 32, 32, 0, 0 },
    { Format::ID::R32G32B32A32_SINT, GL_RGBA32I, GL_RGBA32I, GenerateMip<R32G32B32A32S>, NoCopyFunctions, ReadColor<R32G32B32A32S, GLint>, WriteColor<R32G32B32A32S, GLint>, GL_INT, 32, 32, 32, 32, 0, 0 },
    { Format::ID::R32G32B32A32_UINT, GL_RGBA32UI, GL_RGBA32UI, GenerateMip<R32G32B32A32>, NoCopyFunctions, ReadColor<R32G32B32A32, GLuint>, WriteColor<R32G32B32A32, GLuint>, GL_UNSIGNED_INT, 32, 32, 32, 32, 0, 0 },
    { Format::ID::R32G32B32_FLOAT, GL_RGB32F, GL_RGB32F, GenerateMip<R32G32B32F>, NoCopyFunctions, ReadColor<R32G32B32F, GLfloat>, WriteColor<R32G32B32F, GLfloat>, GL_FLOAT, 32, 32, 32, 0, 0, 0 },
    { Format::ID::R32G32B32_SINT, GL_RGB32I, GL_RGB32I, GenerateMip<R32G32B32S>, NoCopyFunctions, ReadColor<R32G32B32S, GLint>, WriteColor<R32G32B32S, GLint>, GL_INT, 32, 32, 32, 0, 0, 0 },
    { Format::ID::R32G32B32_UINT, GL_RGB32UI, GL_RGB32UI, GenerateMip<R32G32B32>, NoCopyFunctions, ReadColor<R32G32B32, GLuint>, WriteColor<R32G32B32, GLuint>, GL_UNSIGNED_INT, 32, 32, 32, 0, 0, 0 },
    { Format::ID::R32G32_FLOAT, GL_RG32F, GL_RG32F, GenerateMip<R32G32F>, NoCopyFunctions, ReadColor<R32G32F, GLfloat>, WriteColor<R32G32F, GLfloat>, GL_FLOAT, 32, 32, 0, 0, 0, 0 },
    { Format::ID::R32G32_SINT, GL_RG32I, GL_RG32I, GenerateMip<R32G32S>, NoCopyFunctions, ReadColor<R32G32S, GLint>, WriteColor<R32G32S, GLint>, GL_INT, 32, 32, 0, 0, 0, 0 },
    { Format::ID::R32G32_UINT, GL_RG32UI, GL_RG32UI, GenerateMip<R32G32>, NoCopyFunctions, ReadColor<R32G32, GLuint>, WriteColor<R32G32, GLuint>, GL_UNSIGNED_INT, 32, 32, 0, 0, 0, 0 },
    { Format::ID::R32_FLOAT, GL_R32F, GL_R32F, GenerateMip<R32F>, NoCopyFunctions, ReadColor<R32F, GLfloat>, WriteColor<R32F, GLfloat>, GL_FLOAT, 32, 0, 0, 0, 0, 0 },
    { Format::ID::R32_SINT, GL_R32I, GL_R32I, GenerateMip<R32S>, NoCopyFunctions, ReadColor<R32S, GLint>, WriteColor<R32S, GLint>, GL_INT, 32, 0, 0, 0, 0, 0 },
    { Format::ID::R32_UINT, GL_R32UI, GL_R32UI, GenerateMip<R32>, NoCopyFunctions, ReadColor<R32, GLuint>, WriteColor<R32, GLuint>, GL_UNSIGNED_INT, 32, 0, 0, 0, 0, 0 },
    { Format::ID::R4G4B4A4_UNORM, GL_RGBA4, GL_RGBA4, GenerateMip<R4G4B4A4>, NoCopyFunctions, ReadColor<R4G4B4A4, GLfloat>, WriteColor<R4G4B4A4, GLfloat>, GL_UNSIGNED_NORMALIZED, 4, 4, 4, 4, 0, 0 },
    { Format::ID::R5G5B5A1_UNORM, GL_RGB5_A1, GL_RGB5_A1, GenerateMip<R5G5B5A1>, NoCopyFunctions, ReadColor<R5G5B5A1, GLfloat>, WriteColor<R5G5B5A1, GLfloat>, GL_UNSIGNED_NORMALIZED, 5, 5, 5, 1, 0, 0 },
    { Format::ID::R5G6B5_UNORM, GL_RGB565, GL_RGB565, GenerateMip<R5G6B5>, NoCopyFunctions, ReadColor<R5G6B5, GLfloat>, WriteColor<R5G6B5, GLfloat>, GL_UNSIGNED_NORMALIZED, 5, 6, 5, 0, 0, 0 },
    { Format::ID::R8G8B8A8_SINT, GL_RGBA8I, GL_RGBA8I, GenerateMip<R8G8B8A8S>, NoCopyFunctions, ReadColor<R8G8B8A8S, GLint>, WriteColor<R8G8B8A8S, GLint>, GL_INT, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_SNORM, GL_RGBA8_SNORM, GL_RGBA8_SNORM, GenerateMip<R8G8B8A8S>, NoCopyFunctions, ReadColor<R8G8B8A8S, GLfloat>, WriteColor<R8G8B8A8S, GLfloat>, GL_SIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_TYPELESS, GL_RGBA8, GL_RGBA8, GenerateMip<R8G8B8A8>, NoCopyFunctions, ReadColor<R8G8B8A8, GLfloat>, WriteColor<R8G8B8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_TYPELESS_SRGB, GL_SRGB8_ALPHA8, GL_SRGB8_ALPHA8, GenerateMip<R8G8B8A8>, NoCopyFunctions, ReadColor<R8G8B8A8, GLfloat>, WriteColor<R8G8B8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_UINT, GL_RGBA8UI, GL_RGBA8UI, GenerateMip<R8G8B8A8>, NoCopyFunctions, ReadColor<R8G8B8A8, GLuint>, WriteColor<R8G8B8A8, GLuint>, GL_UNSIGNED_INT, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_UNORM, GL_RGBA8, GL_RGBA8, GenerateMip<R8G8B8A8>, NoCopyFunctions, ReadColor<R8G8B8A8, GLfloat>, WriteColor<R8G8B8A8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8A8_UNORM_SRGB, GL_SRGB8_ALPHA8, GL_SRGB8_ALPHA8, GenerateMip<R8G8B8A8SRGB>, NoCopyFunctions, ReadColor<R8G8B8A8SRGB, GLfloat>, WriteColor<R8G8B8A8SRGB, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 8, 0, 0 },
    { Format::ID::R8G8B8_SINT, GL_RGB8I, GL_RGB8I, GenerateMip<R8G8B8S>, NoCopyFunctions, ReadColor<R8G8B8S, GLint>, WriteColor<R8G8B8S, GLint>, GL_INT, 8, 8, 8, 0, 0, 0 },
    { Format::ID::R8G8B8_SNORM, GL_RGB8_SNORM, GL_RGB8_SNORM, GenerateMip<R8G8B8S>, NoCopyFunctions, ReadColor<R8G8B8S, GLfloat>, WriteColor<R8G8B8S, GLfloat>, GL_SIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::R8G8B8_UINT, GL_RGB8UI, GL_RGB8UI, GenerateMip<R8G8B8>, NoCopyFunctions, ReadColor<R8G8B8, GLuint>, WriteColor<R8G8B8, GLuint>, GL_UNSIGNED_INT, 8, 8, 8, 0, 0, 0 },
    { Format::ID::R8G8B8_UNORM, GL_RGB8, GL_RGB8, GenerateMip<R8G8B8>, NoCopyFunctions, ReadColor<R8G8B8, GLfloat>, WriteColor<R8G8B8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::R8G8B8_UNORM_SRGB, GL_SRGB8, GL_SRGB8, GenerateMip<R8G8B8>, NoCopyFunctions, ReadColor<R8G8B8, GLfloat>, WriteColor<R8G8B8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 8, 0, 0, 0 },
    { Format::ID::R8G8_SINT, GL_RG8I, GL_RG8I, GenerateMip<R8G8S>, NoCopyFunctions, ReadColor<R8G8S, GLint>, WriteColor<R8G8S, GLint>, GL_INT, 8, 8, 0, 0, 0, 0 },
    { Format::ID::R8G8_SNORM, GL_RG8_SNORM, GL_RG8_SNORM, GenerateMip<R8G8S>, NoCopyFunctions, ReadColor<R8G8S, GLfloat>, WriteColor<R8G8S, GLfloat>, GL_SIGNED_NORMALIZED, 8, 8, 0, 0, 0, 0 },
    { Format::ID::R8G8_UINT, GL_RG8UI, GL_RG8UI, GenerateMip<R8G8>, NoCopyFunctions, ReadColor<R8G8, GLuint>, WriteColor<R8G8, GLuint>, GL_UNSIGNED_INT, 8, 8, 0, 0, 0, 0 },
    { Format::ID::R8G8_UNORM, GL_RG8, GL_RG8, GenerateMip<R8G8>, NoCopyFunctions, ReadColor<R8G8, GLfloat>, WriteColor<R8G8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 8, 0, 0, 0, 0 },
    { Format::ID::R8_SINT, GL_R8I, GL_R8I, GenerateMip<R8S>, NoCopyFunctions, ReadColor<R8S, GLint>, WriteColor<R8S, GLint>, GL_INT, 8, 0, 0, 0, 0, 0 },
    { Format::ID::R8_SNORM, GL_R8_SNORM, GL_R8_SNORM, GenerateMip<R8S>, NoCopyFunctions, ReadColor<R8S, GLfloat>, WriteColor<R8S, GLfloat>, GL_SIGNED_NORMALIZED, 8, 0, 0, 0, 0, 0 },
    { Format::ID::R8_UINT, GL_R8UI, GL_R8UI, GenerateMip<R8>, NoCopyFunctions, ReadColor<R8, GLuint>, WriteColor<R8, GLuint>, GL_UNSIGNED_INT, 8, 0, 0, 0, 0, 0 },
    { Format::ID::R8_UNORM, GL_R8, GL_R8, GenerateMip<R8>, NoCopyFunctions, ReadColor<R8, GLfloat>, WriteColor<R8, GLfloat>, GL_UNSIGNED_NORMALIZED, 8, 0, 0, 0, 0, 0 },
    { Format::ID::R9G9B9E5_SHAREDEXP, GL_RGB9_E5, GL_RGB9_E5, GenerateMip<R9G9B9E5>, NoCopyFunctions, ReadColor<R9G9B9E5, GLfloat>, WriteColor<R9G9B9E5, GLfloat>, GL_FLOAT, 9, 9, 9, 0, 0, 0 },
    { Format::ID::S8_UINT, GL_STENCIL_INDEX8, GL_STENCIL_INDEX8, nullptr, NoCopyFunctions, nullptr, nullptr, GL_UNSIGNED_INT, 0, 0, 0, 0, 0, 8 },
    // clang-format on
};
#endif

// static
Format::ID Format::InternalFormatToID(GLenum internalFormat)
{
    switch (internalFormat)
    {
        case GL_A1RGB5_ANGLEX:
            return Format::ID::A1R5G5B5_UNORM;
        case GL_ALPHA16F_EXT:
            return Format::ID::A16_FLOAT;
        case GL_ALPHA32F_EXT:
            return Format::ID::A32_FLOAT;
        case GL_ALPHA8_EXT:
            return Format::ID::A8_UNORM;
        case GL_BGR565_ANGLEX:
            return Format::ID::B5G6R5_UNORM;
        case GL_BGR5_A1_ANGLEX:
            return Format::ID::B5G5R5A1_UNORM;
        case GL_BGRA4_ANGLEX:
            return Format::ID::B4G4R4A4_UNORM;
        case GL_BGRA8_EXT:
            return Format::ID::B8G8R8A8_UNORM;
        case GL_BGRA8_SRGB_ANGLEX:
            return Format::ID::B8G8R8A8_UNORM_SRGB;
        case GL_BGRA8_TYPELESS_ANGLEX:
            return Format::ID::B8G8R8A8_TYPELESS;
        case GL_BGRA8_TYPELESS_SRGB_ANGLEX:
            return Format::ID::B8G8R8A8_TYPELESS_SRGB;
        case GL_BGRX8_ANGLEX:
            return Format::ID::B8G8R8X8_UNORM;
        case GL_COMPRESSED_R11_EAC:
            return Format::ID::EAC_R11_UNORM_BLOCK;
        case GL_COMPRESSED_RG11_EAC:
            return Format::ID::EAC_R11G11_UNORM_BLOCK;
        case GL_COMPRESSED_RGB8_ETC2:
            return Format::ID::ETC2_R8G8B8_UNORM_BLOCK;
        case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
            return Format::ID::ETC2_R8G8B8A1_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA8_ETC2_EAC:
            return Format::ID::ETC2_R8G8B8A8_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_10x10_KHR:
            return Format::ID::ASTC_10x10_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_10x5_KHR:
            return Format::ID::ASTC_10x5_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_10x6_KHR:
            return Format::ID::ASTC_10x6_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_10x8_KHR:
            return Format::ID::ASTC_10x8_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_12x10_KHR:
            return Format::ID::ASTC_12x10_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_12x12_KHR:
            return Format::ID::ASTC_12x12_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_4x4_KHR:
            return Format::ID::ASTC_4x4_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_5x4_KHR:
            return Format::ID::ASTC_5x4_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_5x5_KHR:
            return Format::ID::ASTC_5x5_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_6x5_KHR:
            return Format::ID::ASTC_6x5_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_6x6_KHR:
            return Format::ID::ASTC_6x6_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_8x5_KHR:
            return Format::ID::ASTC_8x5_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_8x6_KHR:
            return Format::ID::ASTC_8x6_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_ASTC_8x8_KHR:
            return Format::ID::ASTC_8x8_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            return Format::ID::BC1_RGBA_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE:
            return Format::ID::BC2_RGBA_UNORM_BLOCK;
        case GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE:
            return Format::ID::BC3_RGBA_UNORM_BLOCK;
        case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
            return Format::ID::BC1_RGB_UNORM_BLOCK;
        case GL_COMPRESSED_SIGNED_R11_EAC:
            return Format::ID::EAC_R11_SNORM_BLOCK;
        case GL_COMPRESSED_SIGNED_RG11_EAC:
            return Format::ID::EAC_R11G11_SNORM_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR:
            return Format::ID::ASTC_10x10_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:
            return Format::ID::ASTC_10x5_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:
            return Format::ID::ASTC_10x6_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:
            return Format::ID::ASTC_10x8_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR:
            return Format::ID::ASTC_12x10_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR:
            return Format::ID::ASTC_12x12_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:
            return Format::ID::ASTC_4x4_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:
            return Format::ID::ASTC_5x4_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:
            return Format::ID::ASTC_5x5_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:
            return Format::ID::ASTC_6x5_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:
            return Format::ID::ASTC_6x6_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:
            return Format::ID::ASTC_8x5_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:
            return Format::ID::ASTC_8x6_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:
            return Format::ID::ASTC_8x8_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
            return Format::ID::ETC2_R8G8B8A8_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_ETC2:
            return Format::ID::ETC2_R8G8B8_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
            return Format::ID::ETC2_R8G8B8A1_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
            return Format::ID::BC1_RGBA_UNORM_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
            return Format::ID::BC2_RGBA_UNORM_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
            return Format::ID::BC3_RGBA_UNORM_SRGB_BLOCK;
        case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
            return Format::ID::BC1_RGB_UNORM_SRGB_BLOCK;
        case GL_DEPTH24_STENCIL8:
            return Format::ID::D24_UNORM_S8_UINT;
        case GL_DEPTH32F_STENCIL8:
            return Format::ID::D32_FLOAT_S8X24_UINT;
        case GL_DEPTH_COMPONENT16:
            return Format::ID::D16_UNORM;
        case GL_DEPTH_COMPONENT24:
            return Format::ID::D24_UNORM;
        case GL_DEPTH_COMPONENT32F:
            return Format::ID::D32_FLOAT;
        case GL_DEPTH_COMPONENT32_OES:
            return Format::ID::D32_UNORM;
        case GL_ETC1_RGB8_LOSSY_DECODE_ANGLE:
            return Format::ID::ETC1_LOSSY_DECODE_R8G8B8_UNORM_BLOCK;
        case GL_ETC1_RGB8_OES:
            return Format::ID::ETC1_R8G8B8_UNORM_BLOCK;
        case GL_LUMINANCE16F_EXT:
            return Format::ID::L16_FLOAT;
        case GL_LUMINANCE32F_EXT:
            return Format::ID::L32_FLOAT;
        case GL_LUMINANCE8_ALPHA8_EXT:
            return Format::ID::L8A8_UNORM;
        case GL_LUMINANCE8_EXT:
            return Format::ID::L8_UNORM;
        case GL_LUMINANCE_ALPHA16F_EXT:
            return Format::ID::L16A16_FLOAT;
        case GL_LUMINANCE_ALPHA32F_EXT:
            return Format::ID::L32A32_FLOAT;
        case GL_NONE:
            return Format::ID::NONE;
        case GL_R11F_G11F_B10F:
            return Format::ID::R11G11B10_FLOAT;
        case GL_R16F:
            return Format::ID::R16_FLOAT;
        case GL_R16I:
            return Format::ID::R16_SINT;
        case GL_R16UI:
            return Format::ID::R16_UINT;
        case GL_R16_EXT:
            return Format::ID::R16_UNORM;
        case GL_R16_SNORM_EXT:
            return Format::ID::R16_SNORM;
        case GL_R32F:
            return Format::ID::R32_FLOAT;
        case GL_R32I:
            return Format::ID::R32_SINT;
        case GL_R32UI:
            return Format::ID::R32_UINT;
        case GL_R8:
            return Format::ID::R8_UNORM;
        case GL_R8I:
            return Format::ID::R8_SINT;
        case GL_R8UI:
            return Format::ID::R8_UINT;
        case GL_R8_SNORM:
            return Format::ID::R8_SNORM;
        case GL_RG16F:
            return Format::ID::R16G16_FLOAT;
        case GL_RG16I:
            return Format::ID::R16G16_SINT;
        case GL_RG16UI:
            return Format::ID::R16G16_UINT;
        case GL_RG16_EXT:
            return Format::ID::R16G16_UNORM;
        case GL_RG16_SNORM_EXT:
            return Format::ID::R16G16_SNORM;
        case GL_RG32F:
            return Format::ID::R32G32_FLOAT;
        case GL_RG32I:
            return Format::ID::R32G32_SINT;
        case GL_RG32UI:
            return Format::ID::R32G32_UINT;
        case GL_RG8:
            return Format::ID::R8G8_UNORM;
        case GL_RG8I:
            return Format::ID::R8G8_SINT;
        case GL_RG8UI:
            return Format::ID::R8G8_UINT;
        case GL_RG8_SNORM:
            return Format::ID::R8G8_SNORM;
        case GL_RGB:
            return Format::ID::R8G8B8_UNORM;
        case GL_RGB10_A2:
            return Format::ID::R10G10B10A2_UNORM;
        case GL_RGB10_A2UI:
            return Format::ID::R10G10B10A2_UINT;
        case GL_RGB16F:
            return Format::ID::R16G16B16_FLOAT;
        case GL_RGB16I:
            return Format::ID::R16G16B16_SINT;
        case GL_RGB16UI:
            return Format::ID::R16G16B16_UINT;
        case GL_RGB16_EXT:
            return Format::ID::R16G16B16_UNORM;
        case GL_RGB16_SNORM_EXT:
            return Format::ID::R16G16B16_SNORM;
        case GL_RGB32F:
            return Format::ID::R32G32B32_FLOAT;
        case GL_RGB32I:
            return Format::ID::R32G32B32_SINT;
        case GL_RGB32UI:
            return Format::ID::R32G32B32_UINT;
        case GL_RGB565:
            return Format::ID::R5G6B5_UNORM;
        case GL_RGB5_A1:
            return Format::ID::R5G5B5A1_UNORM;
        case GL_RGB8:
            return Format::ID::R8G8B8_UNORM;
        case GL_RGB8I:
            return Format::ID::R8G8B8_SINT;
        case GL_RGB8UI:
            return Format::ID::R8G8B8_UINT;
        case GL_RGB8_SNORM:
            return Format::ID::R8G8B8_SNORM;
        case GL_RGB9_E5:
            return Format::ID::R9G9B9E5_SHAREDEXP;
        case GL_RGBA:
            return Format::ID::R8G8B8A8_UNORM;
        case GL_RGBA16F:
            return Format::ID::R16G16B16A16_FLOAT;
        case GL_RGBA16I:
            return Format::ID::R16G16B16A16_SINT;
        case GL_RGBA16UI:
            return Format::ID::R16G16B16A16_UINT;
        case GL_RGBA16_EXT:
            return Format::ID::R16G16B16A16_UNORM;
        case GL_RGBA16_SNORM_EXT:
            return Format::ID::R16G16B16A16_SNORM;
        case GL_RGBA32F:
            return Format::ID::R32G32B32A32_FLOAT;
        case GL_RGBA32I:
            return Format::ID::R32G32B32A32_SINT;
        case GL_RGBA32UI:
            return Format::ID::R32G32B32A32_UINT;
        case GL_RGBA4:
            return Format::ID::R4G4B4A4_UNORM;
        case GL_RGBA8:
            return Format::ID::R8G8B8A8_UNORM;
        case GL_RGBA8I:
            return Format::ID::R8G8B8A8_SINT;
        case GL_RGBA8UI:
            return Format::ID::R8G8B8A8_UINT;
        case GL_RGBA8_SNORM:
            return Format::ID::R8G8B8A8_SNORM;
        case GL_RGBA8_TYPELESS_ANGLEX:
            return Format::ID::R8G8B8A8_TYPELESS;
        case GL_RGBA8_TYPELESS_SRGB_ANGLEX:
            return Format::ID::R8G8B8A8_TYPELESS_SRGB;
        case GL_SRGB8:
            return Format::ID::R8G8B8_UNORM_SRGB;
        case GL_SRGB8_ALPHA8:
            return Format::ID::R8G8B8A8_UNORM_SRGB;
        case GL_STENCIL_INDEX8:
            return Format::ID::S8_UINT;
        default:
            return Format::ID::NONE;
    }
}

// static
const Format &Format::Get(ID id)
{
    return g_formatInfoTable[static_cast<size_t>(id)];
}

}  // namespace angle

