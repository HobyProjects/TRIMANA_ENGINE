#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "base.hpp"
#include "window.hpp"

namespace trimana::core {

	class glfw_gl_context final : public context {
	public:
		glfw_gl_context(void* native_window) : m_native_window(native_window) {}
		virtual ~glfw_gl_context() = default;

		virtual bool make_context() override;
		virtual void swap_buffers() override;
		virtual void change_swap_interval(uint32_t interval) override;

	private:
		void* m_native_window{ nullptr };
	};
}