#ifndef _GdkDx9_Input_h_
#define _GdkDx9_Input_h_

#include <dinput.h>
#include "History.h"
#include "Int2.h"

namespace gdk
{
	namespace dx9
	{
		class Input
		{
		private:

			static IDirectInput8* input;
			static IDirectInputDevice8* keyDevice;
			static IDirectInputDevice8* mouseDevice;
			static BYTE keyState[];
			static DIMOUSESTATE2 mouseState;
			static History<Int2, 2> mousePosition;

			Input();

			~Input();

		public:

			Input(const Input&) = delete;

			Input& operator = (const Input&) = delete;

			static void Create();

			static void Check();

			static bool GetKey(int keyCode);

			static Int2 GetMousePosition();

			static Int2 GetMouseDeltaPosition();

		};
	}
}

#endif	// _GdkDx9_Input_h_
