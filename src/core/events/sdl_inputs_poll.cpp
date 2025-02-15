#include "core_pch.hpp"

namespace TE::Core
{
	static bool s_IsTargetWindowSet = false;
	static std::weak_ptr<IWindow> s_Window;
	static std::unordered_map<KEY, KEY_STATE> s_KeyStateMapping;
	static std::unordered_map<MOUSE_BUTTON, MOUSE_BUTTON_STATE> s_MouseButtonStateMapping;

	static KEY GetKey(Uint8 scanCode)
	{
		switch( scanCode )
		{
			case SDL_SCANCODE_A: return KEY_A;
			case SDL_SCANCODE_B: return KEY_B;
			case SDL_SCANCODE_C: return KEY_C;
			case SDL_SCANCODE_D: return KEY_D;
			case SDL_SCANCODE_E: return KEY_E;
			case SDL_SCANCODE_F: return KEY_F;
			case SDL_SCANCODE_G: return KEY_G;
			case SDL_SCANCODE_H: return KEY_H;
			case SDL_SCANCODE_I: return KEY_I;
			case SDL_SCANCODE_J: return KEY_J;
			case SDL_SCANCODE_K: return KEY_K;
			case SDL_SCANCODE_L: return KEY_L;
			case SDL_SCANCODE_M: return KEY_M;
			case SDL_SCANCODE_N: return KEY_N;
			case SDL_SCANCODE_O: return KEY_O;
			case SDL_SCANCODE_P: return KEY_P;
			case SDL_SCANCODE_Q: return KEY_Q;
			case SDL_SCANCODE_R: return KEY_R;
			case SDL_SCANCODE_S: return KEY_S;
			case SDL_SCANCODE_T: return KEY_T;
			case SDL_SCANCODE_U: return KEY_U;
			case SDL_SCANCODE_V: return KEY_V;
			case SDL_SCANCODE_W: return KEY_W;
			case SDL_SCANCODE_X: return KEY_X;
			case SDL_SCANCODE_Y: return KEY_Y;
			case SDL_SCANCODE_Z: return KEY_Z;
			
			case SDL_SCANCODE_1: return KEY_NUM_1;
			case SDL_SCANCODE_2: return KEY_NUM_2;
			case SDL_SCANCODE_3: return KEY_NUM_3;
			case SDL_SCANCODE_4: return KEY_NUM_4;
			case SDL_SCANCODE_5: return KEY_NUM_5;
			case SDL_SCANCODE_6: return KEY_NUM_6;
			case SDL_SCANCODE_7: return KEY_NUM_7;
			case SDL_SCANCODE_8: return KEY_NUM_8;
			case SDL_SCANCODE_9: return KEY_NUM_9;
			case SDL_SCANCODE_0: return KEY_NUM_0;

			case SDL_SCANCODE_RETURN: return KEY_ENTER;
			case SDL_SCANCODE_ESCAPE: return KEY_ESCAPE;
			case SDL_SCANCODE_BACKSLASH: return KEY_BACKSLASH;
			case SDL_SCANCODE_TAB: return KEY_TAB;
			case SDL_SCANCODE_SPACE: return KEY_SPACE;

			case SDL_SCANCODE_MINUS: return KEY_MINUS;
			case SDL_SCANCODE_EQUALS: return KEY_EQUAL;
			case SDL_SCANCODE_LEFTBRACKET: return KEY_LEFT_BRACKET;
			case SDL_SCANCODE_RIGHTBRACKET: return KEY_RIGHT_BRACKET;

			case SDL_SCANCODE_SEMICOLON: return KEY_SEMICOLON;
			case SDL_SCANCODE_APOSTROPHE: return KEY_APOSTROPHE;
			case SDL_SCANCODE_GRAVE: return KEY_GRAVE_ACCENT;

			case SDL_SCANCODE_COMMA: return KEY_COMMA;
			case SDL_SCANCODE_PERIOD: return KEY_PERIOD;
			case SDL_SCANCODE_SLASH: return KEY_SLASH;
			case SDL_SCANCODE_CAPSLOCK: return KEY_CAPS_LOCK;

			case SDL_SCANCODE_F1: return KEY_F1;
			case SDL_SCANCODE_F2: return KEY_F2;
			case SDL_SCANCODE_F3: return KEY_F3;
			case SDL_SCANCODE_F4: return KEY_F4;
			case SDL_SCANCODE_F5: return KEY_F5;
			case SDL_SCANCODE_F6: return KEY_F6;
			case SDL_SCANCODE_F7: return KEY_F7;
			case SDL_SCANCODE_F8: return KEY_F8;
			case SDL_SCANCODE_F9: return KEY_F9;
			case SDL_SCANCODE_F10: return KEY_F10;
			case SDL_SCANCODE_F11: return KEY_F11;
			case SDL_SCANCODE_F12: return KEY_F12;
			case SDL_SCANCODE_F13: return KEY_F13;
			case SDL_SCANCODE_F14: return KEY_F14;
			case SDL_SCANCODE_F15: return KEY_F15;
			case SDL_SCANCODE_F16: return KEY_F16;
			case SDL_SCANCODE_F17: return KEY_F17;
			case SDL_SCANCODE_F18: return KEY_F18;
			case SDL_SCANCODE_F19: return KEY_F19;
			case SDL_SCANCODE_F20: return KEY_F20;
			case SDL_SCANCODE_F21: return KEY_F21;
			case SDL_SCANCODE_F22: return KEY_F22;
			case SDL_SCANCODE_F23: return KEY_F23;
			case SDL_SCANCODE_F24: return KEY_F24;

			case SDL_SCANCODE_PRINTSCREEN: return KEY_PRINT_SCREEN;
			case SDL_SCANCODE_SCROLLLOCK: return KEY_SCROLL_LOCK;
			case SDL_SCANCODE_PAUSE: return KEY_PAUSE;
			case SDL_SCANCODE_INSERT: return KEY_INSERT;
			case SDL_SCANCODE_HOME: return KEY_HOME;
			case SDL_SCANCODE_PAGEUP: return KEY_PAGE_UP;
			case SDL_SCANCODE_PAGEDOWN: return KEY_PAGE_DOWN;
			case SDL_SCANCODE_DELETE: return KEY_DELETE;
			case SDL_SCANCODE_END: return KEY_END;
			case SDL_SCANCODE_RIGHT: return KEY_RIGHT;
			case SDL_SCANCODE_LEFT: return KEY_LEFT;
			case SDL_SCANCODE_UP: return KEY_UP;
			case SDL_SCANCODE_DOWN: return KEY_DOWN;

			case SDL_SCANCODE_KP_1: return KEY_KP_1;
			case SDL_SCANCODE_KP_2: return KEY_KP_2;
			case SDL_SCANCODE_KP_3: return KEY_KP_3;
			case SDL_SCANCODE_KP_4: return KEY_KP_4;
			case SDL_SCANCODE_KP_5: return KEY_KP_5;
			case SDL_SCANCODE_KP_6: return KEY_KP_6;
			case SDL_SCANCODE_KP_7: return KEY_KP_7;
			case SDL_SCANCODE_KP_8: return KEY_KP_8;
			case SDL_SCANCODE_KP_9: return KEY_KP_9;
			case SDL_SCANCODE_KP_0: return KEY_KP_0;

			case SDL_SCANCODE_KP_DIVIDE: return KEY_KP_DIVIDE;
			case SDL_SCANCODE_KP_MULTIPLY: return KEY_KP_MULTIPLY;
			case SDL_SCANCODE_KP_MINUS: return KEY_KP_SUBTRACT;
			case SDL_SCANCODE_KP_PLUS: return KEY_KP_ADD;
			case SDL_SCANCODE_KP_ENTER: return KEY_KP_ENTER;
			case SDL_SCANCODE_KP_EQUALS: return KEY_KP_EQUAL;

			case SDL_SCANCODE_LCTRL: return KEY_LEFT_CONTROL;
			case SDL_SCANCODE_LSHIFT: return KEY_LEFT_SHIFT;
			case SDL_SCANCODE_LALT: return KEY_LEFT_ALT;
			case SDL_SCANCODE_LGUI: return KEY_LEFT_SUPER;
			case SDL_SCANCODE_RCTRL: return KEY_RIGHT_CONTROL;
			case SDL_SCANCODE_RSHIFT: return KEY_RIGHT_SHIFT;
			case SDL_SCANCODE_RALT: return KEY_RIGHT_ALT;
			case SDL_SCANCODE_RGUI: return KEY_RIGHT_SUPER;
			default: return KEY_UNKNOWN;
		}
	}

