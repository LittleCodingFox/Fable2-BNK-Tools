#ifndef FRAGMENTLIB_STRINGS_H
#define FRAGMENTLIB_STRINGS_H
namespace Fragment
{
	/*!
		\addtogroup stringservices String Services
		@{
	*/

	class StringA;

	//!StringW is a 16-bit unicode String class
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 3.0
		\date 29-3-2008
	*/
	class StringW
	{
		friend class StringA;
	private:
		Array<wchar_t> StringData;
	public:
		StringW();
		StringW(const StringW &String);
		StringW(const StringA &String);
		StringW(const wchar_t *String);

		operator wchar_t*() const;

		wchar_t &operator[](const unsigned long Index);
		const wchar_t &operator[](const unsigned long Index) const;

		bool operator==(const StringW &String);
		bool operator==(const wchar_t *String);
		bool operator!=(const StringW &String);
		bool operator!=(const wchar_t *String);

		StringW& operator=(const StringW &o);
		StringW& operator=(const StringA &o);
		StringW& operator=(const wchar_t *String);
		StringW& operator=(float f);
		StringW& operator=(double d);
		StringW& operator=(unsigned int i);
		StringW& operator=(unsigned long l);
		StringW& operator=(unsigned long long ll);
		StringW& operator=(unsigned short s);
		StringW& operator=(int i);
		StringW& operator=(long l);
		StringW& operator=(long long ll);
		StringW& operator=(short s);
		StringW& operator=(wchar_t w);

		void operator+=(const StringW &o);
		void operator+=(const StringA &o);
		void operator+=(const wchar_t *String);
		void operator+=(float f);
		void operator+=(double d);
		void operator+=(unsigned int i);
		void operator+=(unsigned long l);
		void operator+=(unsigned long long ll);
		void operator+=(unsigned short s);
		void operator+=(int i);
		void operator+=(long l);
		void operator+=(long long ll);
		void operator+=(short s);
		void operator+=(wchar_t w);

		StringW operator+(const StringW &o);
		StringW operator+(const StringA &o);
		StringW operator+(const wchar_t *String);
		StringW operator+(float f);
		StringW operator+(double d);
		StringW operator+(unsigned int i);
		StringW operator+(unsigned long l);
		StringW operator+(unsigned long long ll);
		StringW operator+(unsigned short s);
		StringW operator+(int i);
		StringW operator+(long l);
		StringW operator+(long long ll);
		StringW operator+(short s);
		StringW operator+(wchar_t w);

		//!Split will split a String
		/*!
			\param Limits is a string containing each character to be interpreted as a limit between strings.
			\code
StringW Str(L"a, b, c");
DynamicArray<StringW> Letters = Str.Split(L", "); //now contains 3 StringWs, 'a', 'b', 'c'
			\endcode
			\return one String if it didnt split anything, else more than one Strings
		*/
		DynamicArray<StringW> Split(StringW Limits);

		//!Find will search for a character contained in the String
		/*!
			\param Character is the character to look for
			\param Reverse_Search should be true if you want to search from the end to the beginning of the string
			\param Start is the index from where to start looking
			\return -1 if not found, >= 0 if found
		*/
		long Find(wchar_t Character, bool Reverse_Search = false, unsigned long Start = 0);

		//!Find will search for a String contained in the String
		/*!
			\param Str is the String to look for
			\param Reverse_Search should be true if you want to search from the end to the beginning of the string
			\param Start is the index from where to start looking
			\return -1 if not found, >= 0 if found
		*/
		long Find(StringW Str, bool Reverse_Search = false, unsigned long Start = 0);

		//!Copy will copy a piece of a String
		/*!
			\param From is where to start copying
			\param To is where to stop copying
			\warning To may behave differently from expected. Take for instance, the following piece of code:
			\code
StringW Str(L"abc");
Str.Copy(0, Str.Length());
			\endcode
			It'll copy Str from the beginning to Str.Length() - 1
			So, if you do something like this:
			\code
StringW Str(L"abc");
Str.Copy(0, Str.Find(L"c"));
			\endcode
			you must replace the second line with
			\code
Str.Copy(0, Str.Find(L"c") + 1);
			\endcode
			Because 'c' would be excluded from the string.
		*/
		StringW Copy(unsigned long From, unsigned long To);

		//!Compare will compare two strings
		/*!
			\param From is where to start comparing
			\param To is where to end comparing
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return 0 if both strings are equal (the one where you called Compare, and String),
			non-0 if not equal.
		*/
		unsigned long Compare(unsigned long From, unsigned long To, StringW String);

