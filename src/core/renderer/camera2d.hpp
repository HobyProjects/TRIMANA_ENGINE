#pragma once 

#include "camera.hpp"

namespace TE::Core
{
	class Camera2D : public ICamera
	{
		public:
			Camera2D() = default;
			Camera2D(float left, float right, float top, float bottom);
			Camera2D(float size = 10.0f, float nearClip = -1.0f, float farClip = 1.0f);
			virtual ~Camera2D() = default;

			virtual glm::mat4 GetProjection() const override { return m_Projection; }
			virtual glm::mat4 GetView() const override { return m_View; }
			virtual glm::mat4 GetViewProjectionMatrix() const override { return m_MVP; }
			virtual glm::vec3 GetPosition() const override { return m_Position; }
			virtual float GetRotation() const override { return m_Rotation; }
			virtual CAMERA_TYPE GetType() const override { return CAMERA_TYPE::CAMERA_2D; }

			void SetAspectRatio(float ratio);
			void SetRotation(float rotation);
			void SetPosition(const glm::vec3& position);
			void SetProjection(float size, float nearClip, float farClip);
			void SetProjection(float left, float right, float top, float bottom);

			float GetSize() const { return m_OrthographicSize; }
			float GetNearClip() const { return m_OrthographicNear; }
			float GetFarClip() const { return m_OrthographicFar; }

		private:
			void RefreshMVP();

		private:
			float m_AspectRatio{ 1.0f };
			float m_OrthographicSize{ 10.0f };
			float m_OrthographicNear{ -1000.0f };
			float m_OrthographicFar{ 1000.0f };
			glm::mat4 m_View{ 1.0f };
			glm::mat4 m_Projection{ 1.0f };
			glm::mat4 m_MVP{ 1.0f };
			glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
			float m_Rotation{ 0.0f };
	};
}