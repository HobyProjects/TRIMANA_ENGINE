#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "base_window.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class GLFW3_InputPolling
	{
        public:
            static void SetTargetWindow(const std::shared_ptr<IWindow>& window);
            static KEY_STATE GetKeyState(KEY key);
            static MOUSE_BUTTON_STATE GetMouseState(MOUSE_BUTTON button);
            static glm::vec2 GetCurrentMousePosition();

        private:
            GLFW3_InputPolling() = default;
            ~GLFW3_InputPolling() = default;
            GLFW3_InputPolling(GLFW3_InputPolling const&) = delete;
            GLFW3_InputPolling& operator=(GLFW3_InputPolling const&) = delete;
            GLFW3_InputPolling(GLFW3_InputPolling&&) = delete;
            GLFW3_InputPolling& operator=(GLFW3_InputPolling&&) = delete;
	};
}