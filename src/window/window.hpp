#pragma once

#include <memory>
#include <string>

#include "base.hpp"

namespace Trimana::Window
{
    enum class WindowState
    {
        Minimized       = 0,
        Maximized       = 1,
        Normal          = 2
    };

    struct TRIMANA_API WindowSpecification
    {
        uint32_t Width{0};
        uint32_t Height{0};
        bool IsVSyncEnabled{false};
        bool IsActive{false};
        bool IsFocused{false};

        uint32_t RedColorBits{8};
        uint32_t GreenColorBits{8};
        uint32_t BlueColorBits{8};
        uint32_t AlphaColorBits{8};
        uint32_t DepthColorBits{24};
        uint32_t StencilColorBits{8};

        uint32_t RefreshRate{60};
        uint32_t FixedWidth{0};
        uint32_t FixedHeight{0};
        uint32_t MinWidth{1280};
        uint32_t MinHeight{720};

        uint32_t PosX{0};
        uint32_t PosY{0};

        int32_t FramebufferWidth{0};
        int32_t FramebufferHeight{0};

        WindowState WindowState{WindowState::Normal};
        std::string Title{std::string()};
    };

    enum class ServiceAPIs
    {
        None        = TRIMANA_BIT(0),
        GLFW        = TRIMANA_BIT(1),
        SDL         = TRIMANA_BIT(2),
        WIN_32      = TRIMANA_BIT(3)
    };
}