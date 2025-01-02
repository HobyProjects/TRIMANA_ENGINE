#include "application.hpp"
#include "renderer.hpp"
#include "exceptions.hpp"
#include "log.hpp"

namespace TE::App
{
	Application::Application()
	{
		try
		{
			TE::Core::Core::Init();
			m_window = TE::Core::Core::CreateWindow("Trimana Engine");
			m_window2 = TE::Core::Core::CreateWindow("Trimana Engine 2");
			TE::Core::Core::SetEventsCallbackFunc(TRIMANA_EVENT_CALLBACK(OnEvent));
		}
		catch( TE::Core::Exception& e )
		{
			e.What();
		}
	}

	Application::~Application()
	{
		TE::Core::Core::DestroyWindow(m_window);
		TE::Core::Core::DestroyWindow(m_window2);
		TE::Core::Core::Quit();
	}

	void Application::Run() const
	{
		while( TE::Core::Core::HasActiveWindow() )
		{
			TE::Core::Core::PollEvents();

			TE::Core::Renderer::Clear();
			TE::Core::Renderer::ClearColor({1.0f, 0.0f, 0.0f, 0.0f});

			TE::Core::Core::SwapBuffers();
		}
	}

	void Application::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& e)
	{
		TE::Core::EventsHandler handler(handle, e);
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::Event_Window_Close>(TRIMANA_EVENT_CALLBACK(OnWindowClose));
	}

	bool Application::OnWindowClose(TE::Core::WindowHandle handle, TE::Core::Event_Window_Close& e)
	{
		if( handle == m_window->GetWindowHandle() )
			m_window->Properties().IsActive = false;

		if( handle == m_window2->GetWindowHandle() )
			m_window2->Properties().IsActive = false;

		return true;
	}
}