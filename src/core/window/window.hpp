#pragma once

#include <memory>
#include <string>

#include "base.hpp"
#include "context.hpp"

namespace trimana::core {

	/**
	 * @enum window_state
	 * @brief Enum with the possible states a window can have.
	 */
	enum class window_state {
		fullscreen	= 0,		//< Fullscreen state.
		minimized	= 1,		//< Minimized state.
		maximized	= 2,		//< Maximized state.
		normal		= 3			//< Normal state.
	};


	/**
	 * @struct window_properties
	 * @brief Struct to store the properties of a window.
	 * @details This struct is used to store the properties of a window, such as its size, position, title and other settings.
	 */
	struct window_properties {
		std::string title{ "" };                                      /**< The title of the window. */
		uint32_t width{ 0 };                                          /**< Width of the window. */
		uint32_t height{ 0 };                                         /**< Height of the window. */
		uint32_t red_color_bits{ 8 };                                 /**< The number of red color bits. */
		uint32_t green_color_bits{ 8 };                               /**< The number of green color bits. */
		uint32_t blue_color_bits{ 8 };                                /**< The number of blue color bits. */
		uint32_t alpha_color_bits{ 8 };                               /**< The number of alpha color bits. */
		uint32_t depth_color_bits{ 24 };                              /**< The number of depth color bits. */
		uint32_t stencil_color_bits{ 8 };                             /**< The number of stencil color bits. */
		uint32_t refresh_rate{ 60 };                                  /**< The refresh rate of the window. */
		uint32_t fixed_width{ 0 };                                    /**< If the window has a fixed width, this is the value. */
		uint32_t fixed_height{ 0 };                                   /**< If the window has a fixed height, this is the value. */
		uint32_t min_width{ 1280 };                                   /**< The minimum width of the window. */
		uint32_t min_height{ 720 };                                   /**< The minimum height of the window. */
		uint32_t pos_x{ 0 };                                          /**< The x position of the window. */
		uint32_t pos_y{ 0 };                                          /**< The y position of the window. */
		int32_t framebuffer_width{ 0 };                               /**< The width of the framebuffer. */
		int32_t framebuffer_height{ 0 };                              /**< The height of the framebuffer. */
		window_state window_state{ window_state::maximized };         /**< The state of the window. */
		bool is_vsync_enabled{ false };                               /**< If vsync is enabled or not. */
		bool is_focused{ false };                                     /**< If the window is focused or not. */
		bool is_active{ false };                                      /**< If the window is active or not. */
	};


	/**
	 * @enum platform_service_apis
	 * @brief Enum representing different platform service APIs.
	 */
	enum class platform_service_apis {
		glfw_api = TRIMANA_BIT(1),  /**< GLFW API bit flag. */
		sdl_api = TRIMANA_BIT(2),  /**< SDL API bit flag. */
		win32_api = TRIMANA_BIT(3)   /**< Win32 API bit flag. */
	};

	/**
	 * @class platform_service_api
	 * @brief Abstract class representing a platform service API.
	 * @details This class provides the interface for initializing, quitting,
	 * and retrieving the type of platform service API being used.
	 */
	class platform_service_api {
	public:
		platform_service_api() = default;
		virtual ~platform_service_api() = default;

		/**
		 * @brief Initializes the platform service API.
		 * @return True if initialization was successful, otherwise false.
		 */
		virtual bool init() = 0;

		/**
		 * @brief Quits the platform service API.
		 */
		virtual void quit() = 0;

		/**
		 * @brief Retrieves the type of platform service API.
		 * @return The platform service API type.
		 */
		virtual platform_service_apis api() = 0;
	};

	/**
	 * @class window
	 * @brief Abstract class representing a window.
	 * @details This class provides the interface for retrieving the native window,
	 * retrieving the properties of the window, and swapping the window buffers.
	 */
	class window {
	public:
		window() = default;
		virtual ~window() = default;

		/**
		 * @brief Retrieves the native window.
		 * @return A pointer to the native window.
		 */
		virtual void* native_window() const = 0;

		/**
		 * @brief Retrieves the properties of the window.
		 * @return A pointer to the window properties.
		 */
		virtual window_properties* properties() = 0;

		/**
		 * @brief Swaps the window buffers.
		 */
		virtual void swap_buffers() const = 0;

		/**
		 * @brief Retrieves the window context.
		 * @return A pointer to the window context.
		 */
		virtual std::shared_ptr<context> window_context() const = 0;

	public:
		/**
		 * @class window_builder
		 * @brief Class used to create a window.
		 * @details This class provides a static method to create a window.
		 */
		class window_builder {
		private:
			window_builder() = default;
			~window_builder() = default;

		public:
			/**
			 * @brief Creates a window.
			 * @param title The title of the window.
			 * @param api The platform service API to use.
			 * @return A pointer to a window.
			 */
			static std::unique_ptr<window> create(const std::string& title, platform_service_apis api);
		};
	};
}