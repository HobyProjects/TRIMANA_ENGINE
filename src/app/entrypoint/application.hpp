#pragma once

#include "core.hpp"
#include "application_layer.hpp"
#include "application_layers_stack.hpp"

#include "sandbox.hpp"

namespace TE::App
{
	class Application
	{
		public:
			Application();
			~Application();

			void Run();
			void OnEvent(TE::Core::WindowHandle handle, TE::Core::Events& e);
			void PushLayer(const std::shared_ptr<ApplicationLayers>& applicationLayer);
			void PushOverlay(const std::shared_ptr<ApplicationLayers>& applicationLayer);

			static Application* GetApplicationInstance();
			static TE::Core::Native GetNativeWindow();

		private:
			bool OnWindowClose(TE::Core::WindowHandle handle, TE::Core::EventWindowClose& e);
			bool OnWindowResize(TE::Core::WindowHandle handle, TE::Core::EventWindowResize& e);

		private:
			std::shared_ptr<TE::Core::IWindow> m_Window{ nullptr };
			std::shared_ptr<ApplicationLayerStack> m_LayerStack{ nullptr };
			std::shared_ptr<PrimaryCameraController> m_Camera{ nullptr };

			//Application Layers
			std::shared_ptr<SandBoxLayer> m_SandboxLayer{ nullptr };
			float m_LastFrameTime{ 0.0f };
	};
}