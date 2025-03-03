#pragma once

#include "core.hpp"
#include "camera2d.hpp"
#include "camera3d.hpp"
#include "delta_time.hpp"
#include "events.hpp"

namespace TE::App
{
	class PrimaryCameraController
	{
		public:
			PrimaryCameraController(const std::shared_ptr<TE::Core::IWindow> targetWindow, TE::Core::CAMERA_TYPE cameraType, bool rotationEnabled = false);
			~PrimaryCameraController() = default;

			void OnUpdate(TE::Core::DeltaTime deltaTime);
			void OnEvents(TE::Core::WindowHandle handle, TE::Core::Events& e);
			void ChangeCamera(TE::Core::CAMERA_TYPE type);

		public:
			TE::Core::Camera2D Orthographic_Camera;
			TE::Core::Camera3D Perspective_Camera;
			TE::Core::CAMERA_TYPE CurrentCameraType{ TE::Core::CAMERA_TYPE::CAMERA_2D };
	};
}