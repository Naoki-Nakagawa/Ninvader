#include <iostream>
#include <Windows.h>
#include "Debug.h"

using namespace std;

namespace gdk
{
	namespace dx9
	{
		Debug::Debug()
		{

		}


		Debug::~Debug()
		{

		}

		void Debug::Log(const string& message)
		{
			cout << message;
			OutputDebugString(message.c_str());
		}
	}
}
