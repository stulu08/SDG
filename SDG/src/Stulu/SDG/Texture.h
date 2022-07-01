#pragma once
#include "Core.h"

namespace SDG {
	class STULU_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void* getHandle() const = 0;
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual std::string getPath() const = 0;

		virtual void setData(void* data) = 0;
		virtual void setData(void* data, uint32_t offsetX, uint32_t offsetY, uint32_t resizeContentWidth = 1, uint32_t resizeContentHeight = 1) = 0;
		virtual void setPixel(uint32_t color, uint32_t x, uint32_t y) = 0;
		virtual void setPixel(const glm::vec4& color, uint32_t x, uint32_t y) = 0;
		virtual void resize(uint32_t width, uint32_t height, bool copyContent = true) = 0;

		virtual bool operator == (const Texture & other) const = 0;
		
		static Ref<Texture> create(const std::string& path);
		static Ref<Texture> create(uint32_t width, uint32_t height);
	};
}