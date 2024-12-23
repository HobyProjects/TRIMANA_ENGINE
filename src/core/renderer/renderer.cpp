#include "opengl/gl_renderer.hpp"
#include "renderer.hpp"
#include "exceptions.hpp"

namespace trimana::core {

	static rendering_api s_api = rendering_api::opengl;

	void renderer::init() {
		switch (s_api) {
		case rendering_api::opengl: {
			gl_renderer::init();
			break;
		}
		case rendering_api::vulkan: {
			throw unimplemented_feature_exception("Vulkan renderer is not implemented yet");
			break;
		}
		case rendering_api::directx: {
			throw unimplemented_feature_exception("DirectX renderer is not implemented yet");
			break;
		}
		default: {
			gl_renderer::init();
			break;
		}
		};
	}

	void renderer::quit() {
		switch (s_api) {
		case rendering_api::opengl: {
			gl_renderer::quit();
			break;
		}
		case rendering_api::vulkan: {
			throw unimplemented_feature_exception("Vulkan renderer is not implemented yet");
			break;
		}
		case rendering_api::directx: {
			throw unimplemented_feature_exception("DirectX renderer is not implemented yet");
			break;
		}
		default: {
			gl_renderer::quit();
			break;
		}
		};
	}

	rendering_api renderer::api(){
		return s_api;
	}

	void renderer::change_api(rendering_api api){
		//[TODO]: Need to think about how to handle this
	}

	void renderer::clear() {
		switch (s_api) {
		case rendering_api::opengl: {
			gl_renderer::clear();
			break;
		}
		case rendering_api::vulkan: {
			throw unimplemented_feature_exception("Vulkan renderer is not implemented yet");
			break;
		}
		case rendering_api::directx: {
			throw unimplemented_feature_exception("DirectX renderer is not implemented yet");
			break;
		}
		default: {
			gl_renderer::clear();
			break;
		}
		};
	}

	void renderer::clear_color(const glm::vec4& color) {
		switch (s_api) {
		case rendering_api::opengl: {
			gl_renderer::clear_color(color);
			break;
		}
		case rendering_api::vulkan: {
			throw unimplemented_feature_exception("Vulkan renderer is not implemented yet");
			break;
		}
		case rendering_api::directx: {
			throw unimplemented_feature_exception("DirectX renderer is not implemented yet");
			break;
		}
		default: {
			gl_renderer::clear_color(color);
			break;
		}
		};
	}

	void renderer::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height) {
		switch (s_api) {
		case rendering_api::opengl: {
			gl_renderer::set_viewport(x, y, width, height);
			break;
		}
		case rendering_api::vulkan: {
			throw unimplemented_feature_exception("Vulkan renderer is not implemented yet");
			break;
		}
		case rendering_api::directx: {
			throw unimplemented_feature_exception("DirectX renderer is not implemented yet");
			break;
		}
		default: {
			gl_renderer::set_viewport(x, y, width, height);
			break;
		}
		};
	}
}