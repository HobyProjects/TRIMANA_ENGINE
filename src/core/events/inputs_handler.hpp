#pragma once

#include <glm/glm.hpp>
#include "base_window.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class InputHandler
	{
        public:
            static void SetTargetWindow(const std::shared_ptr<IWindow>& window);
            static KEY_STATE GetKeyState(KEY key);
            static MOUSE_BUTTON_STATE GetMouseState(MOUSE_BUTTON button);
            static glm::vec2 GetCurrentMousePosition();

        private:
            InputHandler() = default;
            ~InputHandler() = default;
            InputHandler(InputHandler const&) = delete;
            InputHandler& operator=(InputHandler const&) = delete;
            InputHandler(InputHandler&&) = delete;
            InputHandler& operator=(InputHandler&&) = delete;
	};
}