#ifndef _GdkDx9_Render_h_
#define _GdkDx9_Render_h_

#include <d3d9.h>

namespace gdk
{
	namespace dx9
	{
		class Render
		{
		private:

			static IDirect3DDevice9* device;

			Render();

			~Render();

		public:

			Render(const Render&) = delete;

			Render& operator = (const Render&) = delete;

			static void Create();

			static void Clear(const int& color);

			static void Present();

			static IDirect3DDevice9* Device();

		};
	}
}

#endif	// _GdkDx9_Render_h_
