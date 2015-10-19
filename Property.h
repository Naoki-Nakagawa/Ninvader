#ifndef _GdkDx9_Property_h_
#define _GdkDx9_Property_h_

namespace gdk
{
	namespace dx9
	{
		template <typename T, T setter(T&), T getter(T&)>
		class Property
		{
		private:

			T property;

		public:

			Property() :
				property()
			{

			}

			Property(T value) :
				property(value)
			{

			}

			~Property()
			{

			}

			void operator = (T value)
			{
				if (!setter)
				{
					property = value;
				}
				else
				{
					property = setter(value);
				}
			}

			T* operator -> ()
			{
				if (!getter)
				{
					return &property;
				}
				else
				{
					return &getter(property);
				}
			}

			operator T()
			{
				if (!getter)
				{
					return property;
				}
				else
				{
					return getter(property);
				}
			}

		};
	}
}

#endif	// _GdkDx9_Property_h_
