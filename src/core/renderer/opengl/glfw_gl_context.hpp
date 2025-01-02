#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>

#include "base.hpp"
#include "base_window.hpp"

namespace TE::Core
{
	class GLFW_GL_Context final : public IContext
	{
		public:
			GLFW_GL_Context();
			virtual ~GLFW_GL_Context() = default;

			virtual void Attach(Native window) override;
			virtual void Detach() override;

			virtual Native GetContext() const override;
			virtual void SwapBuffers(Native window) override;
			virtual void SetInterval(uint32_t interval) override;
	};
}