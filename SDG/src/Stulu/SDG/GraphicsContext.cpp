#include "st_pch.h"
#include "GraphicsContext.h"
#include "OpenGL/OpenGLContext.h"

namespace SDG {
	Scope<GraphicsContext> GraphicsContext::create(GLFWwindow* window) {
#if ST_USE_OPENGL
		return createScope<OpenGLContext>(window);
#elif ST_USE_VULKAN
#endif
	}
}