#include "app_pch.hpp"

namespace TE::App
{
	static std::weak_ptr<TE::Core::IWindow> s_Window;

	SandBoxLayer::SandBoxLayer(const std::shared_ptr<TE::Core::IWindow>& window): ApplicationLayers("SandboxLayer")
	{
		s_Window = window;
		if( !s_Window.expired() )
		{
			auto windowShrPtr = s_Window.lock();
			m_CameraController = std::make_shared<PrimaryCameraController>(windowShrPtr, TE::Core::CAMERA_TYPE::CAMERA_2D, false);
			return;
		}

		TE_ASSERT(false, "Expired window");
	}

	void SandBoxLayer::OnAttach()
	{
		m_Texture = TE::Core::CreateTexture2D("res/textures/sasuke.jpg");
	}

	void SandBoxLayer::OnDetach()
	{
	}

	void SandBoxLayer::OnUpdate(TE::Core::DeltaTime dt)
	{
		m_CameraController->OnUpdate(dt);

		TE::Core::BatchRenderer2D::Begin(m_CameraController->Main2DCamera);
		TE::Core::BatchRenderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
		TE::Core::BatchRenderer2D::End();
	}

	void SandBoxLayer::OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& event)
	{
		m_CameraController->OnEvents(handle, event);
	}

	void SandBoxLayer::OnImGuiRenders()
	{
	}
}