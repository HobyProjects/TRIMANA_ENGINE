#pragma once

#include <functional>
#include <type_traits>

#include "base.hpp"

namespace trimana::core
{

	enum class event_category
	{
		window = TRIMANA_BIT(0),
		keyboard = TRIMANA_BIT(1),
		mouse = TRIMANA_BIT(2),
		unknown = TRIMANA_BIT(3)
	};

	enum class event_type
	{
		window_close = TRIMANA_BIT(0),
		window_resize = TRIMANA_BIT(1),
		window_move = TRIMANA_BIT(2),
		window_focus_gain = TRIMANA_BIT(3),
		window_focus_lost = TRIMANA_BIT(4),
		window_pixel_size_change = TRIMANA_BIT(5),
		window_maximize = TRIMANA_BIT(6),
		window_minimize = TRIMANA_BIT(7),
		window_restore = TRIMANA_BIT(8),
		keyboard_key_press = TRIMANA_BIT(9),
		keyboard_key_release = TRIMANA_BIT(10),
		keyboard_key_repeat = TRIMANA_BIT(11),
		keyboard_key_char = TRIMANA_BIT(12),
		mouse_button_press = TRIMANA_BIT(13),
		mouse_button_release = TRIMANA_BIT(14),
		mouse_wheel = TRIMANA_BIT(15),
		mouse_cursor_moved = TRIMANA_BIT(16),
		mouse_cursor_enter = TRIMANA_BIT(17),
		mouse_cursor_leave = TRIMANA_BIT(18)
	};

	#define EVENT_CLASS_TYPE(type) static event_type get_static_type() { return type; } \
		virtual event_type get_event_type() const override { return get_static_type(); } \
		virtual const char* get_name() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual event_category get_category() const override { return category; }

	class events
	{
	public:
		events() = default;
		virtual ~events() = default;

		virtual event_type get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual event_category get_category() const = 0;

		bool is_in_category(event_category category) const
		{
			return static_cast<bool>( get_category() == category );
		}
	};

	class events_handler
	{
	public:
		events_handler(events& event) : m_event(event) {}
		~events_handler() = default;

		template<typename T>
		bool dispatch(const std::function<bool(T&)>& func)
		{
			if( m_event.get_event_type() == T::get_static_type() )
			{
				func(static_cast<T&>( m_event ));
				return true;
			}
			return false;
		}

	private:
		events& m_event;
	};

	using event_callback = std::function<void(events&)>;
}

#define TRIMANA_EVENT_CALLBACK(CALLBACK_FN) [this](auto&&... args) -> decltype(auto) { return this->CALLBACK_FN(std::forward<decltype(args)>(args)...); }