#pragma once

#include "events.hpp"
#include "key_codes.hpp"

namespace trimana::core
{
	class mouse_button_press_event : public events
	{
	public:
		mouse_button_press_event(mouse_button button) : m_button(button) {}
		virtual ~mouse_button_press_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_button_press);
		EVENT_CLASS_CATEGORY(event_category::mouse);

		mouse_button button() const { return m_button; }

	private:
		mouse_button m_button;
	};

	class mouse_button_release_event : public events
	{
	public:
		mouse_button_release_event(mouse_button button) : m_button(button) {}
		virtual ~mouse_button_release_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_button_release);
		EVENT_CLASS_CATEGORY(event_category::mouse);

		mouse_button button() const { return m_button; }

	private:
		mouse_button m_button;
	};

	class mouse_wheel_event : public events
	{
	public:
		mouse_wheel_event(float x_offset, float y_offset) : m_x_offset(x_offset), m_y_offset(y_offset) {}
		virtual ~mouse_wheel_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_wheel);
		EVENT_CLASS_CATEGORY(event_category::mouse);

		float x_offset() const { return m_x_offset; }
		float y_offset() const { return m_y_offset; }

	private:
		float m_x_offset, m_y_offset;
	};

	class mouse_cursor_moved_event : public events
	{
	public:
		mouse_cursor_moved_event(float x, float y) : m_x(x), m_y(y) {}
		virtual ~mouse_cursor_moved_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_cursor_moved);
		EVENT_CLASS_CATEGORY(event_category::mouse);

		float x() const { return m_x; }
		float y() const { return m_y; }

	private:
		float m_x, m_y;
	};

	class mouse_cursor_enter_event : public events
	{
	public:
		mouse_cursor_enter_event() = default;
		virtual ~mouse_cursor_enter_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_cursor_enter);
		EVENT_CLASS_CATEGORY(event_category::mouse);
	};

	class mouse_cursor_leave_event : public events
	{
	public:
		mouse_cursor_leave_event() = default;
		virtual ~mouse_cursor_leave_event() = default;

		EVENT_CLASS_TYPE(event_type::mouse_cursor_leave);
		EVENT_CLASS_CATEGORY(event_category::mouse);
	};
}