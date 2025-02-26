#include "app_pch.hpp"

namespace TE::App
{
	static Application* s_ApplicationInstance = nullptr;

	Application::Application()
	{
		s_ApplicationInstance = this;
		TE::Core::Core::Init();
		m_Window = TE::Core::Core::CreateWindow("Trimana Engine");
		m_Window->SetEventsCallbackFunc(EVENT_CALLBACK(OnEvent));
		TE::Core::Core::InitRenderer(); //NOTE: Always init the renderer after creating the main window
	}

	Application::~Application()
	{
		TE::Core::Core::QuitRenderer();
		TE::Core::Core::Quit();
	}

	void Application::Run() const
	{
		while( m_Window->IsActive() )
		{
			m_Window->PollEvents();
			TE::Core::Renderer::Clear();
			TE::Core::Renderer::ClearColor({ 0.243f, 0.243f, 0.243f, 1.0f });

			if( m_Window->Properties().WindowState != TE::Core::WINDOW_MINIMIZED )
			{
				float currentTime{ 0.0f };
				static float lastFrameTime{ 0.0f };
				currentTime = TE::Core::Core::GetSystemTicks();

				TE::Core::DeltaTime deltaTime = currentTime - lastFrameTime;
				lastFrameTime = currentTime;

				for( auto& layers : *m_LayerStack )
				{
					layers->OnUpdate(deltaTime);
				}
			}



			m_Window->SwapBuffers();
		}
	}

	void Application::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& e)
	{
		TE::Core::EventsHandler handler(handle, e);
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventWindowClose>(EVENT_CALLBACK(OnWindowClose));
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventWindowResize>(EVENT_CALLBACK(OnWindowResize));

		for( std::vector<std::shared_ptr<ApplicationLayers>>::reverse_iterator it = m_LayerStack->rbegin(); it != m_LayerStack->rend(); ++it )
		{
			if( handler.IsHandled() )
				break;

			( *it )->OnEvent(e);
		}
	}

	void Application::PushLayer(const std::shared_ptr<ApplicationLayers>& applicationLayer)
	{
		applicationLayer->OnAttach();
		m_LayerStack->PushLayer(applicationLayer);
	}

	void Application::PushOverlay(const std::shared_ptr<ApplicationLayers>& applicationLayer)
	{
		applicationLayer->OnAttach();
		m_LayerStack->PushOverlay(applicationLayer);
	}

	TE::Core::Native Application::GetNativeWindow()
	{
		return s_ApplicationInstance->m_Window->Window();
	}

	Application* Application::GetApplicationInstance()
	{
		return s_ApplicationInstance;
	}

	bool Application::OnWindowClose(TE::Core::WindowHandle handle, TE::Core::EventWindowClose& e)
	{
		if( handle == m_Window->GetWindowHandle() )
			m_Window->Properties().IsActive = false;

		return true;
	}

	bool Application::OnWindowResize(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e)
	{
		if( !m_Window->Properties().WindowState & TE::Core::WINDOW_MINIMIZED )
			TE::Core::Renderer::SetViewport(NULL, NULL, e.Width(), e.Height());

		return false;
	}
}