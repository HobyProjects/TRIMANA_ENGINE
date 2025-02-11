#include "app_pch.hpp"

namespace TE::App
{
	Application::Application()
	{
		TE::Core::Core::Init();
		m_window = TE::Core::Core::CreateWindow("Trimana Engine");
		m_window->SetEventsCallbackFunc(EVENT_CALLBACK(OnEvent));

		//NOTE: Always init the renderer after creating the main window
		TE::Core::Core::InitRenderer();
	}

	Application::~Application()
	{
		TE::Core::Core::DestroyWindow(m_window);
		TE::Core::Core::QuitRenderer();
		TE::Core::Core::Quit();
	}

	void Application::Run() const
	{
		while( m_window->IsActive() )
		{
			m_window->PollEvents();
			TE::Core::Renderer::Clear();
			TE::Core::Renderer::ClearColor({ 0.243f, 0.243f, 0.243f, 1.0f });





			m_window->SwapBuffers();
		}
	}

	void Application::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& e)
	{
		TE::Core::EventsHandler handler(handle, e);
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventWindowClose>(EVENT_CALLBACK(OnWindowClose));
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventWindowResize>(EVENT_CALLBACK(OnWindowResize));
	}

	bool Application::OnWindowClose(TE::Core::WindowHandle handle, TE::Core::EventWindowClose& e)
	{
		if( handle == m_window->GetWindowHandle() )
			m_window->Properties().IsActive = false;

		return true;
	}

	bool Application::OnWindowResize(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e)
	{
		if( !m_window->Properties().WindowState & TE::Core::WINDOW_MINIMIZED )
			TE::Core::Renderer::SetViewport(NULL, NULL, e.Width(), e.Height());

		return false;
	}
}