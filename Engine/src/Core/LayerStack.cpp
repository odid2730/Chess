#include "pch.h"
#include "LayerStack.h"

void LayerStack::PushLayer(Layer* layer)
{
	m_Layers.push_back(layer);
}
