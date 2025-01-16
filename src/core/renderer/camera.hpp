#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace TE::Core
{
	enum class CAMERA_TYPE
	{
		CAMERA_2D = 0,
		CAMERA_3D = 1
	};

	struct CameraBounds
	{
		float Left{ 0.0f }, Right{ 0.0f }, Top{ 0.0f }, Bottom{ 0.0f };

		CameraBounds() = default;
		CameraBounds(float left, float right, float top, float bottom)
			: Left(left), Right(right), Top(top), Bottom(bottom) {}
		~CameraBounds() = default;

		float Width() const { return Right - Left; }
		float Height() const { return Bottom - Left; }
	};

	class ICamera
	{
		public:
			ICamera() = default;
			virtual ~ICamera() = default;

			virtual glm::mat4 GetProjection() const = 0;
			virtual glm::mat4 GetView() const = 0;
			virtual glm::mat4 GetViewProjectionMatrix() const = 0;
			virtual glm::vec3 GetPosition() const = 0;
			virtual float GetRotation() const = 0;
			virtual CAMERA_TYPE GetType() const = 0;
	};
}