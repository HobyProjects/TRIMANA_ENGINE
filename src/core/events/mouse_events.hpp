#pragma once

#include "events.hpp"
#include "keycodes.hpp"

namespace TE::Core
{
	class EventMouseButtonDown : public Events
	{
		public:
			EventMouseButtonDown(MOUSE_BUTTON button) : m_Button(button) {}
			virtual ~EventMouseButtonDown() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_BUTTON_DOWN);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			MOUSE_BUTTON Button() const { return m_Button; }

		private:
			MOUSE_BUTTON m_Button{ KEY_UNKNOWN };
	};

	class EventMouseButtonUp : public Events
	{
		public:
			EventMouseButtonUp(MOUSE_BUTTON button) : m_Button(button) {}
			virtual ~EventMouseButtonUp() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_BUTTON_UP);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			MOUSE_BUTTON Button() const { return m_Button; }

		private:
			MOUSE_BUTTON m_Button{ KEY_UNKNOWN };
	};

	class EventMouseWheelScroll : public Events
	{
		public:
			EventMouseWheelScroll(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}
			virtual ~EventMouseWheelScroll() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_WHEEL);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			float OffsetX() const { return m_OffsetX; }
			float OffsetY() const { return m_OffsetY; }

		private:
			float m_OffsetX{ 0.0f }, m_OffsetY{ 0.0f };
	};

	class EventMouseCursorMove : public Events
	{
		public:
			EventMouseCursorMove(float x, float y) : m_X(x), m_Y(y) {}
			virtual ~EventMouseCursorMove() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_MOVED);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);

			float GetX() const { return m_X; }
			float GetY() const { return m_Y; }

		private:
			float m_X{ 0.0f }, m_Y{ 0.0f };
	};

	class EventMouseCursorWindowEnter : public Events
	{
		public:
			EventMouseCursorWindowEnter() = default;
			virtual ~EventMouseCursorWindowEnter() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_WINDOW_ENTER);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);
	};

	class EventMouseCursorWindowLeave : public Events
	{
		public:
			EventMouseCursorWindowLeave() = default;
			virtual ~EventMouseCursorWindowLeave() = default;

			EVENT_CLASS_TYPE(EVENT_MOUSE_CURSOR_WINDOW_LEAVE);
			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE);
	};
}