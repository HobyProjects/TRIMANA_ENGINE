#include "sdl_events_receiver.hpp"
#include <SDL3/SDL.h>

namespace trimana::core
{

	static SDL_Event sdl_event;
	static event_callback& const m_callback;
	static std::shared_ptr<window>& const m_window;

	sdl_events_receiver::sdl_events_receiver(const std::shared_ptr<window>& window, const event_callback& callback)
	{
		m_window = window;
		m_callback = callback;
	}

	void sdl_events_receiver::poll_events() const
	{
		SDL_WaitEvent(&sdl_event);

		switch( sdl_event.type )
		{
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			{
				window_close_event close_event;
				m_callback(close_event);
				break;
			}
			case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
			{
				m_window->properties()->width = sdl_event.window.data1;
				m_window->properties()->height = sdl_event.window.data2;
				window_resize_event resize_event(sdl_event.window.data1, sdl_event.window.data2);
				m_callback(resize_event);
				break;
			}
			case SDL_EVENT_WINDOW_MOVED:
			{
				m_window->properties()->pos_x = sdl_event.window.data1;
				m_window->properties()->pos_y = sdl_event.window.data2;
				window_move_event move_event(sdl_event.window.data1, sdl_event.window.data2);
				m_callback(move_event);
				break;
			}
			case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			{
				m_window->properties()->framebuffer_width = sdl_event.window.data1;
				m_window->properties()->framebuffer_height = sdl_event.window.data2;
				window_pixel_size_change_event resize_event(sdl_event.window.data1, sdl_event.window.data2);
				m_callback(resize_event);
				break;
			}
			case SDL_EVENT_WINDOW_MAXIMIZED:
			{
				m_window->properties()->window_state = window_state::maximized;
				window_maximize_event maximize_event;
				m_callback(maximize_event);
				break;
			}
			case SDL_EVENT_WINDOW_MINIMIZED:
			{
				m_window->properties()->window_state = window_state::minimized;
				window_minimize_event minimize_event;
				m_callback(minimize_event);
				break;
			}
			case SDL_EVENT_WINDOW_RESTORED:
			{
				m_window->properties()->window_state = window_state::normal;
				window_restore_event restore_event;
				m_callback(restore_event);
				break;
			}
			case SDL_EVENT_WINDOW_FOCUS_GAINED:
			{
				window_focus_gain_event focus_gain_event;
				m_callback(focus_gain_event);
				break;
			}
			case SDL_EVENT_WINDOW_FOCUS_LOST:
			{
				window_focus_lost_event focus_lost_event;
				m_callback(focus_lost_event);
				break;
			}
			case SDL_EVENT_KEY_DOWN:
			{
				if( sdl_event.key.down )
				{
					keyboard_keypress_event keypress_event(static_cast<key>( sdl_event.key.key ));
					m_callback(keypress_event);
					break;
				}

				if( sdl_event.key.repeat )
				{
					keyboard_keyrepeat_event keyrepeat_event(static_cast<key>( sdl_event.key.key ));
					m_callback(keyrepeat_event);
					break;
				}
			}
			case SDL_EVENT_KEY_UP:
			{
				keyboard_keyrelease_event keyrelease_event(static_cast<key>( sdl_event.key.key ));
				m_callback(keyrelease_event);
				break;
			}
			case SDL_EVENT_TEXT_INPUT:
			{
				keyboard_textinput_event keychar_event(sdl_event.text.text);
				m_callback(keychar_event);
				break;
			}
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			{
				mouse_button_press_event button_press_event(static_cast<mouse_button>( sdl_event.button.button ));
				m_callback(button_press_event);
				break;
			}
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				mouse_button_release_event button_release_event(static_cast<mouse_button>( sdl_event.button.button ));
				m_callback(button_release_event);
				break;
			}
			case SDL_EVENT_MOUSE_WHEEL:
			{
				mouse_wheel_event wheel_event(sdl_event.wheel.x, sdl_event.wheel.y);
				m_callback(wheel_event);
				break;
			}
			case SDL_EVENT_MOUSE_MOTION:
			{
				mouse_cursor_moved_event cursor_moved_event(sdl_event.motion.x, sdl_event.motion.y);
				m_callback(cursor_moved_event);
				break;
			}
			case SDL_EVENT_WINDOW_MOUSE_ENTER:
			{
				mouse_cursor_enter_event cursor_enter_event;
				m_callback(cursor_enter_event);
				break;
			}
			case SDL_EVENT_WINDOW_MOUSE_LEAVE:
			{
				mouse_cursor_leave_event cursor_leave_event;
				m_callback(cursor_leave_event);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}