#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "base.hpp"
#include "base_window.hpp"

namespace TE::Core
{
	class SDL_GL_Context final : public IContext
	{
		public:
			SDL_GL_Context();
			virtual ~SDL_GL_Context() = default;

			virtual void Attach(Native window) override;
			virtual void Detach() override;

			virtual Native GetContext() const override;
			virtual void SwapBuffers(Native window) override;
			virtual void SetInterval(uint32_t interval) override;
	};
}