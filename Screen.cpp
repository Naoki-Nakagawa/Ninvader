#include <Windows.h>
#include "Debug.h"
#include "Input.h"
#include "Render.h"
#include "Screen.h"

using namespace std;

namespace gdk
{
	namespace dx9
	{
		HWND Screen::handle(nullptr);

		std::string Screen::name("GdkDx9");

		Int2 Screen::size(Int2(800, 600));

		Screen::Screen()
		{
			// ウィンドウクラスの設定
			WNDCLASSEX wcex;
			ZeroMemory(&wcex, sizeof(wcex));
			wcex.lpfnWndProc = Procedure;
			wcex.hInstance = GetModuleHandle(nullptr);
			wcex.lpszClassName = name.c_str();
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpszMenuName = name.c_str();
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

			// ウィンドウクラスの登録
			if (!RegisterClassEx(&wcex))
			{
				return;
			}

			// ウィンドウの生成
			handle = CreateWindow(name.c_str(), name.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, wcex.hInstance, nullptr);

			if (!handle)
			{
				return;
			}

			// サイズの変更
			Size(size);

			// ウィンドウの表示
			ShowWindow(handle, SW_SHOWNORMAL);
			ValidateRect(handle, 0);
		}

		Screen::~Screen()
		{
			Debug::Log("delete\n");
		}

		LRESULT CALLBACK Screen::Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if (msg == WM_DESTROY)
			{
				PostQuitMessage(0);
				return 0;
			}

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		Int2 Screen::AdjustSize(const Int2& size)
		{
			RECT rect = { 0, 0, size.x, size.y };

			AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

			return Int2(rect.right - rect.left, rect.bottom - rect.top);
		}

		void Screen::Create()
		{
			static Screen instance;
		}

		bool Screen::Message()
		{
			static MSG msg;

			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
				{
					return false;
				}
			}

			Render::Present();
			Render::Clear(0x00000000);
			Input::Check();

			return true;
		}

		HWND Screen::Handle()
		{
			return handle;
		}

		string Screen::Name()
		{
			return name;
		}

		void Screen::Name(const string& value)
		{
			name = value;

			SetWindowText(handle, value.c_str());
		}

		Int2 Screen::Size()
		{
			return size;
		}

		void Screen::Size(const Int2& value)
		{
			size = value;

			Int2& adjustSize = AdjustSize(value);

			SetWindowPos(handle, nullptr, 960 - adjustSize.x / 2, 540 - adjustSize.y / 2, adjustSize.x, adjustSize.y, 0);
		}
	}
}
