#pragma once

#include <memory>
#include <string>

#include "base.hpp"

namespace trimana::core{

    enum class window_state {
        fullscreen,  
        minimized,    
        maximized     
    };

    struct window_properties{
        uint32_t width{0};
        uint32_t height{0};

        bool is_vsync_enabled{false};
        bool is_active{false};
        bool is_focused{false};

        uint32_t red_color_bits{8};
        uint32_t green_color_bits{8};
        uint32_t blue_color_bits{8};
        uint32_t alpha_color_bits{8};
        uint32_t depth_color_bits{24};
        uint32_t stencil_color_bits{8};

        uint32_t refresh_rate{60};
        uint32_t fixed_width{0};
        uint32_t fixed_height{0};
        uint32_t min_width{1280};
        uint32_t min_height{720};

        uint32_t pos_x{0};
        uint32_t pos_y{0};
        int32_t framebuffer_width{0};
        int32_t framebuffer_height{0};

        window_state window_state{window_state::maximized};
        std::string title{""};
    };

    enum class platform_service_apis{
        glfw_api        = TRIMANA_BIT(1),
        sdl_api         = TRIMANA_BIT(2),
        win32_api       = TRIMANA_BIT(3)
    };

    class TRIMANA_API platform_service_api{
        public:
            platform_service_api() = default;
            virtual ~platform_service_api() = default;
            
            virtual bool init() = 0;
            virtual void quit() = 0;
            virtual platform_service_apis get_api() = 0;
    };

    class TRIMANA_API window{
        public:
            window() = default;
            virtual ~window() = default;

            virtual void* get_native_window() const = 0;
            virtual window_properties& get_window_properties() = 0;
            virtual void swap_buffers() = 0;
    };

    TRIMANA_API std::shared_ptr<platform_service_api> get_platform_service_api();
    TRIMANA_API std::shared_ptr<window> create_window(const std::string& title, platform_service_apis api);
}