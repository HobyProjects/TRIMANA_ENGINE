#include "core_pch.hpp"

namespace TE::Core
{
	Camera2D::Camera2D(float aspectRatio, float size, float nearClip, float farClip)
	{
		m_AspectRatio			= aspectRatio;
		m_OrthographicSize		= size;
		m_OrthographicNear		= nearClip;
		m_OrthographicFar		= farClip;
		RefreshWVP();
	}

	void Camera2D::SetAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
		RefreshWVP();
	}

	void Camera2D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RefreshWVP();
	}

	void Camera2D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RefreshWVP();
	}

	void Camera2D::SetSize(float size)
	{
		m_OrthographicSize = size;
		RefreshWVP();
	}

	void Camera2D::SetNearClip(float nearClip)
	{
		m_OrthographicNear = nearClip;
		RefreshWVP();
	}

	void Camera2D::SetFarClip(float farClip)
	{
		m_OrthographicFar = farClip;
		RefreshWVP();
	}

	void Camera2D::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize	= size;
		m_OrthographicNear	= nearClip;
		m_OrthographicFar	= farClip;
		RefreshWVP();
	}

	void Camera2D::RefreshWVP()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });
		m_View = inverse(transform);

		float left		= -m_OrthographicSize * m_AspectRatio * 0.5f;
		float right		=  m_OrthographicSize * m_AspectRatio * 0.5f;
		float top		=  m_OrthographicSize * 0.5f;
		float bottom	= -m_OrthographicSize * 0.5f;

		m_Projection	= glm::ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);
		m_MVP			= m_View * m_Projection;
	}
}