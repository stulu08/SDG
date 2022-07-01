#include "st_pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include "RenderCommand.h"

namespace SDG {
	Application* Application::s_instance = nullptr;

	Application::Application(const ApplicationInfo& appInfo)
		: m_appInfo(appInfo) {
		s_instance = this;
		initglfw();
		RenderCommand::init();

		IMGUI_CHECKVERSION();
		m_context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		Application& app = Application::get();

		RenderCommand::imgui_init(m_window);
	}
	Application::~Application() {
		for (auto& layer : m_layerStack)
			popLayer(layer);
		RenderCommand::imgui_shutdown();
		ImGui::DestroyContext(m_context);
		glfwDestroyWindow(m_window);
		glfwTerminate();

		m_runnig = false;
		m_context = nullptr;
		m_window = nullptr;
		s_instance = nullptr;
	}

	void Application::popLayer(Ref<Layer> layer) {
		layer->onDetach();
		m_layerStack.erase(std::find(m_layerStack.begin(), m_layerStack.end(), layer));
	}



	void Application::run() {
		m_runnig = true;
		while (m_runnig) {
			if (!m_minimized && m_window) {

				m_frameTime = (float)glfwGetTime() - m_lastFrame;
				m_lastFrame = (float)glfwGetTime();

				RenderCommand::clear();
				glfwPollEvents();
				if (m_context) {
					RenderCommand::imgui_newFrame();
					ImGui::NewFrame();
					ImGui::DockSpaceOverViewport();
				}
				

				for (Ref<Layer> layer : m_layerStack) {
					layer->onRender();
				}

				if (m_context) {
					ImGuiIO& io = ImGui::GetIO();
					Application& app = Application::get();
					io.DisplaySize = ImVec2((float)getWidth(), (float)getHeight());
					// Rendering
					ImGui::Render();
					RenderCommand::imgui_render();
					if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
					{
						GLFWwindow* backup_current_context = glfwGetCurrentContext();
						ImGui::UpdatePlatformWindows();
						ImGui::RenderPlatformWindowsDefault();
						glfwMakeContextCurrent(backup_current_context);
					}
				}
				

				m_graphicsContext->swapBuffers();
			}
		}
	}


	static bool s_glfwInitilized = false;
	void Application::initglfw() {
		if (!s_glfwInitilized) {
			int32_t succes = glfwInit();
			s_glfwInitilized = true;
		}
#ifdef ST_DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
#if ST_USE_VULKAN
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#endif

		m_graphicsContext = GraphicsContext::create(m_window);
		m_window = glfwCreateWindow((int)m_appInfo.width, (int)m_appInfo.height, m_appInfo.title.c_str(), nullptr, nullptr);
		m_graphicsContext->init(m_window);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
				RenderCommand::setViewport(0, 0, width, height);
			});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
				Application::get().shutdown();
			});


		glfwSwapInterval(0); //enable vsync
	}
	void Application::shutdown() {
		m_runnig = false;
	}
	uint32_t Application::getWidth() {
		int x, y;
		glfwGetWindowSize(m_window, &x, &y);
		return (uint32_t)x;
	}
	uint32_t Application::getHeight() {
		int x, y;
		glfwGetWindowSize(m_window, &x, &y);
		return (uint32_t)y;
	}
}