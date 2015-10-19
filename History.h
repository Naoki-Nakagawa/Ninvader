#ifndef _GdkDx9_History_h_
#define _GdkDx9_History_h_

namespace gdk
{
	namespace dx9
	{
		template<typename T, int length>
		class History
		{
		private:

			T memento[length];

			void SetMemento(T value)
			{
				for (int i = length - 1; i > 0; --i)
				{
					memento[i] = memento[i - 1];
				}

				memento[0] = value;
			}

		public:

			History() :
				memento()
			{

			}

			History(T value) :
				memento()
			{
				for (int i = 0; i < length; ++i)
				{
					SetMemento(value);
				}
			}

			~History()
			{

			}

			void operator = (T value)
			{
				SetMemento(value);
			}

			T* operator -> ()
			{
				return &memento[0];
			}

			operator T()
			{
				return memento[0];
			}

			T operator [] (int index)
			{
				return memento[index];
			}

			void Clear(T value)
			{
				for (int i = 0; i < length; ++i)
				{
					SetMemento(value);
				}
			}

			int Length()
			{
				return length;
			}
		};
	}
}

#endif	// _GdkDx9_History_h_
