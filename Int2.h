#ifndef _GdkDx9_Int2_h_
#define _GdkDx9_Int2_h_

#include <Windows.h>

namespace gdk
{
	namespace dx9
	{
		struct Int2
		{
		public:

			int x, y;

			static Int2 zero;

			Int2();

			Int2(const int& x, const int& y);

			~Int2();

			Int2 operator - (Int2 value);

			operator POINT();

		};
	}
}

#endif	// _GdkDx9_Int2_h_
