#include "glfw_window.hpp"
#include "sdl_window.hpp"
#include "exceptions.hpp"

namespace trimana::core{
    
    std::unique_ptr<window> trimana::core::window::window_builder::create(const std::string & title, platform_service_apis api){
        switch(api){
            case platform_service_apis::glfw_api:{
                return std::make_unique<glfw_window>(title);
            }
            case platform_service_apis::sdl_api:{
                return std::make_unique<sdl_window>(title);
            }
            case platform_service_apis::win32_api:{
                throw not_implemented_exception("Win32 API is not implemented yet");
                return nullptr;
            }
            default:{
                return nullptr;
            }
        };
    }
}
