#pragma once
#include "Core.h"

namespace SDG {
	class STULU_API UniformBuffer {
	public:
		virtual ~UniformBuffer() = default;
		virtual void setData(const void* data, uint32_t size, uint32_t offset = 0) = 0;
		virtual uint32_t getSize() const = 0;

		static Ref<UniformBuffer> create(uint32_t size, uint32_t binding);
	};
}