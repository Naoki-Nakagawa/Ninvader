#include "Cursor.h"
#include "Screen.h"

namespace gdk
{
	namespace dx9
	{
		bool Cursor::Lock(false);

		Cursor::Cursor()
		{

		}

		Cursor::~Cursor()
		{

		}

		Int2 Cursor::ConvertMousePositionGlobalToLocal(POINT mousePosition)
		{
			RECT rect, adjustRect;

			GetWindowRect(Screen::Handle(), &rect);

			adjustRect = rect;
			AdjustWindowRect(&adjustRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
			mousePosition.x -= rect.left + (rect.left - adjustRect.left);
			mousePosition.y -= rect.top + (rect.top - adjustRect.top);

			return Int2(mousePosition.x, mousePosition.y);
		}

		POINT Cursor::ConvertMousePositionLocalToGlobal(Int2 mousePosition)
		{
			RECT rect, adjustRect;

			GetWindowRect(Screen::Handle(), &rect);

			adjustRect = rect;
			AdjustWindowRect(&adjustRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
			mousePosition.x += rect.left + (rect.left - adjustRect.left);
			mousePosition.y += rect.top + (rect.top - adjustRect.top);

			return { mousePosition.x, mousePosition.y };
		}
	}
}
