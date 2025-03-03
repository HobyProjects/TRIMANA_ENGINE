#include "app_pch.hpp"

namespace TE::App
{
	static std::weak_ptr<TE::Core::IWindow> s_TargetWindow;

	PrimaryCameraController::PrimaryCameraController(const std::shared_ptr<TE::Core::IWindow> targetWindow, TE::Core::CAMERA_TYPE cameraType, bool rotationEnabled)
		:AspectRatio(targetWindow->Properties().Width/targetWindow->Properties().Height), CurrentCameraType(cameraType), IsRotationEnabled(rotationEnabled),
		CameraBounds(-AspectRatio * ZoomLevel, AspectRatio* ZoomLevel, -ZoomLevel, ZoomLevel), 
		Main2DCamera(AspectRatio, false),Main3DCamera(AspectRatio)
	{
		TE::Core::InputHandler::SetTargetWindow(targetWindow);
		s_TargetWindow = targetWindow;
	}

	void PrimaryCameraController::OnUpdate(TE::Core::DeltaTime deltaTime)
	{
		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_2D )
		{
			Main2DCamera.OnUpdate(deltaTime);
		}

		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_3D )
		{
			if( TE::Core::InputHandler::GetMouseState(TE::Core::MOUSE_BUTTON_RIGHT) & TE::Core::MOUSE_BUTTON_PRESSED )
			{
				if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_W) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
				{
					glm::vec3 position = Main3DCamera.GetPosition();
					position += Camera3DTranslationSpeed * Main3DCamera.GetOriantaion();
					Main3DCamera.SetPosition(position);
				}

				if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_S) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
				{
					glm::vec3 position = Main3DCamera.GetPosition();
					position += Camera3DTranslationSpeed * -( Main3DCamera.GetOriantaion() );
					Main3DCamera.SetPosition(position);
				}

				if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_A) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
				{
					glm::vec3 position = Main3DCamera.GetPosition();
					position += Camera3DTranslationSpeed * -( glm::normalize(glm::cross(Main3DCamera.GetOriantaion(), Main3DCamera.GetOriantaionUp())) );
					Main3DCamera.SetPosition(position);
				}

				if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_D) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
				{
					glm::vec3 position = Main3DCamera.GetPosition();
					position += Camera3DTranslationSpeed * glm::normalize(glm::cross(Main3DCamera.GetOriantaion(), Main3DCamera.GetOriantaionUp()));
					Main3DCamera.SetPosition(position);
				}
			}
			

			if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_LEFT_CONTROL) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
			{
				glm::vec3 position = Main3DCamera.GetPosition();
				position += Camera3DTranslationSpeed * -Main3DCamera.GetOriantaionUp();
				Main3DCamera.SetPosition(position);
			}

			if( TE::Core::InputHandler::GetKeyState(TE::Core::KEY_SPACE) & ( TE::Core::KEY_PRESSED | TE::Core::KEY_REPEAT ) )
			{
				glm::vec3 position = Main3DCamera.GetPosition();
				position += Camera3DTranslationSpeed * Main3DCamera.GetOriantaionUp();
				Main3DCamera.SetPosition(position);
			}
		}
	}

	void PrimaryCameraController::OnEvents(TE::Core::WindowHandle handle, TE::Core::Events& e)
	{
		TE::Core::EventsHandler handler(handle, e);
		Main2DCamera.OnEvents(handle, e);

		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventMouseWheelScroll>(EVENT_CALLBACK(OnMouseWheelScrollEvent));
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventWindowResize>(EVENT_CALLBACK(OnWindowResizeEvent));
		handler.Dispatch<TE::Core::WindowHandle, TE::Core::EventMouseCursorMove>(EVENT_CALLBACK(OnMouseCursorPosChange));
	}

	void PrimaryCameraController::ChangeCamera(TE::Core::CAMERA_TYPE type)
	{
		CurrentCameraType = type;
	}

	bool PrimaryCameraController::OnMouseWheelScrollEvent(TE::Core::WindowHandle handle, TE::Core::EventMouseWheelScroll& e)
	{
		return false;
	}

	bool PrimaryCameraController::OnWindowResizeEvent(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e)
	{
		AspectRatio = (float) e.Width() / (float) e.Height();
		Main3DCamera.SetAspectRatio(AspectRatio);
		return false;
	}

	bool PrimaryCameraController::OnMouseCursorPosChange(TE::Core::WindowHandle handle, TE::Core::EventMouseCursorMove& e)
	{
		if( CurrentCameraType == TE::Core::CAMERA_TYPE::CAMERA_3D )
		{
			MousePosX = e.GetX();
			MousePosY = e.GetY();

			float width{ 0.0f }, height{ 0.0f };
			auto windowPtr = s_TargetWindow.lock();

			width = static_cast<float>(windowPtr->Properties().Width);
			height = static_cast<float>(windowPtr->Properties().Height);

			float rotX = Camera3DSensitivity * ( MousePosY - ( height / 2.0f ) ) / height;
			float rotY = Camera3DSensitivity * ( MousePosX - ( width / 2.0f ) ) / width;

			glm::vec3 newOrientation = glm::rotate(Main3DCamera.GetOriantaion(), glm::radians(-rotX), glm::normalize(glm::cross(Main3DCamera.GetOriantaion(), Main3DCamera.GetOriantaionUp())));
			if( abs(glm::angle(newOrientation, Main3DCamera.GetOriantaionUp()) - glm::radians(90.0f)) <= glm::radians(85.0f) )
				Main3DCamera.SetOriantaion(newOrientation);

			Main3DCamera.SetOriantaion(glm::rotate(Main3DCamera.GetOriantaion(), glm::radians(-rotY), Main3DCamera.GetOriantaionUp()));
		}
	
		return false;
	}
}