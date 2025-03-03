#pragma once

#include "camera.hpp"

namespace TE::Core
{
	class Camera3D
	{
		public:
			Camera3D() = default;
			Camera3D(float aspectRatio, float fov = 45.0f, float nearClip = 0.01f, float farClip = 1000.0f);
			~Camera3D() = default;

			glm::mat4 GetProjection() const { return m_Projection; }
			glm::mat4 GetView() const { return m_View; }
			glm::mat4 GetViewProjectionMatrix() const { return m_MVP; }
			glm::vec3 GetPosition() const { return m_Position; }
			float GetRotation() const { return m_Rotation; }

			void SetAspectRatio(float ratio);
			void SetRotation(float rotation);
			void SetPosition(const glm::vec3& position);

			void SetFOV(float fov);
			void SetNearClip(float nearClip);
			void SetFarClip(float farClip);
			void SetOriantaion(const glm::vec3& oriantaion);
			void SetPerspective(float fov = 45.0f, float nearClip = 0.01f, float farClip = 1000.0f);

			float GetFOV() const { return m_PerspectiveFov; }
			float GetNearClip() const { return m_PerspectiveNear; }
			float GetFarClip() const { return m_PerspectiveFar; }
			glm::vec3 GetOriantaion() const { return m_Oriantaion; }
			glm::vec3 GetOriantaionUp() const { return m_OriantaionUp; }

		private:
			void RefreshProjectionMatrix();

		private:
			float m_AspectRatio{ 1.0f };
			float m_PerspectiveFov{ 45.0f };
			float m_PerspectiveNear{ 0.01f };
			float m_PerspectiveFar{ 1000.0f };
			float m_Rotation{ 0.0f };

			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_MVP{ 1.0f };
			glm::vec3 m_Position{ 0.0f, 0.0f, 2.0f };
			glm::vec3 m_Oriantaion{ 0.0f, 0.0f, -1.0f };
			glm::vec3 m_OriantaionUp{ 0.0f, 1.0f, 0.0f };
	};
}