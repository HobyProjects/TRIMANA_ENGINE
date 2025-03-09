#include "app_pch.hpp"

namespace TE::App
{
	static std::weak_ptr<TE::Core::IWindow> s_Window;

	// Vertices coordinates
	float vertices[] =
	{ //     COORDINATES     /        COLORS                /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 1.0f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f, 1.0f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f, 1.0f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 1.0f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f, 1.0f,	2.5f, 5.0f
	};

	// Indices for vertices order
	uint32_t indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	struct MeshStruct
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};

	SandBoxLayer::SandBoxLayer(const std::shared_ptr<TE::Core::IWindow>& window): ApplicationLayers("SandboxLayer")
	{
		s_Window = window;
		if( !s_Window.expired() )
		{
			auto windowShrPtr = s_Window.lock();
			m_CameraController = std::make_shared<PrimaryCameraController>(windowShrPtr, TE::Core::CAMERA_TYPE::CAMERA_3D, false);
			return;
		}

		TE_ASSERT(false, "Expired window");
	}

	void SandBoxLayer::OnAttach()
	{
		m_ShaderProgram = TE::Core::CreateShaderProgram("3DModelShader", "res/shaders/Vertex3D.glsl", "res/shaders/Fragment3D.glsl");
		m_Model = std::make_shared<TE::Core::Model>();
		if(m_Model->Load("res/models/78176/78176.obj"))
			TE_INFO("Model loaded successfully");
		else
			TE_ERROR("Model loading failed");
	}

	void SandBoxLayer::OnDetach()
	{
	}

	void SandBoxLayer::OnUpdate(TE::Core::DeltaTime dt)
	{
		m_CameraController->OnUpdate(dt);


		m_ShaderProgram->Bind();
		m_ShaderProgram->SetUniform("u_CameraMatrix", m_CameraController->Perspective_Camera.GetCameraMatrix());
		m_ShaderProgram->SetUniform("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		m_Model->Render();
		m_ShaderProgram->Unbind();

	}

	void SandBoxLayer::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& event)
	{
		m_CameraController->OnEvents(handle, event);
	}

	void SandBoxLayer::OnImGuiRenders()
	{
		ImGui::ShowDemoWindow();
	}
}