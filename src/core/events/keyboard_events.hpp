#pragma once

#include "events.hpp"
#include "key_codes.hpp"

namespace trimana::core
{
	class keyboard_keypress_event : public events
	{
	public:
		keyboard_keypress_event(key key_code) : key_code(key_code) {}
		virtual ~keyboard_keypress_event() = default;

		EVENT_CLASS_TYPE(event_type::keyboard_key_press);
		EVENT_CLASS_CATEGORY(event_category::keyboard);

		key keycode() const { return key_code; }
	private:
		key key_code;
	};

	class keyboard_keyrelease_event : public events
	{
	public:
		keyboard_keyrelease_event(key key_code) : key_code(key_code) {}
		virtual ~keyboard_keyrelease_event() = default;

		EVENT_CLASS_TYPE(event_type::keyboard_key_release);
		EVENT_CLASS_CATEGORY(event_category::keyboard);

		key keycode() const { return key_code; }
	private:
		key key_code;
	};

	class keyboard_keyrepeat_event : public events
	{
	public:
		keyboard_keyrepeat_event(key key_code) : key_code(key_code) {}
		virtual ~keyboard_keyrepeat_event() = default;

		EVENT_CLASS_TYPE(event_type::keyboard_key_repeat);
		EVENT_CLASS_CATEGORY(event_category::keyboard);

		key keycode() const { return key_code; }
	private:
		key key_code;
	};

	class keyboard_keychar_event : public events
	{
	public:
		keyboard_keychar_event(uint32_t character) : character(character) {}
		virtual ~keyboard_keychar_event() = default;

		EVENT_CLASS_TYPE(event_type::keyboard_key_char);
		EVENT_CLASS_CATEGORY(event_category::keyboard);

		uint32_t codepoint() const { return character; }
	private:
		uint32_t character;
	};

	class keyboard_textinput_event : public events
	{
	public:
		keyboard_textinput_event(const char* text) : m_text(text) {}
		virtual ~keyboard_textinput_event() = default;

		EVENT_CLASS_TYPE(event_type::keyboard_key_char);
		EVENT_CLASS_CATEGORY(event_category::keyboard);

		const char* text() const { return m_text; }
	private:
		const char* m_text;
	};
}