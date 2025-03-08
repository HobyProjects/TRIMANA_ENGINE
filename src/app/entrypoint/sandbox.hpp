#pragma once

#include "core.hpp"
#include "application_layer.hpp"
#include "primary_camera.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace TE::App
{
	class SandBoxLayer : public ApplicationLayers
	{
		public:
			SandBoxLayer(const std::shared_ptr<TE::Core::IWindow>& window);
			virtual ~SandBoxLayer() = default;

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnUpdate(TE::Core::DeltaTime dt) override;
			virtual void OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& event) override;
			virtual void OnImGuiRenders() override;

		private:
			std::shared_ptr<PrimaryCameraController> m_CameraController{ nullptr };
			std::shared_ptr<TE::Core::IShader> m_ShaderProgram{ nullptr };
			std::shared_ptr<TE::Core::Model> m_Model{ nullptr };
	};
}