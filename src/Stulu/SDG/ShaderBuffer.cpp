#include "st_pch.h"
#include "ShaderBuffer.h"

#include "OpenGL/OpenGLShaderBuffer.h"


SDG::Ref<SDG::UniformBuffer> SDG::UniformBuffer::create(uint32_t size, uint32_t binding) {
#if ST_USE_OPENGL
    return createRef<OpenGLUniformBuffer>(size, binding);
#elif ST_USE_VULKAN
#endif
}

SDG::Ref<SDG::ShaderStorageBuffer> SDG::ShaderStorageBuffer::create(uint32_t size, uint32_t binding, BufferDrawMode mode) {
#if ST_USE_OPENGL
    return createRef<OpenGLShaderStorageBuffer>(size, binding, mode);
#elif ST_USE_VULKAN
#endif
}