	static MOUSE_BUTTON GetMouseButtonState(Uint8 mouseButton)
	{
		if( mouseButton == SDL_BUTTON_MASK(SDL_BUTTON_LEFT) )
			return MOUSE_BUTTON_LEFT;

		if( mouseButton == SDL_BUTTON_MASK(SDL_BUTTON_RIGHT) )
			return MOUSE_BUTTON_RIGHT;

		if( mouseButton == SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE) )
			return MOUSE_BUTTON_MIDDLE;
	}

	void SDL3_InputsPolling::SetTargetWindow(const std::shared_ptr<IWindow>& window)
	{
		s_Window = window;
		s_IsTargetWindowSet = true;
	}

	KEY_STATE SDL3_InputsPolling::GetKeyState(KEY key)
	{
		return s_KeyStateMapping [key];
	}

	MOUSE_BUTTON_STATE SDL3_InputsPolling::GetMouseState(MOUSE_BUTTON button)
	{
		return s_MouseButtonStateMapping [button];
	}

	glm::vec2 SDL3_InputsPolling::GetCurrentMousePosition()
	{
		glm::vec2 pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}

	void SDL3_InputsPolling::SetKeyState(Uint8 scanCode, KEY_STATE keyState)
	{
		s_KeyStateMapping [GetKey(scanCode)] = keyState;
	}

	void SDL3_InputsPolling::SetMouseButtonState(Uint8 button, MOUSE_BUTTON_STATE mouseButtonState)
	{
		s_MouseButtonStateMapping [GetMouseButtonState(button)] = mouseButtonState;
	}

	Native SDL3_InputsPolling::TargetWindow()
	{
		if( !s_IsTargetWindowSet )
			return nullptr;

		if( !s_Window.expired() )
			return s_Window.lock()->Window();

		TE_ASSERT(false, "The input handler targeting window is already destroyed.");
	}

}