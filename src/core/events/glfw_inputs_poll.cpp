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
		return static_cast<KEY_STATE>( state );
	}

	MOUSE_BUTTON_STATE GLFW3_InputPolling::GetMouseState(MOUSE_BUTTON button)
	{
		if( s_Window.expired() )
			TE_ASSERT(false, "Input handling from destroyed window.");

		std::shared_ptr<IWindow> windowPtr = s_Window.lock();
		int state = glfwGetMouseButton((GLFWwindow*) windowPtr->Window(), static_cast<int>( button ));
		return static_cast<MOUSE_BUTTON_STATE>( state );
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