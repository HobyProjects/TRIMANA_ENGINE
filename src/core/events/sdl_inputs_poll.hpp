#pragma once

#include <SDL3/SDL.h>

#include "base_window.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
    class SDL3_Window; // Forward Dec

	class SDL3_InputsPolling
	{
        public:
            static void SetTargetWindow(const std::shared_ptr<IWindow>& window);
            static KEY_STATE GetKeyState(KEY key);
            static MOUSE_BUTTON_STATE GetMouseState(MOUSE_BUTTON button);
            static glm::vec2 GetCurrentMousePosition();

            static void SetKeyState(Uint8 scanCode, KEY_STATE keyState);
            static void SetMouseButtonState(Uint8 button, MOUSE_BUTTON_STATE mouseButtonState);

        private:
            SDL3_InputsPolling() = default;
            ~SDL3_InputsPolling() = default;
            SDL3_InputsPolling(SDL3_InputsPolling const&) = delete;
            SDL3_InputsPolling& operator=(SDL3_InputsPolling const&) = delete;
            SDL3_InputsPolling(SDL3_InputsPolling&&) = delete;
            SDL3_InputsPolling& operator=(SDL3_InputsPolling&&) = delete;

            static Native TargetWindow();
            friend class SDL3_Window;

	};
}