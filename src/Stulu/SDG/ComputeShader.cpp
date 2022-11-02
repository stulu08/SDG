#include "st_pch.h"
#include "ComputeShader.h"

#include "OpenGL/OpenGLComputeShader.h"

namespace SDG {
	Ref<ComputeShader> ComputeShader::create(const std::string& name, const std::string& src) {
#if ST_USE_OPENGL
		return createRef<OpenGLComputeShader>(name, src);
#elif ST_USE_VULKAN
#endif
	}
}