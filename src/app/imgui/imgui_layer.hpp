#pragma once

#include "tgui.hpp"
#include "events.hpp"
#include "window_events.hpp"
#include "application_layer.hpp"

namespace TE::App
{
    enum class ImGuiColorScheme
    {
        Light,
        Dark,
    };

    class ImGuiLayer final : public ApplicationLayers
    {
        public:
            ImGuiLayer() : ApplicationLayers("ImGuiLayer") {}
            ImGuiLayer(const std::shared_ptr<TE::Core::IWindow>& window, ImGuiColorScheme colorScheme = ImGuiColorScheme::Dark);
            virtual ~ImGuiLayer() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& event) override;

            void Begin();
            void End();
            void AllowEvents(bool allowEvents) { m_AllowEvents = allowEvents; };
            void UseColorScheme(ImGuiColorScheme colorScheme);

        private:
            std::shared_ptr<TE::Core::IWindow> m_Window{ nullptr };
            ImGuiColorScheme m_ColorScheme{ ImGuiColorScheme::Dark };
            bool m_AllowEvents{ false };
    };
}