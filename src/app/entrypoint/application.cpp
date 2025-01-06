#include "application.hpp"

float vertices[] = {
	// positions          // colors           // texture coords
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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
		TE::Core::Core::Init();
		m_window = TE::Core::Core::CreateWindow("Trimana Engine");
		m_window->SetEventsCallbackFunc(EVENT_CALLBACK(OnEvent));

		std::filesystem::path vertexShaderPath = "res/shaders/DefaultVertex.glsl";
		std::filesystem::path fragmentShaderPath = "res/shaders/DefaultFrag.glsl";
		std::filesystem::path textureFilePath = "res/textures/sasuke.jpg";

		m_Shader = TE::Core::CreateShaderProgram("TestShaderProgram", vertexShaderPath, fragmentShaderPath);
		m_VBO = TE::Core::CreateVertexBuffer(vertices, sizeof(vertices));
		m_IBO = TE::Core::CreateIndexBuffer(indices, 6);
		m_VAO = TE::Core::CreateVertexArray();
		m_Texture = TE::Core::CreateTexture2D(textureFilePath);

		TE::Core::BufferLayout bufferLayout
		{
			{"aPos", TE::Core::BUFFER_COMPO_XYZ, TE::Core::BUFFER_STRIDE_F3, false},
			{"aColor", TE::Core::BUFFER_COMPO_RGB, TE::Core::BUFFER_STRIDE_F3, false},
			{"aTexCoords", TE::Core::BUFFER_COMPO_UV, TE::Core::BUFFER_STRIDE_F2, false}
		};

		m_VBO->SetLayout(bufferLayout);
		m_VAO->EmplaceVtxBuffer(m_VBO);
		m_VAO->EmplaceIdxBuffer(m_IBO);
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

			m_Texture->Bind();
			TE::Core::Renderer::Draw(6);
			m_Texture->Unbind();

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