#include "st_pch.h"
#include "Texture.h"

#include "OpenGL/OpenGLTexture.h"

namespace SDG {
	Ref<Texture> Texture::create(const std::string& path, const TextureSettings& settings) {
#if ST_USE_OPENGL
		return createRef<OpenGLTexture>(path, settings);
#elif ST_USE_VULKAN
#endif
	}
	Ref<Texture> Texture::create(uint32_t width, uint32_t height, const TextureSettings& settings) {
#if ST_USE_OPENGL
		return createRef<OpenGLTexture>(width, height, settings);
#elif ST_USE_VULKAN
#endif
	}

}