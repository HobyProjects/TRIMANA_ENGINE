#include "core_pch.hpp"
#include "camera3d.hpp"

namespace TE::Core
{
	Camera3D::Camera3D(float width, float height)
	{
		m_AspectRatio = width / height;
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetAspectRatio(float width, float height)
	{
		m_AspectRatio = width / height;
		m_ViewportWidth = (uint32_t)width;
		m_ViewportHeight = (uint32_t)height;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetFOV(float fov)
	{
		m_PerspectiveFov = fov;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetNearClip(float nearClip)
	{
		m_PerspectiveNear = nearClip;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetFarClip(float farClip)
	{
		m_PerspectiveFar = farClip;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetOriantaion(const glm::vec3& oriantaion)
	{
		m_Oriantaion = oriantaion;
		RefreshProjectionMatrix();
	}

	void Camera3D::SetPerspective(float fov, float nearClip, float farClip)
	{
		m_PerspectiveFov	= fov;
		m_PerspectiveNear	= nearClip;
		m_PerspectiveFar	= farClip;
		RefreshProjectionMatrix();
	}

	void Camera3D::OnUpdate(DeltaTime deltaTime)
	{
		//m_TranslationSpeed = m_TranslationSpeed * deltaTime;

		if( InputHandler::GetKeyState(KEY_W) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * m_Oriantaion;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_S) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * -m_Oriantaion;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_A) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * -( glm::normalize(glm::cross(m_Oriantaion, m_Up)) );
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_D) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * glm::normalize(glm::cross(m_Oriantaion, m_Up));
			RefreshProjectionMatrix();
		}


		if( InputHandler::GetKeyState(KEY_LEFT_CONTROL) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * -m_Up;
			RefreshProjectionMatrix();
		}

		if( InputHandler::GetKeyState(KEY_SPACE) & ( KEY_PRESSED | KEY_REPEAT ) )
		{
			m_Position += m_TranslationSpeed * m_Up;
			RefreshProjectionMatrix();
		}
	}

	void Camera3D::OnEvents(WindowHandle handle, Events& e)
	{
		TE::Core::EventsHandler handler(handle, e);
		handler.Dispatch<WindowHandle, EventMouseWheelScroll>(EVENT_CALLBACK(OnMouseWheelScrollEvent));
		handler.Dispatch<WindowHandle, EventWindowResize>(EVENT_CALLBACK(OnWindowResizeEvent));
		handler.Dispatch<WindowHandle, EventMouseCursorMove>(EVENT_CALLBACK(OnMouseCursorPosChange));
	}

	bool Camera3D::OnMouseWheelScrollEvent(WindowHandle handle, EventMouseWheelScroll& e)
	{
		return false;
	}

	bool Camera3D::OnWindowResizeEvent(WindowHandle handle, EventWindowResize& e)
	{
		if( e.Width() > 0 && e.Height() > 0 )
		{
			m_ViewportWidth = e.Width();
			m_ViewportHeight = e.Height();
			m_AspectRatio = (float) ( m_ViewportWidth / m_ViewportHeight );
			RefreshProjectionMatrix();
		}

		return false;
	}

	bool Camera3D::OnMouseCursorPosChange(WindowHandle handle, EventMouseCursorMove& e)
	{
		float mouseX = e.GetX();
		float mouseY = e.GetY();

		float rotX = m_Sensitivity * (float)( mouseY - ( m_ViewportHeight / 2 ) ) / m_ViewportHeight;
		float rotY = m_Sensitivity * (float)( mouseX - ( m_ViewportWidth  / 2 ) ) / m_ViewportWidth;

		glm::vec3 newOrientation = glm::rotate(m_Oriantaion, glm::radians(-rotX), glm::normalize(glm::cross(m_Oriantaion, m_Up)));

		if( abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f) )
			m_Oriantaion = newOrientation;

		m_Oriantaion = glm::rotate(m_Oriantaion, glm::radians(-rotY), m_Up);
		RefreshProjectionMatrix();

		return false;
	}


	void Camera3D::RefreshProjectionMatrix()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_Oriantaion, m_Up);
		m_Projection = glm::perspective(glm::radians(m_PerspectiveFov), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		m_CameraMatrix = m_Projection * m_View;
	}
}