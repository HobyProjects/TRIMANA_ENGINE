#include "app_pch.hpp"

namespace TE::App
{
	ApplicationLayerStack::~ApplicationLayerStack()
	{
		for( auto& layer : m_Layers )
		{
			layer->OnDetach();
		}
	}

	void ApplicationLayerStack::PushLayer(std::shared_ptr<ApplicationLayers> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	}

	void ApplicationLayerStack::PopLayer(std::shared_ptr<ApplicationLayers> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if( it != m_Layers.end() )
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void ApplicationLayerStack::PushOverlay(std::shared_ptr<ApplicationLayers> overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void ApplicationLayerStack::PopOverlay(std::shared_ptr<ApplicationLayers> overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if( it != m_Layers.end() )
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}