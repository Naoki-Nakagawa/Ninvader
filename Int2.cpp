#include "Int2.h"

namespace gdk
{
	namespace dx9
	{
		Int2 Int2::zero(0, 0);

		Int2::Int2() :
			x(0),
			y(0)
		{

		}

		Int2::Int2(const int& x, const int& y) :
			x(x),
			y(y)
		{

		}

		Int2::~Int2()
		{

		}

		Int2 Int2::operator - (Int2 value)
		{
			return Int2(x - value.x, y - value.y);
		}

		Int2::operator POINT()
		{
			return { x, y };
		}
	}
}
