
#include "Component.h"
#include <iostream>
using namespace std;

int Component::ID = 1;

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
	m_Label = "No Label";
}

void Component::set_label(string x)
{
	m_Label = x;
}

string Component::get_label()
{
	return m_Label;
}

OutputPin * Component::getSourcePin()
{
	return NULL;
}

InputPin * Component::getDestPin()
{
	return NULL;
}

void Component::setID(int id)
{
	ID = id;
}


GraphicsInfo & Component::get_GraphicInfo()
{
	return m_GfxInfo;
}

void Component::set_GraphicInfo(GraphicsInfo GFX)
{
	m_GfxInfo = GFX;
}

void Component::AddComponent( ApplicationManager * pApp )
{
	Component *** Arr = pApp->GetArr( );
	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = this;
}

void Component::DeleteComponent( ApplicationManager * pApp )
{
	EraseComponent( pApp );
	pApp->DeleteComponent( this );
}

void Component::EraseComponent(ApplicationManager * pApp) 
{
	Component *** Arr = pApp->GetArr();
	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2 ; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = NULL;
	pApp->GetOutput()->DeleteGate(m_GfxInfo);
}

void Component::Highlight()
{
	highlighted = true;
}

void Component::Unhighlight()
{
	highlighted = false;
}

void Component::Forbid( )
{
	forbidden = true;
}

void Component::Allow( )
{
	forbidden = false;
}

void Component::ChangeState()
{
	highlighted = !highlighted;
}

int Component::GetInputPinIndex(pair<int, int> &coordinates)
{
	return -1;
}

bool Component::isSelected( )
{
	return highlighted;
}

bool Component::ChangePath(ApplicationManager*)
{
	return false;
}



ComponentType Component::getType()
{
	return Type;
}

Component::Component()
{
	m_Label = "NO-Label";
}

void Component::setCompIndex(int index)
{
	compIndex = index;
}

int Component::getCompIndex()
{
	return compIndex;
}


Component::~Component()
{}

void Component::AddConnection(BFSOut& xx, ApplicationManager * pApp) {
	Component *** Arr = pApp->GetArr();
	int a = m_GfxInfo.x2, b = m_GfxInfo.y2;
	while (true)
	{
		if (a == m_GfxInfo.x1 &&b == m_GfxInfo.y1)break;
		int c = a;int d = b;
		int x = a;
		a = xx.arr[a][b].first, b = xx.arr[x][b].second;
		if (a == c) {
			if (d > b) {
				for (int i = b - 5;i <= d - 5;i++)
					if (Arr[i][a] == NULL) {
						for (int j = a;j < a + 5;j++)Arr[i][j] = this;
					}
			}
			else
				for (int i = d - 5;i <= b - 5;i++)
					if (Arr[i][a] == NULL) {

						for (int j = a;j < a + 5;j++)Arr[i][j] = this;
					}
		}
		if (b == d) {
			if (a> c)
				for (int i = c;i <= a;i++) {
					if (Arr[b][i] == NULL) {
						for (int j = b - 7;j < b + 1;j++)Arr[j][i] = this;
					}
				}
			else
				for (int i = a;i <= c;i++)
					if (Arr[b][i] == NULL) {
						for (int j = b - 7;j < b + 1;j++)Arr[j][i] = this;
					}

		}
	}
}


