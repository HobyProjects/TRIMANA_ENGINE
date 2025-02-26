#include "core_pch.hpp"
#include "camera3d.hpp"

namespace TE::Core
{
	Camera3D::Camera3D(float aspectRatio, float fov, float nearClip, float farClip)
	{
		m_AspectRatio		= aspectRatio;
		m_PerspectiveFov	= fov;
		m_PerspectiveNear	= nearClip;
		m_PerspectiveFar	= farClip;
		RefreshWVP();
	}

	void Camera3D::SetAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
		RefreshWVP();
	}

	void Camera3D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RefreshWVP();
	}

	void Camera3D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RefreshWVP();
	}

	void Camera3D::SetFOV(float fov)
	{
		m_PerspectiveFov = fov;
		RefreshWVP();
	}

	void Camera3D::SetNearClip(float nearClip)
	{
		m_PerspectiveNear = nearClip;
		RefreshWVP();
	}

	void Camera3D::SetFarClip(float farClip)
	{
		m_PerspectiveFar = farClip;
		RefreshWVP();
	}

	void Camera3D::SetOriantaion(const glm::vec3& oriantaion)
	{
		m_Oriantaion = oriantaion;
		RefreshWVP();
	}

	void Camera3D::SetPerspective(float fov, float nearClip, float farClip)
	{
		m_PerspectiveFov	= fov;
		m_PerspectiveNear	= nearClip;
		m_PerspectiveFar	= farClip;
		RefreshWVP();
	}

	void Camera3D::RefreshWVP()
	{
		m_View = glm::mat4(1.0f);
		m_Projection = glm::mat4(1.0f);

		m_View = glm::lookAt(m_Position, m_Position + m_Oriantaion, m_OriantaionUp);
		m_Projection = glm::perspective(glm::radians(m_PerspectiveFov), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
	}
}