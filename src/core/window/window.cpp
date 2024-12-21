#include "glfw_window.hpp"

namespace trimana::core{
    
    std::unique_ptr<window> window_builder::create(const std::string& title, platform_service_apis api){
        switch(api){
            case platform_service_apis::glfw_api:{
                return std::make_unique<glfw_window>(title);
            }
            case platform_service_apis::sdl_api:{
                return nullptr;
            }
            case platform_service_apis::win32_api:{
                return nullptr;
            }
            default:{
                return nullptr;
            }
        };
    }
}