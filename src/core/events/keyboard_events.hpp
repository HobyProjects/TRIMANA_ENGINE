#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class EventKeyboardKeyPress : public Events
	{
		public:
			EventKeyboardKeyPress(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~EventKeyboardKeyPress() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYPRESS);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);

			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class EventKeyboardKeyRelease : public Events
	{
		public:
			EventKeyboardKeyRelease(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~EventKeyboardKeyRelease() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYRELEASE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class EventKeyboardKeyRepeate : public Events
	{
		public:
			EventKeyboardKeyRepeate(KEY keyCode) : m_KeyCode(keyCode) {}
			virtual ~EventKeyboardKeyRepeate() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYREPEATE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			KEY KeyCode() const { return m_KeyCode; }

		private:
			KEY m_KeyCode{ KEY_UNKNOWN };
	};

	class EventKeyboardKeyChar : public Events
	{
		public:
			EventKeyboardKeyChar(uint32_t character) : m_Character(character) {}
			virtual ~EventKeyboardKeyChar() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYCHAR);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			uint32_t CodePoint() const { return m_Character; }

		private:
			uint32_t m_Character{ 0 };
	};

	class EventKeyboardTextInput : public Events
	{
		public:
			EventKeyboardTextInput(const char* text) : m_Text(text) {}
			virtual ~EventKeyboardTextInput() = default;

			EVENT_CLASS_TYPE(EVENT_KEYBOARD_KEYCHAR);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD);
			const char* Text() const { return m_Text; }

		private:
			const char* m_Text{ nullptr };
	};
}