#ifndef _GdkDx9_Debug_h_
#define _GdkDx9_Debug_h_

#include <string>

namespace gdk
{
	namespace dx9
	{
		class Debug
		{
		private:

			Debug();

			~Debug();

		public:

			static void Log(const std::string& message);

		};
	}
}

#endif	// _GdkDx9_Debug_h_
