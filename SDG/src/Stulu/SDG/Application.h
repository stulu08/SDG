#pragma once

#include "Layer.h"
#include "GraphicsContext.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>


namespace SDG {
	class STULU_API Texture;
	struct ApplicationInfo {
		std::string title = "App Title";
		uint32_t width = 1280, height = 720;
		glm::uvec2 pos = glm::uvec2(25, 25);
		bool VSync = true, maximized = false;
		bool loadWindowPosSizeFromConfig = true;
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
		
		void setWindowPos(const glm::uvec2& pos);
		void setWindowSize(const glm::uvec2& size);

		void shutdown();

		uint32_t getWidth();
		uint32_t getHeight();
		glm::uvec2 getPos();
		void* getNativeWindow() { return m_window; }

		inline const float getFrameTime() const { return m_frameTime; }
		inline const ApplicationInfo& getApplicationInfo() const { return m_appInfo; }
		inline ApplicationInfo& getApplicationInfo() { return m_appInfo; }
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

namespace ImGui {
	STULU_API void Image(const SDG::Ref<SDG::Texture>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col);
	STULU_API void Image(const SDG::Ref<SDG::Texture>& texture, const glm::vec2& size, const glm::vec2& uv0 = { 0,0 }, const glm::vec2& uv1 = { 1,1 }, const glm::vec4& tint_col = { 1,1,1,1 }, const glm::vec4& border_col = { 0,0,0,0 });

	STULU_API bool ImageButton(const SDG::Ref<SDG::Texture>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col);    // <0 frame_padding uses default frame padding settings. 0 for no padding
	STULU_API bool ImageButton(const SDG::Ref<SDG::Texture>& texture, const glm::vec2& size, const glm::vec2& uv0 = glm::vec2(0, 0), const glm::vec2& uv1 = glm::vec2(1, 1), int frame_padding = -1, const glm::vec4& bg_col = glm::vec4(0, 0, 0, 0), const glm::vec4& tint_col = glm::vec4(1, 1, 1, 1));    // <0 frame_padding uses default frame padding settings. 0 for no padding

	STULU_API ImTextureID SDGTextureToImGui(const SDG::Ref<SDG::Texture>& texture);
}