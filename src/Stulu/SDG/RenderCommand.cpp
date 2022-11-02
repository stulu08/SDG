#include "st_pch.h"
#include "RenderCommand.h"

#include "OpenGL/OpenGLRenderAPI.h"

namespace SDG {
	void RenderCommand::init() {
#if ST_USE_OPENGL
		OpenGLRenderAPI::init();
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
#if ST_USE_OPENGL
		OpenGLRenderAPI::setViewport(x,y,width,height);
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::setClearColor(const glm::vec4& color) {
#if ST_USE_OPENGL
		OpenGLRenderAPI::setClearColor(color);
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::clear() {
#if ST_USE_OPENGL
		OpenGLRenderAPI::clear();
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::imgui_init(GLFWwindow* window) {
#if ST_USE_OPENGL
		OpenGLRenderAPI::imgui_init(window);
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::imgui_newFrame() {
#if ST_USE_OPENGL
		OpenGLRenderAPI::imgui_newFrame();
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::imgui_render() {
#if ST_USE_OPENGL
		OpenGLRenderAPI::imgui_render();
#elif ST_USE_VULKAN
#endif
	}

	void RenderCommand::imgui_shutdown() {
#if ST_USE_OPENGL
		OpenGLRenderAPI::imgui_shutdown();
#elif ST_USE_VULKAN
#endif
	}

}