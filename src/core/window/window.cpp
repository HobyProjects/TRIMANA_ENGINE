#include "glfw_window.hpp"
#include "sdl_window.hpp"
#include "exceptions.hpp"

namespace trimana::core {

	std::unique_ptr<window> trimana::core::window::window_builder::create(const std::string& title, platform_service_apis api) {
		switch (api) {
		case platform_service_apis::glfw_api:				return std::make_unique<glfw_window>(title);
		case platform_service_apis::sdl_api:				return std::make_unique<sdl_window>(title);
		case platform_service_apis::win32_api:				throw not_implemented_exception("Win32 API is not implemented yet"); return nullptr;
		default:											return nullptr;
		};
	}

	static platform_service_apis s_service_api = platform_service_apis::glfw_api;

	platform_service_apis window::window_builder::get_platform_service_api()
	{
#ifdef TRIMANA_PLATFORM_WINDOWS
		//return platform_service_apis::win32_api; // Not implemented yet
		return s_service_api = platform_service_apis::glfw_api;

#elif defined(TRIMANA_PLATFORM_LINUX)
		return s_service_api = platform_service_apis::sdl_api;
#else
		return s_service_api = platform_service_apis::glfw_api;
#endif
	}

	void window::window_builder::change_service_api(platform_service_apis api)
	{
		//[TODO]: Need to think about how to change the service API
		// 01. identifying running services of the current service API (ex: window, inputs, events.. etc)
		// 02. quit from the current service API
		// 03. initialize the new service API
	}
}
