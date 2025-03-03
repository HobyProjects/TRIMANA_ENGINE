#pragma once 

#include "base_window.hpp"
#include "delta_time.hpp"
#include "events.hpp"
#include "window_events.hpp"
#include "mouse_events.hpp"
#include "camera.hpp"

namespace TE::Core
{
	class Camera2D
	{
		public:
			Camera2D() = default;
			Camera2D(float aspectRatio, bool enableRotation) : m_AspectRatio(aspectRatio), m_IsRotationEnabled(enableRotation) {}
			~Camera2D() = default;

			glm::mat4 GetProjection() const { return m_Projection; }
			glm::mat4 GetView() const { return m_View; }
			glm::mat4 GetViewProjectionMatrix() const { return m_MVP; }
			glm::vec3 GetPosition() const { return m_Position; }
			float GetRotation() const { return m_Rotation; }
			float GetAspectRatio() const { return m_AspectRatio; }

			void SetAspectRatio(float ratio);
			void SetRotation(float rotation);
			void SetPosition(const glm::vec3& position);
			void SetProjection(float left, float right, float bottom, float top);


			void OnUpdate(DeltaTime deltaTime);
			void OnEvents(WindowHandle handle, Events& e);

		private:
			bool OnMouseWheelScrollEvent(WindowHandle handle, EventMouseWheelScroll& e);
			bool OnWindowResizeEvent(WindowHandle handle, EventWindowResize& e);

		private:
			void RefreshProjectionMatrix();
			void RefreshProjectionMatrix(float left, float right, float bottom, float top);

		private:
			float m_AspectRatio{ 1.0f };
			float m_Rotation{ 0.0f };

			float m_TranslationSpeed{ 1.0f };
			float m_RotationSpeed{ 10.0f };
			float m_ZoomLevel{ 1.0f };

			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_MVP{ 1.0f };
			glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };

			CameraBounds m_CameraBounds;
			bool m_IsRotationEnabled{ false };
	};
}