#include "Cursor.h"
#include "Input.h"
#include "Screen.h"

namespace gdk
{
	namespace dx9
	{
		IDirectInput8* Input::input(nullptr);
		IDirectInputDevice8* Input::keyDevice(nullptr);
		IDirectInputDevice8* Input::mouseDevice(nullptr);
		BYTE Input::keyState[256];
		DIMOUSESTATE2 Input::mouseState;
		History<Int2, 2> Input::mousePosition(Int2::zero);

		Input::Input()
		{
			mousePosition.Clear(Int2(Screen::Size().x / 2, Screen::Size().y / 2));

			POINT mousePoint = Cursor::ConvertMousePositionLocalToGlobal(mousePosition[0]);

			SetCursorPos(mousePoint.x, mousePoint.y);

			if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&input, nullptr)))
			{
				return;
			}

			if (FAILED(input->CreateDevice(GUID_SysKeyboard, &keyDevice, nullptr)))
			{
				return;
			}

			if (FAILED(keyDevice->SetDataFormat(&c_dfDIKeyboard)))
			{
				return;
			}

			if (FAILED(keyDevice->SetCooperativeLevel(Screen::Handle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			{
				return;
			}

			if (FAILED(input->CreateDevice(GUID_SysMouse, &mouseDevice, nullptr)))
			{
				return;
			}

			if (FAILED(mouseDevice->SetDataFormat(&c_dfDIMouse2)))
			{
				return;
			}

			if (FAILED(mouseDevice->SetCooperativeLevel(Screen::Handle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			{
				return;
			}

			DIPROPDWORD diprop;
			diprop.diph.dwSize = sizeof(diprop);
			diprop.diph.dwHeaderSize = sizeof(diprop.diph);
			diprop.diph.dwObj = 0;
			diprop.diph.dwHow = DIPH_DEVICE;
			diprop.dwData = DIPROPAXISMODE_ABS;

			if (FAILED(mouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
			{
				return;
			}

			keyDevice->Acquire();

			mouseDevice->Acquire();
		}

		Input::~Input()
		{
			keyDevice->Unacquire();

			if (keyDevice)
			{
				keyDevice->Release();
				keyDevice = nullptr;
			}

			mouseDevice->Unacquire();

			if (mouseDevice)
			{
				mouseDevice->Release();
				mouseDevice = nullptr;
			}

			if (input)
			{
				input->Release();
				input = nullptr;
			}
		}

		void Input::Create()
		{
			static Input instance;
		}

		void Input::Check()
		{
			keyDevice->GetDeviceState(256, keyState);

			mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);

			// マウスの座標の取得
			POINT mousePoint;
			GetCursorPos(&mousePoint);

			mousePosition = Cursor::ConvertMousePositionGlobalToLocal(mousePoint);

			if (Cursor::Lock)
			{
				mousePoint = Cursor::ConvertMousePositionLocalToGlobal(Int2(Screen::Size().x / 2, Screen::Size().y / 2));

				SetCursorPos(mousePoint.x, mousePoint.y);
			}
		}

		// 状態を取得
		bool Input::GetKey(int keyCode)
		{
			return keyState[keyCode] & 0xf0;
		}

		Int2 Input::GetMousePosition()
		{
			return mousePosition;
		}

		Int2 Input::GetMouseDeltaPosition()
		{
			if (Cursor::Lock)
			{
				return Int2(Screen::Size().x / 2, Screen::Size().y / 2) - mousePosition[1];
			}
			else
			{
				return mousePosition[0] - mousePosition[1];
			}
		}
	}
}
