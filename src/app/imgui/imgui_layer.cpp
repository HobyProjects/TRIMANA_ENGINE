#include "app_pch.hpp"

namespace TE::App
{
	TE::App::ImGuiLayer::ImGuiLayer(const std::shared_ptr<TE::Core::IWindow>& window, ImGuiColorScheme colorScheme):
		ApplicationLayers("ImguiLayer"), m_Window(window), m_ColorScheme(colorScheme) {}

    void ImGuiLayer::OnAttach()
    {
        if( IMGUI_Init(m_Window) )
            TE_INFO("IMGUI initialized successfully");

        ( m_ColorScheme == ImGuiColorScheme::Dark ) ? IMGUI_UseColorDark() : IMGUI_UseColorLight();
    }

    void ImGuiLayer::OnDetach()
    {
        IMGUI_Quit();
    }

    void ImGuiLayer::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& event)
    {
        if( m_AllowEvents )
        {
            ImGuiIO& io = ImGui::GetIO();
            event.InCategory(TE::Core::EVENT_CATEGORY_KEYBOARD) & io.WantCaptureKeyboard;
            event.InCategory(TE::Core::EVENT_CATEGORY_MOUSE) & io.WantCaptureMouse;
        }
    }

    void ImGuiLayer::Begin()
    {
        if( ( TE::Core::Core::GetBaseAPI() & TE::Core::API_GLFW ) && ( TE::Core::Renderer::API() & TE::Core::RENDERER_API_OPENGL ) )
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        if( ( TE::Core::Core::GetBaseAPI() & TE::Core::API_SDL ) && ( TE::Core::Renderer::API() & TE::Core::RENDERER_API_OPENGL ) )
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
        }
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>( m_Window->Properties().Width ), static_cast<float>( m_Window->Properties().Height ));

        if( ( TE::Core::Core::GetBaseAPI() & TE::Core::API_GLFW ) && ( TE::Core::Renderer::API() & TE::Core::RENDERER_API_OPENGL ) )
        {
            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }

        if( ( TE::Core::Core::GetBaseAPI() & TE::Core::API_SDL ) && ( TE::Core::Renderer::API() & TE::Core::RENDERER_API_OPENGL ) )
        {
            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
            {
                SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
                SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
            }
        }
    }

    void ImGuiLayer::UseColorScheme(ImGuiColorScheme colorScheme)
    {
        ( colorScheme == ImGuiColorScheme::Dark ) ? IMGUI_UseColorDark() : IMGUI_UseColorLight();
        m_ColorScheme = colorScheme;
    }



}