#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}

void Component::set_label(string x)
{m_Label = x;}

string Component::get_label()
{return m_Label;}

GraphicsInfo Component::get_GraphicInfo()
{return m_GfxInfo;}

void Component::AddComponent(Component ** Arr[780])
{
	for (int i = m_GfxInfo.x1; i < m_GfxInfo.x2; i++)
		for (int j = m_GfxInfo.y1; j < m_GfxInfo.y2; j++)
			Arr[i][j] = this;	 
}

Component::Component()
{}

Component::~Component()
{}

