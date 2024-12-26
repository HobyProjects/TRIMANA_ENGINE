#pragma once

#include "events.hpp"

namespace trimana::core
{

	class window_close_event : public events
	{
	public:
		window_close_event() = default;
		virtual ~window_close_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_close);
	};

	class window_resize_event : public events
	{
	public:
		window_resize_event(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}
		virtual ~window_resize_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_resize);

		inline uint32_t width() const { return m_width; }
		inline uint32_t height() const { return m_height; }

	private:
		uint32_t m_width{ 0 };
		uint32_t m_height{ 0 };
	};

	class window_move_event : public events
	{
	public:
		window_move_event(uint32_t x, uint32_t y) : m_x(x), m_y(y) {}
		virtual ~window_move_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_move);

		inline uint32_t x() const { return m_x; }
		inline uint32_t y() const { return m_y; }

	private:
		uint32_t m_x{ 0 };
		uint32_t m_y{ 0 };
	};

	class window_focus_gain_event : public events
	{
	public:
		window_focus_gain_event() = default;
		virtual ~window_focus_gain_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_focus_gain);
	};

	class window_focus_lost_event : public events
	{
	public:
		window_focus_lost_event() = default;
		virtual ~window_focus_lost_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_focus_lost);
	};

	class window_pixel_size_change_event : public events
	{
	public:
		window_pixel_size_change_event(int32_t width, int32_t height) : m_width(width), m_height(height) {}
		virtual ~window_pixel_size_change_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_pixel_size_change);

		inline uint32_t width() const { return m_width; }
		inline uint32_t height() const { return m_height; }
	private:
		int32_t m_width{ 0 };
		int32_t m_height{ 0 };
	};

	class window_maximize_event : public events
	{
	public:
		window_maximize_event() = default;
		virtual ~window_maximize_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_maximize);
	};

	class window_minimize_event : public events
	{
	public:
		window_minimize_event() = default;
		virtual ~window_minimize_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_minimize);
	};

	class window_restore_event : public events
	{
	public:
		window_restore_event() = default;
		virtual ~window_restore_event() = default;

		EVENT_CLASS_CATEGORY(event_category::window);
		EVENT_CLASS_TYPE(event_type::window_restore);
	};
}