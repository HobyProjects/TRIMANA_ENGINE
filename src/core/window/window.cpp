#include "glfw_window.hpp"
#include "sdl_window.hpp"
#include "exceptions.hpp"

#include "opengl/glfw_gl_context.hpp"

namespace trimana::core {

	static std::once_flag s_platform_service_api_flag;
	static std::shared_ptr<platform_service_api> s_platform_service_api = nullptr;

	static platform_service_apis service_api() {
#ifdef TRIMANA_PLATFORM_WINDOWS
		//return platform_service_apis::win32_api; // [TODO]: Implement Win32 API
		return platform_service_apis::glfw_api;
#elif defined(TRIMANA_PLATFORM_LINUX)
		return platform_service_apis::sdl_api;
#else
		return platform_service_apis::glfw_api;
#endif
	}

	std::unique_ptr<window> trimana::core::window::window_builder::create(const std::string& title) {
		switch (service_api()) {
		case platform_service_apis::glfw_api:				return std::make_unique<glfw_window>(title, s_platform_service_api);
		case platform_service_apis::sdl_api:				return std::make_unique<sdl_window>(title);
		case platform_service_apis::win32_api:				throw unimplemented_feature_exception("Win32 API is not implemented yet"); return nullptr;
		default:											return nullptr;
		};
	}

	const std::shared_ptr<platform_service_api>& window::window_builder::get_platform_service_api()
	{
		std::call_once(s_platform_service_api_flag, []() {
			switch (service_api()) {
			case platform_service_apis::glfw_api: {
				s_platform_service_api = std::make_shared<glfw_service_api>();
				if (!s_platform_service_api->init()) {
					throw uninitialized_object_exception("Failed to initialize the platform service API : GLFW");
				}
				break;
			}
			case platform_service_apis::sdl_api: {
				s_platform_service_api = std::make_shared<sdl_service_api>();
				if (!s_platform_service_api->init()) {
					throw uninitialized_object_exception("Failed to initialize the platform service API : SDL");
				}
				break;
			}
			case platform_service_apis::win32_api: {
				throw unimplemented_feature_exception("Win32 API is not implemented yet");
				break;
			}
			default: {
				s_platform_service_api = std::make_shared<glfw_service_api>();
				if (!s_platform_service_api->init()) {
					throw uninitialized_object_exception("Failed to initialize the platform service API : GLFW");
				}
				break;
			}
			};

		});

		return s_platform_service_api;
	}

	std::shared_ptr<context> context::context_builder::create(void* native_window, rendering_api api)
	{
		if (s_platform_service_api->api() == platform_service_apis::glfw_api) {
			switch (api) {
			case rendering_api::opengl: return std::make_shared<glfw_gl_context>(native_window);
			case rendering_api::vulkan: throw unimplemented_feature_exception("Vulkan API is not implemented yet"); return nullptr;
			case rendering_api::directx: throw unimplemented_feature_exception("DirectX API is not implemented yet"); return nullptr;
			default: return nullptr;
			}
		}

		if (s_platform_service_api->api() == platform_service_apis::sdl_api) {
			switch (api) {
			case rendering_api::opengl: throw unimplemented_feature_exception("OpenGL API is not implemented yet"); return nullptr;
			case rendering_api::vulkan: throw unimplemented_feature_exception("Vulkan API is not implemented yet"); return nullptr;
			case rendering_api::directx: throw unimplemented_feature_exception("DirectX API is not implemented yet"); return nullptr;
			default: return nullptr;
			}
		}

		if (s_platform_service_api->api() == platform_service_apis::win32_api) {
			throw unimplemented_feature_exception("Win32 API is not implemented yet");
			return nullptr;
		}
	}
}
