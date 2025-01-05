#include "application.hpp"

std::string vertexSrc = R"(
#version 450 core

layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

std::string fragSrc = R"(
#version 450 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}
)";

float vertices[] = 
{
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
};

unsigned int indices[] = 
{  
	0, 1, 2,
	2, 3, 0
};

namespace TE::App
{
	Application::Application()
	{
		try
		{
			TE::Core::Core::Init();
			m_window = TE::Core::Core::CreateWindow("Trimana Engine");
			m_window->SetEventsCallbackFunc(EVENT_CALLBACK(OnEvent));

			m_Shader = TE::Core::CreateShaderProgram("TestShaderProgram", vertexSrc, fragSrc);
			m_VBO = TE::Core::CreateVertexBuffer(vertices, sizeof(vertices));
			m_IBO = TE::Core::CreateIndexBuffer(indices, 6);
			m_VAO = TE::Core::CreateVertexArray();

			TE::Core::BufferLayout bufferLayout
			{
				{"aPos", TE::Core::BUFFER_COMPO_XYZ, TE::Core::BUFFER_STRIDE_F3, false}
			};

			m_VBO->SetLayout(bufferLayout);
			m_VAO->EmplaceVtxBuffer(m_VBO);
			m_VAO->EmplaceIdxBuffer(m_IBO);

		}
		catch( TE::Core::Exception& e )
		{
			e.What();
		}
	}

	Application::~Application()
	{
		TE::Core::Core::DestroyWindow(m_window);
		TE::Core::Core::Quit();
	}

	void Application::Run() const
	{
		while( m_window->IsActive() )
		{
			m_window->PollEvents();

			TE::Core::Renderer::Clear();
			TE::Core::Renderer::ClearColor({ 0.243f, 0.243f, 0.243f, 1.0f });


			m_Shader->Bind();
			m_VAO->Bind();

			TE::Core::Renderer::Draw(6);

			m_VAO->Unbind();
			m_Shader->Unbind();
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
		if( !m_window->Properties().WindowState != TE::Core::WINDOW_MINIMIZED )
			TE::Core::Renderer::SetViewport(NULL, NULL, e.Width(), e.Height());

		return false;
	}
}