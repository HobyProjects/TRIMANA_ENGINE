#pragma once

#include <string_view>
#include <functional>
#include <type_traits>

#include "base.hpp"

namespace TE::Core
{
	enum EVENT_CATEGORY : uint32_t
	{
		EVENT_CATEGORY_WINDOW 		= TE_BIT(0),
		EVENT_CATEGORY_KEYBOARD 	= TE_BIT(1),
		EVENT_CATEGORY_MOUSE 		= TE_BIT(2),
		EVENT_CATEGORY_GAMEPAD		= TE_BIT(3),
		EVENT_CATEGORY_UNKNOWN 		= TE_BIT(4)
	};

	enum EVENT_TYPE : uint32_t
	{
		EVENT_WINDOW_CLOSE 				= TE_BIT(0),
		EVENT_WINDOW_RESIZE 			= TE_BIT(1),
		EVENT_WINDOW_MOVED 				= TE_BIT(2),
		EVENT_WINDOW_FOCUS_GAIN 		= TE_BIT(3),
		EVENT_WINDOW_FOCUS_LOST 		= TE_BIT(4),
		EVENT_WINDOW_PIXEL_SIZE_CHANGED = TE_BIT(5),
		EVENT_WINDOW_MAXIMIZED 			= TE_BIT(6),
		EVENT_WINDOW_MINIMIZED 			= TE_BIT(7),
		EVENT_WINDOW_RESTORE 			= TE_BIT(8),

		EVENT_KEYBOARD_KEYPRESS 		= TE_BIT(9),
		EVENT_KEYBOARD_KEYRELEASE 		= TE_BIT(10),
		EVENT_KEYBOARD_KEYREPEATE 		= TE_BIT(11),
		EVENT_KEYBOARD_KEYCHAR 			= TE_BIT(12),

		EVENT_MOUSE_BUTTON_DOWN 		= TE_BIT(13),
		EVENT_MOUSE_BUTTON_UP 			= TE_BIT(14),
		EVENT_MOUSE_WHEEL 				= TE_BIT(15),
		EVENT_MOUSE_CURSOR_MOVED 		= TE_BIT(16),
		EVENT_MOUSE_CURSOR_WINDOW_ENTER = TE_BIT(17),
		EVENT_MOUSE_CURSOR_WINDOW_LEAVE = TE_BIT(18)
	};

	#define EVENT_CLASS_TYPE(ty) static EVENT_TYPE StaticType() { return ty; } \
		virtual EVENT_TYPE Type() const override { return StaticType(); } \
		virtual std::string_view What() const override { return std::string_view(#ty); }

	#define EVENT_CLASS_CATEGORY(cat) virtual EVENT_CATEGORY Category() const override { return cat; }

	class Events
	{
		public:
			Events() = default;
			virtual ~Events() = default;

			virtual EVENT_TYPE Type() const = 0;
			virtual std::string_view What() const = 0;
			virtual EVENT_CATEGORY Category() const = 0;

			bool InCategory(EVENT_CATEGORY cat) const
			{
				return static_cast<bool>( Category() & cat );
			}
	};

	class EventsHandler
	{
		public:
			EventsHandler(uint32_t handle, Events& event) : m_Handle(handle), m_Event(event) {}
			~EventsHandler() = default;

			template<typename THandle, typename TEvent>
			bool Dispatch(const std::function<bool(THandle, TEvent&)>& func)
			{
				if( m_Event.Type() == TEvent::StaticType() )
				{
					m_IsHandled |= func(m_Handle, static_cast<TEvent&>( m_Event ));
					return m_IsHandled;
				}

				return m_IsHandled;
			}

			bool IsHandled() const { return m_IsHandled; }

		private:
			Events& m_Event;
			uint32_t m_Handle;
			bool m_IsHandled{ false };
	};
}

#define TRIMANA_EVENT_CALLBACK(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
