#pragma once
#include "../Texture.h"

namespace SDG {
	class STULU_API OpenGLTexture : public Texture {
	public:
		OpenGLTexture(uint32_t width, uint32_t height);
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();
		virtual void* getHandle() const override;
		virtual uint32_t getWidth() const override { return m_width; }
		virtual uint32_t getHeight() const override { return m_height; }

		virtual void setData(void* data, uint32_t offsetX = 0, uint32_t offsetY = 0, uint32_t resizeContentWidth = 1, uint32_t resizeContentHeight = 1) override;
		
		virtual void setData(void* data) override {
			setData(data, 0, 0, m_width, m_height);
		}
		virtual void setPixel(uint32_t color, uint32_t x, uint32_t y) {
			setData(&color, x, y, 1, 1);
		}
		virtual void setPixel(const glm::vec4& color, uint32_t x, uint32_t y) {
			uint32_t r, g, b, a;
			
			r = static_cast<uint32_t>(glm::min(color.x * 255,255.0f));
			g = static_cast<uint32_t>(glm::min(color.y * 255,255.0f));
			b = static_cast<uint32_t>(glm::min(color.z * 255,255.0f));
			a = static_cast<uint32_t>(glm::min(color.w * 255,255.0f));

			uint32_t colorData = (r << 24 | g << 16 | b << 8 | a << 0);
			

			setData(&colorData, x, y, 1, 1);
		}

		
		virtual void resize(uint32_t width, uint32_t height, bool copyContent = true) override;

		virtual bool operator == (const Texture& other) const override;
		//temp
		virtual std::string getPath() const override { return m_path; }
	private:
		std::string m_path;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_rendererID;
	};
}

