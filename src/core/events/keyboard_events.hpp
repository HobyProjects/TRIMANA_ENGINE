#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class Event_Keyboard_KeyPress : public Events
	{
		public:
			Event_Keyboard_KeyPress(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~Event_Keyboard_KeyPress() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYPRESS);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);

			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class Event_Keyboard_KeyRelease : public Events
	{
		public:
			Event_Keyboard_KeyRelease(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~Event_Keyboard_KeyRelease() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYRELEASE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class Event_Keyboard_KeyRepeate : public Events
	{
		public:
			Event_Keyboard_KeyRepeate(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~Event_Keyboard_KeyRepeate() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYREPEATE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class Event_Keyboard_KeyChar : public Events
	{
		public:
			Event_Keyboard_KeyChar(uint32_t character) : m_Character(character) {}
			virtual ~Event_Keyboard_KeyChar() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYCHAR);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			uint32_t CodePoint() const { return m_Character; }

		private:
			uint32_t m_Character{ 0 };
	};

	class Event_Keyboard_TextInput : public Events
	{
		public:
			Event_Keyboard_TextInput(const char* text) : m_Text(text) {}
			virtual ~Event_Keyboard_TextInput() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYCHAR);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			const char* Text() const { return m_Text; }

		private:
			const char* m_Text{ nullptr };
	};
}