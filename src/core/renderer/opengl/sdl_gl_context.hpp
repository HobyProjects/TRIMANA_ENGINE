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
			SDL_GL_Context() = default;
			virtual ~SDL_GL_Context() = default;

			virtual bool MakeContext(Native window) override;
			virtual Native GetContext() const override;
			virtual void SwapBuffers() override;
			virtual void SetInterval(uint32_t interval) override;

		private:
			static std::once_flag s_InitRendererAPI;
			static void InitRendereringAPI();
	};
}