#pragma once

#include <memory>
#include <string>

#include "base.hpp"

namespace trimana::window
{
    enum class window_status
    {
        minimized       = 0,
        maximized       = 1,
        normal          = 2,
        fullscreen      = 3
    };

    struct TRIMANA_API window_specification
    {
        uint32_t width{0};
        uint32_t height{0};

        bool is_vsycn_enabled{false};
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

        window_status window_state{window_status::normal};
        std::string title{std::string()};
    };

    enum class platform_apis
    {
        default     = TRIMANA_BIT(0),
        glfw        = TRIMANA_BIT(1),
        sdl         = TRIMANA_BIT(2),
        windows     = TRIMANA_BIT(3)
    };

    class TRIMANA_API platform_api
    {
        public:
            platform_api() = default;
            virtual ~platform_api() = default;

            virtual bool init() = 0;
            virtual void quit() = 0;
            virtual platform_apis api() = 0;
    };

    class TRIMANA_API window
    {
        public:
            window() = default;
            virtual ~window() = default;

            virtual void* get_native_window() const = 0;
            virtual window_specification& get_window_specification() = 0;
            virtual void swap_buffers() = 0;
    };
}