		//!Compare will compare two strings
		/*!
			\param String is the string to compare
			\return 0 if both strings are equal (the one where you called Compare, and String),
			non-0 if not equal.
		*/
		unsigned long Compare(StringW String);

		//!PartialMatch will compare two strings until it finds a difference
		/*!
			\param From is where to start comparing
			\param To is where to end comparing
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return true if both strings are fully equal, false if not equal.
		*/
		bool PartialMatch(unsigned long From, unsigned long To, StringW String);

		//!PartialMatch will compare two strings until it finds a difference
		/*!
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return true if both strings are fully equal, false if not equal.
		*/
		bool PartialMatch(StringW String);

		//!Get will return the String's contents
		/*!
			\return nullptr if no content, else non-nullptr to it's content
		*/
		wchar_t *Get() const;

		//!Length will return the Length of the String's content
		unsigned long Length() const;
	};

	//!StringA is an ASCII String class
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 31-5-2008
	*/
	class StringA
	{
		friend class StringW;
	private:
		Array<char> StringData;
	public:
		StringA();
		StringA(const StringW &String);
		StringA(const StringA &String);
		StringA(const char *String);

		operator char*() const;

		char &operator[](const unsigned long Index);
		const char &operator[](const unsigned long Index) const;

		bool operator==(const StringA &String);
		bool operator==(const char *String);
		bool operator!=(const StringA &String);
		bool operator!=(const char *String);

		StringA& operator=(const StringW &o);
		StringA& operator=(const StringA &o);
		StringA& operator=(const char *String);
		StringA& operator=(float f);
		StringA& operator=(double d);
		StringA& operator=(unsigned int i);
		StringA& operator=(unsigned long l);
		StringA& operator=(unsigned long long ll);
		StringA& operator=(unsigned short s);
		StringA& operator=(int i);
		StringA& operator=(long l);
		StringA& operator=(long long ll);
		StringA& operator=(short s);
		StringA& operator=(char c);

		void operator+=(const StringW &o);
		void operator+=(const StringA &o);
		void operator+=(const char *String);
		void operator+=(float f);
		void operator+=(double d);
		void operator+=(unsigned int i);
		void operator+=(unsigned long l);
		void operator+=(unsigned long long ll);
		void operator+=(unsigned short s);
		void operator+=(int i);
		void operator+=(long l);
		void operator+=(long long ll);
		void operator+=(short s);
		void operator+=(char w);

		StringA operator+(const StringW &o);
		StringA operator+(const StringA &o);
		StringA operator+(const char *String);
		StringA operator+(float f);
		StringA operator+(double d);
		StringA operator+(unsigned int i);
		StringA operator+(unsigned long l);
		StringA operator+(unsigned long long ll);
		StringA operator+(unsigned short s);
		StringA operator+(int i);
		StringA operator+(long l);
		StringA operator+(long long ll);
		StringA operator+(short s);
		StringA operator+(char c);

		//!Split will split a String
		/*!
			\param Limits is a string containing each character to be interpreted as a limit between strings.
			\code
StringA Str("a, b, c");
DynamicArray<StringA> Letters = Str.Split(", "); //now contains 3 StringWs, 'a', 'b', 'c'
			\endcode
			\return one String if it didnt split anything, else more than one Strings
		*/
		DynamicArray<StringA> Split(StringA Limits);

		//!Find will search for a character contained in the String
		/*!
			\param Character is the character to look for
			\param Reverse_Search should be true if you want to search from the end to the beginning of the string
			\param Start is the index from where to start looking
			\return -1 if not found, >= 0 if found
		*/
		long Find(char Character, bool Reverse_Search = false, unsigned long Start = 0);

		//!Find will search for a String contained in the String
		/*!
			\param Str is the String to look for
			\param Reverse_Search should be true if you want to search from the end to the beginning of the string
			\param Start is the index from where to start looking
			\return -1 if not found, >= 0 if found
		*/
		long Find(StringA Str, bool Reverse_Search = false, unsigned long Start = 0);

		//!Copy will copy a piece of a String
		/*!
			\param From is where to start copying
			\param To is where to stop copying
			\warning To may behave differently from expected. Take for instance, the following piece of code:
			\code
StringA Str("abc");
Str.Copy(0, Str.Length());
			\endcode
			It'll copy Str from the beginning to Str.Length() - 1
			So, if you do something like this:
			\code
StringA Str("abc");
Str.Copy(0, Str.Find("c"));
			\endcode
			you must replace the second line with
			\code
Str.Copy(0, Str.Find("c") + 1);
			\endcode
			Because 'c' would be excluded from the string.
		*/
		StringA Copy(unsigned long From, unsigned long To);

