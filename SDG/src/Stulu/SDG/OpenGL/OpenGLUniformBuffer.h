#pragma once
#include "../UniformBuffer.h"

namespace SDG {
	class STULU_API OpenGLUniformBuffer : public UniformBuffer {
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~OpenGLUniformBuffer();

		virtual void setData(const void* data, uint32_t size, uint32_t offset) override;
		virtual uint32_t getSize() const override { return m_size; }
	private:
		uint32_t m_rendererID = 0;
		uint32_t m_size = 0;
	};
}