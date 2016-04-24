#include "Component.h"
#include <iostream>
using namespace std;
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

void Component::AddComponent( Component ** Arr[780])
{

	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2-1; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = this;
	for ( int i = 0; i < UI.height; i += 30 )
	{
		for ( int j = 0; j < UI.width; j += 30 )
		{
			if ( Arr[i][j] != NULL )
				cout << " T ";
			else
				cout << " 0 ";
		}
		cout << endl;
	}

}

Component::Component()
{}

Component::~Component()
{}

