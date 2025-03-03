#include "core_pch.hpp"

namespace TE::Core
{
	void Camera2D::SetAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
		RefreshProjectionMatrix();
	}

	void Camera2D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RefreshProjectionMatrix();
	}

	void Camera2D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RefreshProjectionMatrix();
	}

	void Camera2D::SetProjection(float left, float right, float bottom, float top)
	{
		RefreshProjectionMatrix(left, right, bottom, top);
	}

	void Camera2D::OnUpdate(DeltaTime deltaTime)
	{
		if( InputHandler::GetKeyState(KEY_W) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position.y += m_TranslationSpeed * deltaTime;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_S) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position.y -= m_TranslationSpeed * deltaTime;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_A) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position.x -= m_TranslationSpeed * deltaTime;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_D) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position.x += m_TranslationSpeed * deltaTime;
			RefreshProjectionMatrix();
		}

		if( m_IsRotationEnabled )
		{
			if( InputHandler::GetKeyState(KEY_Q) & ( KEY_PRESSED | KEY_REPEAT ) )
			{
				m_Rotation += m_RotationSpeed * deltaTime;
				RefreshProjectionMatrix();
			}

			if( InputHandler::GetKeyState(KEY_E) & ( KEY_PRESSED | KEY_REPEAT ) )
			{
				m_Rotation -= m_RotationSpeed * deltaTime;
				RefreshProjectionMatrix();
			}
		}

		m_TranslationSpeed = m_ZoomLevel;
	}

	void Camera2D::OnEvents(WindowHandle handle, Events& e)
	{
		EventsHandler handler(handle, e);
		handler.Dispatch<WindowHandle, EventMouseWheelScroll>(EVENT_CALLBACK(OnMouseWheelScrollEvent));
		handler.Dispatch<WindowHandle, EventWindowResize>(EVENT_CALLBACK(OnWindowResizeEvent));
	}

	bool Camera2D::OnMouseWheelScrollEvent(WindowHandle handle, EventMouseWheelScroll& e)
	{
		m_ZoomLevel -= e.OffsetY();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_CameraBounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		RefreshProjectionMatrix(m_CameraBounds.Left, m_CameraBounds.Right, m_CameraBounds.Bottom, m_CameraBounds.Top);
		return false;
	}

	bool Camera2D::OnWindowResizeEvent(WindowHandle handle, EventWindowResize& e)
	{
		m_AspectRatio = (float) e.Width() / (float) e.Height();
		m_CameraBounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		RefreshProjectionMatrix(m_CameraBounds.Left, m_CameraBounds.Right, m_CameraBounds.Bottom, m_CameraBounds.Top);

		return false;
	}

	void Camera2D::RefreshProjectionMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });
		glm::mat4 view = inverse(transform);

		float left		= -m_AspectRatio * m_ZoomLevel;
		float right		=  m_AspectRatio * m_ZoomLevel;
		float top		=  m_ZoomLevel;
		float bottom	= -m_ZoomLevel;

		m_Projection	= glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_MVP			= view * m_Projection;
	}

	void Camera2D::RefreshProjectionMatrix(float left, float right, float bottom, float top)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });
		glm::mat4 view = inverse(transform);

		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_MVP = view * m_Projection;
	}
}