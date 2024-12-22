#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "window.hpp"

namespace trimana::core {

	class glfw_service_api final : public platform_service_api {
	public:
		glfw_service_api() = default;
		~glfw_service_api() = default;

		virtual bool init() override;
		virtual void quit() override;
		virtual platform_service_apis api() override { return platform_service_apis::glfw_api; }

	private:
		bool m_initialized{ false };
	};

	class glfw_window final : public window {
	public:
		glfw_window(const std::string& title);
		~glfw_window();

		virtual void* native_window() const override { return m_window; }
		virtual window_properties* properties() override { return &m_properties; }
		virtual void swap_buffers() const override;

	private:
		GLFWwindow* m_window{ nullptr };
		window_properties m_properties{};
	};
}