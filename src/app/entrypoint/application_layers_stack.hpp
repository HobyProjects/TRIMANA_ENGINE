#pragma once

#include <memory>
#include <vector>

#include "application_layer.hpp"

namespace TE::App
{
    class ApplicationLayerStack
    {
    public:
        ApplicationLayerStack() = default;
        ~ApplicationLayerStack();

        void PushLayer(std::shared_ptr<ApplicationLayers> layer);
        void PopLayer(std::shared_ptr<ApplicationLayers> layer);
        void PushOverlay(std::shared_ptr<ApplicationLayers> overlay);
        void PopOverlay(std::shared_ptr<ApplicationLayers> overlay);

        std::vector<std::shared_ptr<ApplicationLayers>>::iterator begin() { return m_Layers.begin(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::iterator end() { return m_Layers.end(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::const_iterator end() const { return m_Layers.end(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::reverse_iterator rend() { return m_Layers.rend(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<std::shared_ptr<ApplicationLayers>>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<std::shared_ptr<ApplicationLayers>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}