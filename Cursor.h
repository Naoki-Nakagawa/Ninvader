#ifndef _GdkDx9_Cursor_h_
#define _GdkDx9_Cursor_h_

#include "Int2.h"
namespace gdk
{
	namespace dx9
	{
		class Cursor
		{
		public:

			static bool Lock;

			Cursor();

			~Cursor();

			static Int2 ConvertMousePositionGlobalToLocal(POINT mousePosition);

			static POINT ConvertMousePositionLocalToGlobal(Int2 mousePosition);

		};
	}
}

#endif	// _GdkDx9_Cursor_h_
