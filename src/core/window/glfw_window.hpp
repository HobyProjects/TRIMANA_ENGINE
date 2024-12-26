#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "window.hpp"

namespace trimana::core
{
	class glfw_service_api final : public platform_service_api
	{
	public:
		glfw_service_api() = default;
		~glfw_service_api() = default;

		virtual bool init() override;
		virtual void quit() override;
		virtual platform_service_apis api() override { return platform_service_apis::glfw_api; }

	private:
		bool m_initialized{ false };
	};

	class glfw_window final : public window
	{
	public:
		glfw_window(const std::string& title, const std::shared_ptr<glfw_service_api>& glfw_service_api);
		~glfw_window();

		virtual void* native_window() const override { return m_window; }
		virtual window_properties* properties() override { return &m_properties; }
		virtual void swap_buffers() const override;
		virtual std::shared_ptr<context> window_context() const override { return m_context; }

	private:
		GLFWwindow* m_window{ nullptr };
		window_properties m_properties{};
		std::shared_ptr<context> m_context{ nullptr };
		std::weak_ptr<glfw_service_api> m_glfw_service_api;
	};
}