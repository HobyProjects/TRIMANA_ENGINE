#include "core_pch.hpp"

namespace TE::Core
{
	static std::weak_ptr<IWindow> s_Window;

	void GLFW3_InputPolling::SetTargetWindow(const std::shared_ptr<IWindow>& window)
	{
		s_Window = window;
	}

	KEY_STATE GLFW3_InputPolling::GetKeyState(KEY key)
	{
		if( s_Window.expired() )
			TE_ASSERT(false, "Input handling from destroyed window.");

		std::shared_ptr<IWindow> windowPtr = s_Window.lock();
		int state = glfwGetKey((GLFWwindow*) windowPtr->Window(), static_cast<int>( key ));
		
		if( state == GLFW_PRESS )
			return KEY_STATE::KEY_PRESSED;

		if( state == GLFW_RELEASE )
			return KEY_STATE::KEY_RELEASED;

		if( state == GLFW_REPEAT )
			return KEY_STATE::KEY_REPEAT;

		return KEY_STATE::KEY_NONE;
	}

	MOUSE_BUTTON_STATE GLFW3_InputPolling::GetMouseState(MOUSE_BUTTON button)
	{
		if( s_Window.expired() )
			TE_ASSERT(false, "Input handling from destroyed window.");

		int mouseButton = 0;

		if( button & MOUSE_BUTTON::MOUSE_BUTTON_LEFT )
			mouseButton = GLFW_MOUSE_BUTTON_LEFT;
		else if( button & MOUSE_BUTTON::MOUSE_BUTTON_RIGHT )
			mouseButton = GLFW_MOUSE_BUTTON_RIGHT;
		else if( button & MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE )
			mouseButton = GLFW_MOUSE_BUTTON_MIDDLE;
		else
			TE_ASSERT(false, "Unknown mouse button.");

		std::shared_ptr<IWindow> windowPtr = s_Window.lock();
		int state = glfwGetMouseButton((GLFWwindow*) windowPtr->Window(), mouseButton);

		if( state == GLFW_PRESS )
			return MOUSE_BUTTON_STATE::MOUSE_BUTTON_PRESSED;

		if( state == GLFW_RELEASE )
			return MOUSE_BUTTON_STATE::MOUSE_BUTTON_RELEASED;

		return MOUSE_BUTTON_STATE::MOUSE_BUTTON_NONE;
	}

	glm::vec2 GLFW3_InputPolling::GetCurrentMousePosition()
	{
		if( s_Window.expired() )
			TE_ASSERT(false, "Input handling from destroyed window.");

		double posX{ 0.0 }, posY{ 0.0 };
		std::shared_ptr<IWindow> windowPtr = s_Window.lock();
		glfwGetCursorPos((GLFWwindow*) windowPtr->Window(), &posX, &posY);
		return glm::vec2(static_cast<float>( posX ), static_cast<float>( posY ));
	}




}