#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class Event_Mouse_ButtonDown : public Events
	{
		public:
			Event_Mouse_ButtonDown(MOUSE_BUTTON button) : m_Button(button) {}
			virtual ~Event_Mouse_ButtonDown() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_BUTTON_DOWN);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			MOUSE_BUTTON Button() const { return m_Button; }

		private:
			MOUSE_BUTTON m_Button{ KEY_UNKNOWN };
	};

	class Event_Mouse_ButtonUp : public Events
	{
		public:
			Event_Mouse_ButtonUp(MOUSE_BUTTON button) : m_Button(button) {}
			virtual ~Event_Mouse_ButtonUp() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_BUTTON_UP);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			MOUSE_BUTTON Button() const { return m_Button; }

		private:
			MOUSE_BUTTON m_Button{ KEY_UNKNOWN };
	};

	class Event_Mouse_WheelScroll : public Events
	{
		public:
			Event_Mouse_WheelScroll(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}
			virtual ~Event_Mouse_WheelScroll() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_WHEEL);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			float OffsetX() const { return m_OffsetX; }
			float OffsetY() const { return m_OffsetY; }

		private:
			float m_OffsetX{ 0.0f }, m_OffsetY{ 0.0f };
	};

	class Event_Mouse_CursorMove : public Events
	{
		public:
			Event_Mouse_CursorMove(float x, float y) : m_X(x), m_Y(y) {}
			virtual ~Event_Mouse_CursorMove() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_MOVED);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			float GetX() const { return m_X; }
			float GetY() const { return m_Y; }

		private:
			float m_X{ 0.0f }, m_Y{ 0.0f };
	};

	class Event_Mouse_CursorWindowEnter : public Events
	{
		public:
			Event_Mouse_CursorWindowEnter() = default;
			virtual ~Event_Mouse_CursorWindowEnter() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_WINDOW_ENTER);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);
	};

	class Event_Mouse_CursorWindowLeave : public Events
	{
		public:
			Event_Mouse_CursorWindowLeave() = default;
			virtual ~Event_Mouse_CursorWindowLeave() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_WINDOW_LEAVE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);
	};
}