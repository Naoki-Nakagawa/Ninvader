#ifndef _GdkDx9_Screen_h_
#define _GdkDx9_Screen_h_

#include <string>
#include "Int2.h"
#include "Property.h"

namespace gdk
{
	namespace dx9
	{
		class Screen
		{
		private:

			static HWND handle;

			static std::string name;

			static Int2 size;

			Screen();

			~Screen();

			static LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

			static Int2 AdjustSize(const Int2& size);

		public:

			Screen(const Screen&) = delete;

			Screen& operator = (const Screen&) = delete;

			static void Create();

			static bool Message();

			static HWND Handle();

			static std::string Name();

			static void Name(const std::string& value);

			static Int2 Size();

			static void Size(const Int2& value);

		};
	}
}

#endif	// _GdkDx9_Screen_h_
