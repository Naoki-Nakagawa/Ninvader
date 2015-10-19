#ifndef _GdkDx9_Font_h_
#define _GdkDx9_Font_h_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace gdk
{
	namespace dx9
	{
		class Font
		{
		private:

			ID3DXFont* font;

		public:

			D3DXVECTOR3 position;

			Font();

			Font(int size, std::string name);

			~Font();

			void Print(std::string str);

		};
	}
}

#endif	// _GdkDx9_Font_h_
