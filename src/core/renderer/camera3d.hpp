#pragma once

#include "base_window.hpp"
#include "delta_time.hpp"
#include "events.hpp"
#include "window_events.hpp"
#include "mouse_events.hpp"
#include "camera.hpp"

namespace TE::Core
{
	class Camera3D
	{
		public:
			Camera3D() = default;
			Camera3D(float width, float height);
			~Camera3D() = default;

			glm::mat4 GetProjection() const { return m_Projection; }
			glm::mat4 GetView() const { return m_View; }
			glm::mat4 GetCameraMatrix() const { return m_CameraMatrix; }
			glm::vec3 GetPosition() const { return m_Position; }
			float GetRotation() const { return m_Rotation; }

			void SetAspectRatio(float width, float height);
			void SetRotation(float rotation);
			void SetPosition(const glm::vec3& position);

			void SetFOV(float fov);
			void SetNearClip(float nearClip);
			void SetFarClip(float farClip);
			void SetOriantaion(const glm::vec3& oriantaion);
			void SetPerspective(float fov = 45.0f, float nearClip = 0.01f, float farClip = 100.0f);

			float GetFOV() const { return m_PerspectiveFov; }
			float GetNearClip() const { return m_PerspectiveNear; }
			float GetFarClip() const { return m_PerspectiveFar; }
			glm::vec3 GetOriantaion() const { return m_Oriantaion; }
			glm::vec3 GetWorldUp() const { return m_Up; }

			void OnUpdate(DeltaTime deltaTime);
			void OnEvents(WindowHandle handle, Events& e);

		private:
			bool OnMouseWheelScrollEvent(WindowHandle handle, EventMouseWheelScroll& e);
			bool OnWindowResizeEvent(WindowHandle handle, EventWindowResize& e);
			bool OnMouseCursorPosChange(WindowHandle handle, EventMouseCursorMove& e);

		private:
			void RefreshProjectionMatrix();

		private:
			float m_AspectRatio{ 1.0f };
			float m_PerspectiveFov{ 45.0f };
			float m_PerspectiveNear{ 0.1f };
			float m_PerspectiveFar{ 1000.0f };
			float m_Rotation{ 0.0f };

			float m_TranslationSpeed{ 1.0f };
			float m_Sensitivity{ 1.5f };

			float m_MouseX{ 0.0f };
			float m_MouseY{ 0.0f };

			float m_Yaw{ -90.0f };
			float m_Pitch{ 0.0f };
			float m_Roll{ 0.0f };

			uint32_t m_ViewportWidth{ 0 };
			uint32_t m_ViewportHeight{ 0 };

			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_CameraMatrix{ 1.0f };
			glm::vec3 m_Position{ 0.0f, 0.0f, 10.0f };
			glm::vec3 m_Oriantaion{ 0.0f, 0.0f, -1.0f };
			glm::vec3 m_Up{ 0.0f, 1.0f, 0.0f };

			CameraBounds m_Bounds{};
	};
}