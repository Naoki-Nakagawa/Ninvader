#include <Windows.h>
#include "GdkDx9.h"

namespace gdk
{
	namespace dx9
	{
		GdkDx9::GdkDx9()
		{
			Screen::Create();
			Render::Create();
			Input::Create();
		}

		GdkDx9::~GdkDx9()
		{

		}
	}
}
