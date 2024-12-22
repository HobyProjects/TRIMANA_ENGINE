#include "sdl_window.hpp"
#include "log.hpp"

namespace trimana::core{

    bool sdl_service_api::init() {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
            TRIMANA_CORE_CRITICAL("Failed to initialize SDL");
            return (m_initialized = false);
        }

        TRIMANA_CORE_INFO("SDL initialized successfully");
        return (m_initialized = true);
    }

    void sdl_service_api::quit() {
        if(m_initialized){
            SDL_Quit();
            m_initialized = false;
        }
    }

    sdl_window::sdl_window(const std::string& title) {
        const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
        if(mode != nullptr){
            m_properties.width = mode->w;
            m_properties.height = mode->h;
            m_properties.fixed_width = mode->w;
            m_properties.fixed_height = mode->h;
            m_properties.min_width = 1024;
            m_properties.min_height = 720;
            m_properties.red_color_bits = 8;
            m_properties.green_color_bits = 8;
            m_properties.blue_color_bits = 8;
            m_properties.alpha_color_bits = 8;
            m_properties.refresh_rate = mode->refresh_rate;
            m_properties.stencil_color_bits = 8;
            m_properties.depth_color_bits = 24;

        }else{
            TRIMANA_CORE_WARN("Failed to get display mode, using default values");
            m_properties.width = 1280;
            m_properties.height = 720;
            m_properties.fixed_width = 0;
            m_properties.fixed_height = 0;
            m_properties.min_width = 1024;
            m_properties.min_height = 720;
            m_properties.red_color_bits = 8;
            m_properties.green_color_bits = 8;
            m_properties.blue_color_bits = 8;
            m_properties.alpha_color_bits = 8;
            m_properties.refresh_rate = 60;
            m_properties.stencil_color_bits = 8;
            m_properties.depth_color_bits = 24;
        }

        m_properties.title = title;
    }
}