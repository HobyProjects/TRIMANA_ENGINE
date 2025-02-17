#pragma once

#include <string>

#include "events.hpp"
#include "delta_time.hpp"

namespace TE::App
{
	class ApplicationLayers
	{
        public:
            ApplicationLayers(const std::string& name) : m_Name(name) {}
            virtual ~ApplicationLayers() = default;

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(TE::Core::DeltaTime dt) {}
            virtual void OnEvent(TE::Core::Events& event) {}
            virtual void OnImGuiRenders() {}

        private:
            std::string m_Name{ std::string() };
	};
}