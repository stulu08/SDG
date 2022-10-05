#pragma once

#include "Layer.h"
#include "GraphicsContext.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include <vector>
struct ImGuiContext;
namespace SDG {
	struct ApplicationInfo {
		std::string title = "App Title";
		uint32_t width = 1280, height = 720;
	};
	class STULU_API Application {
	public:
		Application(const ApplicationInfo& info);
		virtual ~Application();

		void run();
		void pushLayer(Ref<Layer> layer) {
			m_layerStack.emplace_back(layer)->onAttach();
		}
		template<typename T>
		void pushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_layerStack.emplace_back(createRef<T>())->onAttach();
		}
		void popLayer(Ref<Layer> layer);
		
		void shutdown();

		uint32_t getWidth();
		uint32_t getHeight();
		void* getNativeWindow() { return m_window; }

		inline const float getFrameTime() const { return m_frameTime; }
		inline const ApplicationInfo& getApplicationInfo() const { return m_appInfo; }
		inline static Application& get(){ return *s_instance; }
	private:
		bool m_runnig = false;
		bool m_minimized = false;
		float m_frameTime = .0f, m_lastFrame = .0f;
		ApplicationInfo m_appInfo;
		GLFWwindow* m_window;
		ImGuiContext* m_context;
		Scope<GraphicsContext> m_graphicsContext;
		std::vector<Ref<Layer>> m_layerStack;

		void initglfw();
		
		static Application* s_instance;
	};

	//defined in Client
	Application* CreateApplication();
}

