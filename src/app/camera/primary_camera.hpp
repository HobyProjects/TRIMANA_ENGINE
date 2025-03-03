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

		private:
			bool OnMouseWheelScrollEvent(TE::Core::WindowHandle handle, TE::Core::EventMouseWheelScroll& e);
			bool OnWindowResizeEvent(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e);
			bool OnMouseCursorPosChange(TE::Core::WindowHandle handle, TE::Core::EventMouseCursorMove& e);

		public:
			float AspectRatio{ 0.0f };
			float ZoomLevel{ 0.25f };
			glm::vec3 CameraPosition{ 0.0f, 0.0f, 0.0f };

			float Camera2DRotationAngle{ 0.0f };
			float Camera2DTranslationSpeed{ 50.0f };
			float Camera2DRotationSpeed{ 10.0f };

			float Camera3DTranslationSpeed{ 100.0f };
			float Camera3DSensitivity{ 1.0f };

			float MousePosX{ 0.0f };
			float MousePosY{ 0.0f };

			TE::Core::Camera2D Main2DCamera;
			TE::Core::Camera3D Main3DCamera;
			TE::Core::CameraBounds CameraBounds;

			TE::Core::CAMERA_TYPE CurrentCameraType;
			bool IsRotationEnabled{ false };
	};
}