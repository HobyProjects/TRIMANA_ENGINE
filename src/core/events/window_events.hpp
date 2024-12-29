#pragma once

#include "events.hpp"

namespace TE::Core
{
	class Event_Window_Close : public Events
	{
		public:
			Event_Window_Close() = default;
			virtual ~Event_Window_Close() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_CLOSE);
	};

	class Event_Window_Resize : public Events
	{
		public:
			Event_Window_Resize(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}
			virtual ~Event_Window_Resize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_RESIZE);

			uint32_t Width() const { return m_Width; }
			uint32_t Height() const { return m_Height; }

		private:
			uint32_t m_Width{ 0 };
			uint32_t m_Height{ 0 };
	};

	class Event_Window_Move : public Events
	{
		public:
			Event_Window_Move(uint32_t x, uint32_t y) : m_X(x), m_Y(y) {}
			virtual ~Event_Window_Move() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MOVED);

			uint32_t GetX() const { return m_X; }
			uint32_t GetY() const { return m_Y; }

		private:
			uint32_t m_X{ 0 };
			uint32_t m_Y{ 0 };
	};

	class Event_Window_FocusGain : public Events
	{
		public:
			Event_Window_FocusGain() = default;
			virtual ~Event_Window_FocusGain() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_FOCUS_GAIN);
	};

	class Event_Window_FocusLost : public Events
	{
		public:
			Event_Window_FocusLost() = default;
			virtual ~Event_Window_FocusLost() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_FOCUS_LOST);
	};

	class Event_Window_PixelSizeChange : public Events
	{
		public:
			Event_Window_PixelSizeChange(int32_t width, int32_t height) : m_Width(width), m_Height(height) {}
			virtual ~Event_Window_PixelSizeChange() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_PIXEL_SIZE_CHANGED);

			uint32_t Width() const { return m_Width; }
			uint32_t Height() const { return m_Height; }

		private:
			int32_t m_Width{ 0 };
			int32_t m_Height{ 0 };
	};

	class Event_Window_Maximaize : public Events
	{
		public:
			Event_Window_Maximaize() = default;
			virtual ~Event_Window_Maximaize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MAXIMIZED);
	};

	class Event_Window_Minimize : public Events
	{
		public:
			Event_Window_Minimize() = default;
			virtual ~Event_Window_Minimize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MINIMIZED);
	};

	class Event_Window_Restore : public Events
	{
		public:
			Event_Window_Restore() = default;
			virtual ~Event_Window_Restore() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_RESTORE);
	};
}