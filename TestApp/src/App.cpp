#include "SDG/SDG.h"
#include "SDG/EntryPoint.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"

class ExampleLayer : public SDG::Layer {
private:
	uint32_t* m_data = nullptr;
	SDG::Ref<SDG::Texture> m_texture;
public:

	virtual void onAttach() override {
		const uint32_t width = 500, height = 500;
		m_texture = SDG::Texture::create(width, height);
		m_data = new uint32_t[width * height];
		
	}
	virtual void onRender() override {
		uint32_t width = m_texture->getWidth(), height = m_texture->getHeight();

		for (uint32_t x = 0; x < width; x++) {
			for (uint32_t y = 0; y < height; y++) {
				glm::vec2 coord = { (float)x / (float)width, (float)y / (float)height };
				coord = coord * 2.0f - 1.0f; // -1 -> 1

				m_data[x + y * width] = calcPixelColor(coord);
				//m_data[x + y * width] = 0xffff00ff;
			}
		}
		m_texture->setData(m_data);


		if (ImGui::Begin("Test")) {
			static float scale = 1.0f;
			ImGui::Text("Frametime: %.2fms", SDG::Application::get().getFrameTime() * 1000);
			ImGui::DragFloat("Scale", &scale, .01f);
			scale = max(scale, .01f);
			ImGui::Image(m_texture->getHandle(), ImVec2((float)width, (float)height) * scale);
		}
		ImGui::End();
	}
	uint32_t calcPixelColor(const glm::vec2& coord) {
		glm::vec3 spherePos(.0f, .0f, .0f);
		glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
		float radius = 0.5f;
		// rayDirection = glm::normalize(rayDirection);

		// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
		// where
		// a = ray origin
		// b = ray direction
		// r = radius
		// t = hit distance

		float a = glm::dot(rayDirection, rayDirection);
		float b = 2.0f * glm::dot(rayOrigin + spherePos, rayDirection);
		float c = glm::dot(rayOrigin + spherePos, rayOrigin + spherePos) - radius * radius;

		// Quadratic forumula discriminant:
		// b^2 - 4ac

		float discriminant = b * b - 4.0f * a * c;
		if (discriminant >= 0.0f)
			return 0xffff00ff;

		return 0xff000000;
	}
};

SDG::Application* SDG::CreateApplication()
{
	SDG::ApplicationInfo info;
	info.title = "Example";

	SDG::Application* app = new SDG::Application(info);
	app->pushLayer<ExampleLayer>();
	
	return app;
}