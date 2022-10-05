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
		//set imgui style
		{
			ImGuiStyle* style = &ImGui::GetStyle();
			ImVec4* colors = style->Colors;
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
			colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
			colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_DockingPreview] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.7f };
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}


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