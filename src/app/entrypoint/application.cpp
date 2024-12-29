#include "application.hpp"
#include "renderer.hpp"
#include "exceptions.hpp"
#include "log.hpp"

namespace TE::app
{
	application::application()
	{
		try
		{
			m_window = TE::Core::create_window("Trimana Engine");
			m_events_receiver = TE::Core::create_event_receiver(m_window, TRIMANA_EVENT_CALLBACK(on_events));
			TE::Core::Renderer::Init();
		}
		catch( TE::Core::exception& e )
		{
			e.what();
		}
	}

	application::~application()
	{
		TE::Core::Renderer::Quit();
		m_window->base()->quit();
	}

	void application::run() const
	{
		while( m_window->properties()->is_active )
		{
			m_events_receiver->poll_events();

			TE::Core::Renderer::Clear();
			TE::Core::Renderer::ClearColor({ 1.0f, 0.0f, 0.0f, 0.0f });

			m_window->swap_buffers();
		}
	}

	void application::on_events(TE::Core::Events& e)
	{
		TE::Core::EventsHandler handler(e);
		handler.dispatch<TE::Core::window_close_event>(TRIMANA_EVENT_CALLBACK(on_window_close));
	}

	bool application::on_window_close(TE::Core::window_close_event& e)
	{
		if( m_window->properties()->is_active )
			m_window->properties()->is_active = false;

		return true;
	}
}