#include "Font.h"
#include "Render.h"
#include "Screen.h"

using namespace std;

namespace gdk
{
	namespace dx9
	{
		Font::Font()
		{

		}

		Font::Font(int size, string name)
		{
			if (FAILED(D3DXCreateFont(Render::Device(), size, size / 2, FW_NORMAL, 0, false, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, name.c_str(), &font)))
			{
				font->Release();
				font = nullptr;
				return;
			}
		}


		Font::~Font()
		{

		}

		void Font::Print(string str)
		{
			D3DXVECTOR3 location;
			D3DXMATRIX m_world, m_view, m_projection;
			D3DVIEWPORT9 viewPort;
			RECT rect;

			D3DXMatrixIdentity(&m_world);
			D3DXMatrixIdentity(&m_view);
			D3DXMatrixIdentity(&m_projection);

			Render::Device()->GetTransform(D3DTS_VIEW, &m_view);
			Render::Device()->GetTransform(D3DTS_PROJECTION, &m_projection);
			Render::Device()->GetViewport(&viewPort);

			D3DXVec3Project(&location, &position, &viewPort, &m_projection, &m_view, &m_world);

			SetRect(&rect, int(location.x), int(location.y), 0, 0);

			font->DrawText(nullptr, str.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}
