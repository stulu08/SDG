#include "st_pch.h"
#include "UniformBuffer.h"

#include "OpenGL/OpenGLUniformBuffer.h"


SDG::Ref<SDG::UniformBuffer> SDG::UniformBuffer::create(uint32_t size, uint32_t binding) {
#if ST_USE_OPENGL
    return createRef<OpenGLUniformBuffer>(size, binding);
#elif ST_USE_VULKAN
#endif
}
