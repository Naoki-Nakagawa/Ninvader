#ifndef _GdkDx9_Camera_h_
#define _GdkDx9_Camera_h_

#include <d3dx9.h>

namespace gdk
{
	namespace dx9
	{
		class Camera
		{
		private:

			void Create();

		public:

			D3DXVECTOR3 position;
			D3DXVECTOR3 rotation;

			Camera();

			Camera(const D3DXVECTOR3& position, const D3DXVECTOR3& rotation);

			~Camera();

			void View();
		};
	}
}

#endif	// _GdkDx9_Camera_h_
