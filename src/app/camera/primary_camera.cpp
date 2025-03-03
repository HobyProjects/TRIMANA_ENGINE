#include "app_pch.hpp"

namespace TE::App
{
	static std::weak_ptr<TE::Core::IWindow> s_TargetWindow;

	PrimaryCameraController::PrimaryCameraController(const std::shared_ptr<TE::Core::IWindow> targetWindow, TE::Core::CAMERA_TYPE cameraType, bool rotationEnabled)
	{
		TE::Core::InputHandler::SetTargetWindow(targetWindow);
		s_TargetWindow = targetWindow;

		auto window = s_TargetWindow.lock();

		float width = window->Properties().Width;
		float height = window->Properties().Height;

		Orthographic_Camera.SetAspectRatio(width/height);
		Perspective_Camera.SetAspectRatio(width, height);
		CurrentCameraType = cameraType;
	}

	void PrimaryCameraController::OnUpdate(TE::Core::DeltaTime deltaTime)
	{
		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_2D )
		{
			Orthographic_Camera.OnUpdate(deltaTime);
		}

		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_3D )
		{
			Perspective_Camera.OnUpdate(deltaTime);
		}
	}

	void PrimaryCameraController::OnEvents(TE::Core::WindowHandle handle, TE::Core::Events& e)
	{
		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_2D )
			Orthographic_Camera.OnEvents(handle, e);
		

		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_3D )
			Perspective_Camera.OnEvents(handle, e);
	}

	void PrimaryCameraController::ChangeCamera(TE::Core::CAMERA_TYPE type)
	{
		CurrentCameraType = type;
	}
}