#include "core_pch.hpp"

namespace TE::Core
{
	void InputHandler::SetTargetWindow(const std::shared_ptr<IWindow>& window)
	{
		if( Core::GetBaseAPI() & API_GLFW )
		{
			GLFW3_InputPolling::SetTargetWindow(window);
		}

		if( Core::GetBaseAPI() & API_SDL )
		{
			SDL3_InputsPolling::SetTargetWindow(window);
		}
	}

	KEY_STATE InputHandler::GetKeyState(KEY key)
	{
		if( Core::GetBaseAPI() & API_GLFW )
		{
			return GLFW3_InputPolling::GetKeyState(key);
		}

		if( Core::GetBaseAPI() & API_SDL )
		{
			return SDL3_InputsPolling::GetKeyState(key);
		}

		return KEY_NONE;
	}

	MOUSE_BUTTON_STATE InputHandler::GetMouseState(MOUSE_BUTTON button)
	{
		if( Core::GetBaseAPI() & API_GLFW )
		{
			return GLFW3_InputPolling::GetMouseState(button);
		}

		if( Core::GetBaseAPI() & API_SDL )
		{
			return SDL3_InputsPolling::GetMouseState(button);
		}

		return MOUSE_BUTTON_NONE;
	}

	glm::vec2 InputHandler::GetCurrentMousePosition()
	{
		if( Core::GetBaseAPI() & API_GLFW )
		{
			return GLFW3_InputPolling::GetCurrentMousePosition();
		}

		if( Core::GetBaseAPI() & API_SDL )
		{
			return SDL3_InputsPolling::GetCurrentMousePosition();
		}

		return { 0.0f, 0.0f };
	}
}