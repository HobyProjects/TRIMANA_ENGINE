#pragma once

#include "events.hpp"

namespace TE::Core
{
	class EventWindowClose : public Events
	{
		public:
			EventWindowClose() = default;
			virtual ~EventWindowClose() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_CLOSE);
	};

	class EventWindowResize : public Events
	{
		public:
			EventWindowResize(uint32_t width, uint32_t Height) : m_Width(width), m_Height(Height) {}
			virtual ~EventWindowResize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_RESIZE);

			uint32_t Width() const { return m_Width; }
			uint32_t Height() const { return m_Height; }

		private:
			uint32_t m_Width{ 0 };
			uint32_t m_Height{ 0 };
	};

	class EventWindowPosChange : public Events
	{
		public:
			EventWindowPosChange(uint32_t x, uint32_t y) : m_X(x), m_Y(y) {}
			virtual ~EventWindowPosChange() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MOVED);

			uint32_t GetX() const { return m_X; }
			uint32_t GetY() const { return m_Y; }

		private:
			uint32_t m_X{ 0 };
			uint32_t m_Y{ 0 };
	};

	class EventWindowFocusGain : public Events
	{
		public:
			EventWindowFocusGain() = default;
			virtual ~EventWindowFocusGain() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_FOCUS_GAIN);
	};

	class EventWindowFocusLost : public Events
	{
		public:
			EventWindowFocusLost() = default;
			virtual ~EventWindowFocusLost() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_FOCUS_LOST);
	};

	class EventWindowPixelSizeChange : public Events
	{
		public:
			EventWindowPixelSizeChange(int32_t width, int32_t Height) : m_Width(width), m_Height(Height) {}
			virtual ~EventWindowPixelSizeChange() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_PIXEL_SIZE_CHANGED);

			uint32_t Width() const { return m_Width; }
			uint32_t Height() const { return m_Height; }

		private:
			int32_t m_Width{ 0 };
			int32_t m_Height{ 0 };
	};

	class EventWindowMaximaize : public Events
	{
		public:
			EventWindowMaximaize() = default;
			virtual ~EventWindowMaximaize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MAXIMIZED);
	};

	class EventWindowMinimize : public Events
	{
		public:
			EventWindowMinimize() = default;
			virtual ~EventWindowMinimize() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_MINIMIZED);
	};

	class EventWindowRestore : public Events
	{
		public:
			EventWindowRestore() = default;
			virtual ~EventWindowRestore() = default;

			EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
			EVENT_CLASS_TYPE(EVENT_WINDOW_RESTORE);
	};
}