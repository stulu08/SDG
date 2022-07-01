#include "st_pch.h"
#include "Texture.h"

#include "OpenGL/OpenGLTexture.h"

namespace SDG {
	Ref<Texture> Texture::create(const std::string& path) {
#if ST_USE_OPENGL
		return createRef<OpenGLTexture>(path);
#elif ST_USE_VULKAN
#endif
	}
	Ref<Texture> Texture::create(uint32_t width, uint32_t height) {
#if ST_USE_OPENGL
		return createRef<OpenGLTexture>(width, height);
#elif ST_USE_VULKAN
#endif
	}

}