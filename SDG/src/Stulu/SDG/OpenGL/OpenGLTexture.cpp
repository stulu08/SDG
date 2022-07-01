#include "st_pch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace SDG {
	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height) {
		m_width = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, GL_RGBA8, m_width, m_height);

		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	OpenGLTexture::OpenGLTexture(const std::string& path)
		:m_path(path) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);

		int32_t width, height, channels;
		stbi_set_flip_vertically_on_load(0);
		stbi_uc* textureData = nullptr;
		{

			textureData = stbi_load(m_path.c_str(), &width, &height, &channels, 4);
			if (!textureData)
				std::cout << "Texture failed to load: " << m_path << std::endl;

		}
		m_width = width;
		m_height = height;

		glTextureStorage2D(m_rendererID, 1, GL_RGBA8, m_width, m_height);

		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		stbi_image_free(textureData);

	}
	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &m_rendererID);
	}
	void* OpenGLTexture::getHandle() const {
		return reinterpret_cast<void*>((uint64_t)m_rendererID);
	}
	void OpenGLTexture::setData(void* data, uint32_t offsetX, uint32_t offsetY, uint32_t resizeContentWidth, uint32_t resizeContentHeight) {
		glTextureSubImage2D(m_rendererID, 0, offsetX, offsetY, resizeContentWidth, resizeContentHeight, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
	}
	void OpenGLTexture::resize(uint32_t width, uint32_t height, bool copyContent) {
		uint32_t sourceTexture = m_rendererID;
		uint32_t sourceWidth = m_width;
		uint32_t sourceHeight = m_height;

		m_width = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, GL_RGBA8, m_width, m_height);

		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (copyContent) {
			glCopyImageSubData(
				sourceTexture, GL_TEXTURE_2D,
				0, 0, 0, 0, 
				m_rendererID, GL_TEXTURE_2D, 
				0, 0, 0, 0, sourceWidth, sourceHeight, 1);
		}


		glDeleteTextures(1, &sourceTexture);
	}
	bool OpenGLTexture::operator==(const Texture& other) const {
		return getHandle() == other.getHandle();
	}
}