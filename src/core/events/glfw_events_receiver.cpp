#include "glfw_events_receiver.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace trimana::core {

	static std::shared_ptr<window>& const s_window;
	static event_callback& const s_event_callback;

	glfw_events_receiver::glfw_events_receiver(const std::shared_ptr<window>& win, const event_callback& callback) {
		
		s_window = win;
		s_event_callback = callback;

		glfwSetWindowCloseCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window) 
		{
			window_close_event windowClose;
			s_event_callback(windowClose);
		});

		glfwSetWindowSizeCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int width, int height) 
		{
			s_window->properties()->width = width;
			s_window->properties()->height = height;
			window_resize_event windowResize(width, height);
			s_event_callback(windowResize);
		});

		glfwSetWindowPosCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int x, int y) 
		{
			s_window->properties()->pos_x = x;
			s_window->properties()->pos_y = y;
			window_move_event windowPosChange(x, y);
			s_event_callback(windowPosChange);
		});

		glfwSetWindowFocusCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int focused) 
		{
			if (focused) {
				s_window->properties()->is_focused = true;
				window_focus_gain_event windowFocusGain;
				s_event_callback(windowFocusGain);
			}
			else {
				s_window->properties()->is_focused = false;
				window_focus_lost_event windowFocusLost;
				s_event_callback(windowFocusLost);
			}
		});

		glfwSetWindowMaximizeCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int maximized)
		{
			s_window->properties()->window_state = window_state::maximized;
			window_maximize_event windowMaximized;
			s_event_callback(windowMaximized);
		});

		glfwSetWindowIconifyCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int iconified)
		{
			s_window->properties()->window_state = window_state::minimized;
			window_minimize_event windowMinimized;
			s_event_callback(windowMinimized);
		});

		glfwSetFramebufferSizeCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int width, int height)
		{
			window_pixel_size_change_event windowFramebufferResize(width, height);
			s_event_callback(windowFramebufferResize);
		});

		glfwSetCursorEnterCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int entered)
		{
			if (entered) {
				mouse_cursor_enter_event cursorEnter;
				s_event_callback(cursorEnter);
			}
			else {
				mouse_cursor_leave_event cursorLeave;
				s_event_callback(cursorLeave);
			}
		});

		glfwSetMouseButtonCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS) {
				mouse_button_press_event mouseButtonPressed(static_cast<mouse_button>(button));
				s_event_callback(mouseButtonPressed);
			}

			if (action == GLFW_RELEASE) {
				mouse_button_release_event mouseButtonReleased(static_cast<mouse_button>(button));
				s_event_callback(mouseButtonReleased);
			}
		});

		glfwSetKeyCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS) {
				keyboard_keypress_event keyPressed(static_cast<trimana::core::key>(key));
				s_event_callback(keyPressed);
			}

			if (action == GLFW_RELEASE) {
				keyboard_keyrelease_event keyReleased(static_cast<trimana::core::key>(key));
				s_event_callback(keyReleased);
			}

			if (action == GLFW_REPEAT) {
				keyboard_keyrepeat_event keyRepeat(static_cast<trimana::core::key>(key));
				s_event_callback(keyRepeat);
			}
		});

		glfwSetCharCallback((GLFWwindow*)s_window->native_window(), [](GLFWwindow* window, unsigned int keycode)
		{
			keyboard_keychar_event keyChar(keycode);
			s_event_callback(keyChar);
		});
	}

	void glfw_events_receiver::poll_events() const
	{
		glfwPollEvents();
	}
}