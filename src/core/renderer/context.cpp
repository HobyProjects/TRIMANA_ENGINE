#include "renderer.hpp"
#include "context.hpp"
#include "exceptions.hpp"

#include "opengl/gl_context.hpp"

namespace trimana::core {
    std::shared_ptr<context> context::context_builder::create(void* native_window, rendering_api api){
        switch (api) {
        case rendering_api::opengl: 			return std::make_shared<gl_context>(native_window);
        case rendering_api::vulkan: 			throw not_implemented_exception("Vulkan is not implemented yet."); return nullptr;
		case rendering_api::directx: 			throw not_implemented_exception("DirectX is not implemented yet."); return nullptr;
		default: 								return nullptr;
        };
    }
}