		//!Compare will compare two strings
		/*!
			\param From is where to start comparing
			\param To is where to end comparing
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return 0 if both strings are equal (the one where you called Compare, and String),
			non-0 if not equal.
		*/
		unsigned long Compare(unsigned long From, unsigned long To, StringA String);

		//!Compare will compare two strings
		/*!
			\param String is the string to compare
			\return 0 if both strings are equal (the one where you called Compare, and String),
			non-0 if not equal.
		*/
		unsigned long Compare(StringA String);

		//!PartialMatch will compare two strings until it finds a difference
		/*!
			\param From is where to start comparing
			\param To is where to end comparing
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return true if both strings are fully equal, false if not equal.
		*/
		bool PartialMatch(unsigned long From, unsigned long To, StringA String);

		//!PartialMatch will compare two strings until it finds a difference
		/*!
			\param String is the string to compare
			\note The same warning from Copy applies here.
			\return true if both strings are fully equal, false if not equal.
		*/
		bool PartialMatch(StringA String);

		//!Get will return the String's contents
		/*!
			\return nullptr if no content, else non-nullptr to it's content
		*/
		char *Get() const;

		//!Length will return the Length of the String's content
		unsigned long Length() const;
	};

	/*!
		@}
	*/

	/*!
		\addtogroup arrayservices
		@{
	*/

	//!NamedArrayA is an Array that is sorted by strings
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 19-10-2008
	*/
	template<typename type>
	class NamedArrayA
	{
	private:
		class Pair
		{
		public:
			StringA Name;
			type t;
			Pair() {}
			Pair(const Pair &p) : t(p.t), Name(t.Name) {}
		};
		DynamicArray<Pair> Pairs;
	public:
		//!Iterator is a NamedArrayA iteration class
		/*!
			\author Nuno Miguel Azevedo Lopes Da Silva
			\version 1.0
			\date 19-10-2008
		*/
		class Iterator
		{
			friend class NamedArrayA;
		private:
			NamedArrayA<type> *Self;
			long CurrMemberID;
		public:
			Iterator()
			{
				Self = nullptr;
				CurrMemberID = -1;
			};
			//!operator++ will move the iterator one member to the front
			void operator++()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID + 1 < Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			void operator++(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID + 1 < Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			//!operator-- will move the iterator one member to the back
			void operator--()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};
			void operator--(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};
			inline type *operator->()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID < Self->Size())
				{
					return Self[CurrMemberID];
				};
				return nullptr;
			};

			inline type* Get()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID < Self->Size())
				{
					return Self[CurrMemberID];
				};
				return nullptr;
			};

			operator bool()
			{
				if(CurrMemberID == -1)
				{
					return false;
				};
				return true;
			};
			//!Erase will erase the current member
			void Erase()
			{
				if(CurrMemberID != -1 && CurrMemberID < Self->Size())
				{
					Self->Erase(CurrMemberID);
					if(CurrMemberID > 0)
					{
						CurrMemberID--;
					}
					else
					{
						CurrMemberID = -1;
					};
				};
			};
			bool operator!=(const Iterator &Other)
			{
				return !(Other.CurrMemberID == CurrMemberID && Other.Self == Self);
			};
		};

		type &operator[](const unsigned long Position)
		{
			return Pairs[Position].t;
		};

		type &operator[](const char* Name)
		{
			for(unsigned long i = 0; i < Pairs.Size(); i++)
			{
				if(Pairs[i].Name.PartialMatch(Name))
				{
					return Pairs[i].t;
				};
			};
			Pairs.New();
			Pairs.Last().Name = Name;
			return Pairs.Last().t;
		};

		type &operator[](const StringA &Name)
		{
			for(unsigned long i = 0; i < Pairs.Size(); i++)
			{
				if(Pairs[i].Name.PartialMatch(Name))
				{
					return Pairs[i].t;
				};
			};
			Pairs.New();
			Pairs.Last().Name = Name;
			Pairs.Last().t = new type;
			return Pairs.Last().t;
		};

		NamedArrayA<type> operator+(const NamedArrayA<type> &Other)
		{
			*this.Pairs = *this.Pairs + Other.Pairs;
		};

		void operator+=(const NamedArrayA<type> &Other)
		{
			*this.Pairs = *this.Pairs + Other.Pairs;
		};

        //!Erase erases a element of the array by its number (ID)
        /*!
        	\param ID is the element's ID
        */
		void Erase(unsigned long ID)
		{
			Pairs.Erase(ID);
		};

        //!Clear frees all data allocated
        /*!
        	\sa Erase()
        */
		void Clear()
		{
			Pairs.Clear();
		};

		//!Size returns the number of members in the array
        /*!
        	\return Number of members in the array
        */
        inline unsigned long Size() const
        {
            return Pairs.Size(); //Return the current number of elements on our pointer
        };

		//!Last returns the last element of the array
		inline type &Last()
		{
			return Pairs.Last().t;
		};

		//!Begin will provide an Iterator for this array
		Iterator Begin()
		{
			if(Size() == 0)
				return End();
			Iterator it;
			it.Self = this;
			it.CurrMemberID = 0;
			return it;
		};

		//!End will provide the Iterator symbolizing the end of this array
		Iterator End()
		{
			Iterator it;
			it.Self = this;
			it.CurrMemberID = -1;
			return it;
		};
	};

	//!NamedArrayA is an Array that is sorted by strings
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 19-10-2008
	*/
	template<typename type>
	class NamedArrayW
	{
	private:
		class Pair
		{
		public:
			StringW Name;
			type t;
			Pair() {}
			Pair(const Pair &p) : t(p.t), Name(t.Name) {}
		};
		DynamicArray<Pair> Pairs;
	public:
		//!Iterator is a NamedArrayA iteration class
		/*!
			\author Nuno Miguel Azevedo Lopes Da Silva
			\version 1.0
			\date 19-10-2008
		*/
		class Iterator
		{
			friend class NamedArrayW;
		private:
			NamedArrayW<type> *Self;
			long CurrMemberID;
		public:
			Iterator()
			{
				Self = nullptr;
				CurrMemberID = -1;
			};
			//!operator++ will move the iterator one member to the front
			void operator++()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID + 1 < Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			void operator++(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID + 1 < Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			//!operator-- will move the iterator one member to the back
			void operator--()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};
			void operator--(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};
			inline type *operator->()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID < Self->Size())
				{
					return Self[CurrMemberID];
				};
				return nullptr;
			};

			inline type* Get()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID < Self->Size())
				{
					return Self[CurrMemberID];
				};
				return nullptr;
			};

			operator bool()
			{
				if(CurrMemberID == -1)
				{
					return false;
				};
				return true;
			};
			//!Erase will erase the current member
			void Erase()
			{
				if(CurrMemberID != -1 && CurrMemberID < Self->Size())
				{
					Self->Erase(CurrMemberID);
					if(CurrMemberID > 0)
					{
						CurrMemberID--;
					}
					else
					{
						CurrMemberID = -1;
					};
				};
			};
			bool operator!=(const Iterator &Other)
			{
				return !(Other.CurrMemberID == CurrMemberID && Other.Self == Self);
			};
		};

		type &operator[](const unsigned long Position)
		{
			return Pairs[Position].t;
		};

		type &operator[](const wchar_t* Name)
		{
			for(unsigned long i = 0; i < Pairs.Size(); i++)
			{
				if(Pairs[i].Name.PartialMatch(Name))
				{
					return Pairs[i].t;
				};
			};
			Pairs.New();
			Pairs.Last().Name = Name;
			return Pairs.Last().t;
		};

		type &operator[](const StringW &Name)
		{
			for(unsigned long i = 0; i < Pairs.Size(); i++)
			{
				if(Pairs[i].Name.PartialMatch(Name))
				{
					return Pairs[i].t;
				};
			};
			Pairs.New();
			Pairs.Last().Name = Name;
			Pairs.Last().t = new type;
			return Pairs.Last().t;
		};

		NamedArrayW<type> operator+(const NamedArrayW<type> &Other)
		{
			*this.Pairs = *this.Pairs + Other.Pairs;
		};

		void operator+=(const NamedArrayW<type> &Other)
		{
			*this.Pairs = *this.Pairs + Other.Pairs;
		};

        //!Erase erases a element of the array by its number (ID)
        /*!
        	\param ID is the element's ID
        */
		void Erase(unsigned long ID)
		{
			Pairs.Erase(ID);
		};

        //!Clear frees all data allocated
        /*!
        	\sa Erase()
        */
		void Clear()
		{
			Pairs.Clear();
		};

		//!Size returns the number of members in the array
        /*!
        	\return Number of members in the array
        */
        inline unsigned long Size() const
        {
            return Pairs.Size(); //Return the current number of elements on our pointer
        };

		//!Last returns the last element of the array
		inline type &Last()
		{
			return Pairs.Last().t;
		};

		//!Begin will provide an Iterator for this array
		Iterator Begin()
		{
			if(Size() == 0)
				return End();
			Iterator it;
			it.Self = this;
			it.CurrMemberID = 0;
			return it;
		};

		//!End will provide the Iterator symbolizing the end of this array
		Iterator End()
		{
			Iterator it;
			it.Self = this;
			it.CurrMemberID = -1;
			return it;
		};
	};
};
#endif
