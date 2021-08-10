#ifndef FRAGMENTLIB_ARRAYS_H
#define FRAGMENTLIB_ARRAYS_H
namespace Fragment
{
	/*!
		\addtogroup arrayservices Array Services
		@{
	*/

	//!Array is a normal array similar to std::vector
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 5.1
		\date 25-3-2008
	*/
    template<typename type>
    class Array
    {
    private:
        unsigned long AllocatedSize;
        type *t;
    public:
		//!Iterator is an array iteration class
		/*!
			\author Nuno Miguel Azevedo Lopes Da Silva
			\version 1.0
			\date 6-8-2008
		*/
		class Iterator
		{
			friend class Array;
		private:
			Array<type> *Self;
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
					return Self->Get() + CurrMemberID;
				};
				return nullptr;
			};

			inline type* Get()
			{
				FRASSERT(Self, "Attempted to access a non-existing Array iterator!");
				if(CurrMemberID < Self->Size())
				{
					return Self->Get() + CurrMemberID;
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
        //!Constructor
        Array()
        {
            AllocatedSize = 0;
			t = nullptr;
        };

        //!Copy Constructor
        Array(const Array &Other)
        {
            AllocatedSize = 0;
			t = nullptr;
            *this = Other;
        };

		Array(unsigned long Size)
		{
			AllocatedSize = 0;
			t = nullptr;
			Allocate(Size);
		};

        Array<type> &operator=(const Array<type> &Other)
        {
			if(Other.Size() == 0)
			{
				this->Clear();
				return *this;
			};
            Allocate(Other.Size());
            for (unsigned long i=0; i < Other.Size(); i++)
            {
                (*this)[i] = Other[i];
            };
			return *this;
        };

		Array<type> operator+(const Array<type> &Other)
		{
			if(Other.Size() == 0)
			{
				return *this;
			};
			Array<type> Temp = *this;
			Temp.Resize(Temp.Size() + Other.Size());
			for(unsigned long i = Temp.Size() - Other.Size(); i < Temp.Size(); i++)
			{
				Temp[i] = Other[i - (Temp.Size() - Other.Size())];
			};
			return Temp;
		};

		void operator+=(const Array<type> &Other)
		{
			*this = *this + Other;
		};

		void operator+=(const type &Other)
		{
			New();
			Last() = Other;
		};

		//!BinarySearch will search for a member in the Array
		/*!
			\param SearchFunction is a function pointer that should return -1 
				if the member should be to the left, 1 if the member should be to the right, 
				and 0 if the member was found.
			\param Object is the Object to pass to SearchFunction
			\note the Array must be sorted left to right
			\return 0xFFFFFFFF on failure, member index on success
		*/
		unsigned long BinarySearch(short (*SearchFunction)(type *t, void* Object), void* Object)
		{
			unsigned long Match = 0xFFFFFFFF;
			unsigned long i = 0, j = Size();
			while(i < j)
			{
				unsigned long m = (i + j) / 2;
				short Validation = SearchFunction(&(*this)[m], Object);
				bool Break = false;
				switch(Validation)
				{
				case -1:
					{
						i = m + 1;
					}
					break;
				case 0:
					{
						Match = m;
						Break = true;
					}
					break;
				case 1:
					{
						j = m;
					}
					break;
				};
				if(Break)
					break;
			};
			return Match;
		};

		//!Copy will copy a piece of an array to another array
		/*!
			\param From is where to start copying
			\param To is where to end copying
			\return an Array with the copy
		*/
		Array<type> Copy(unsigned long From, unsigned long To)
		{
			Array<type> Data;
			if(From >= To || From > Size() || To > Size())
				return Data;
			Data.Allocate(To - From);
			for(unsigned long i = From; i < To; i++)
			{
				Data[i - From] = (*this)[i];
			};
			return Data;
		};

		//!Move will move an element from the array
		/*!
			\param From is where the element to move is
			\param To is where to move the element
		*/
		void Move(unsigned long From, unsigned long To)
		{
			if(Size() == 0)
				return;
			Array<type> Data = *this;
			Data[From] = (*this)[To];
			Data[To] = (*this)[From];
			*this = Data;
		};

        //!Erase erases a element of the array by its number (ID)
        /*!
        	\param ID is the element's ID
        */
        void Erase(unsigned long ID)
        {
            FRASSERT(ID < Size(), "Invalid element ID, \nmake sure you're choosing the right ID, \nit must be less than the total allocated size");
			SILENTVOIDFRASSERT(Size() != 0);
			if(Size() - 1 == 0 && ID == 0)
			{
				Clear();
				return;
			};
            Array<type> T2;
            T2.Allocate(Size()-1);
			unsigned long Curr = 0;
            for (unsigned long i=0; i < Size(); i++)
            {
                if (i == ID)
                    continue;
                T2[Curr++] = (*this)[i];
            };
			*this = T2;
        };

        //!Resize resizes the total elements on the array
        /*!
        	\param numofobjects is the total ammount of elements to contain in the array
        */
        void Resize(unsigned long numofobjects)
        {
            FRASSERT(numofobjects > 0, "Total Elements to resize to must be bigger than 0"); //Make sure we got a valid number of objects
            if (Size() > 0) //If we've already got at least one object
            {
                Array<type> T2(numofobjects);
                unsigned long RealSize = (Size() > (unsigned long)numofobjects) ? (unsigned long)numofobjects : Size();
                for (unsigned long i=0; i < RealSize; i++)
                {
                    T2[i] = (*this)[i];
                };
				*this = T2;
            }
            else //we dont have any objects
            {
                Allocate(numofobjects);
            };
        };

		inline const type& operator[](const unsigned long num) const
		{
			FRASSERT(num < AllocatedSize, "Out Of Bounds Array Access!");
			return t[num];
		};

		inline type& operator[](const unsigned long num)
		{
			FRASSERT(num < AllocatedSize, "Out Of Bounds Array Access!");
			return t[num];
		};

        //!Allocate allocates a specified ammount of members of the array
        /*!
        	\param Total is the total elements to allocate
        */
        void Allocate(unsigned long Total)
        {
            FRASSERT(Total > 0, "Invalid total elements to allocate"); //Make sure Total is valid
            Clear();
            t = new type[Total];
            AllocatedSize = Total;
        };

		inline type *Get() const
		{
			return t;
		};

        //!Clear frees all data allocated
        /*!
        	\sa Erase()
        */
        void Clear()
        {
			if(t != 0)
			{
				delete [] t;
				t = 0;
			};
            AllocatedSize = 0;
        };

        //!Size returns the number of members in the array
        /*!
        	\return Number of members in the array
        */
        inline unsigned long Size() const
        {
            return AllocatedSize; //Return the current number of elements on our pointer
        };

		//!New adds a new element to the array
		void New()
		{
			Resize(Size() + 1);
		};

		//!RemoveLast will remove the last element of the array
		void RemoveLast()
		{
			if(Size() > 1)
			{
				Resize(Size() - 1);
			}
			else
			{
				Clear();
			};
		};

		//!Last returns the last element of the array
		inline type &Last()
		{
			FRASSERT(Size() > 0, "Empty Array!");
			return t[Size() - 1];
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

        //!Deconstructor
        ~Array()
        {
            Clear(); //Free everything
        };
    };
	//!DynamicArray is a dynamic array similar to std::vector, but that keeps its member's memory address, and uses a linked list instead of a normal array.
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 3.1
		\date 25-3-2008
	*/
    template<typename type>
    class DynamicArray
    {
    private:
        unsigned long AllocatedSize;
		Array<type*> CacheList;
        class MemoryNode
        {
        public:
            type *t;
            MemoryNode *Next,*Prev;
            MemoryNode()
            {
                t = 0;
                Next = Prev = 0;
            };
            void Create()
            {
                Destroy();
                t = new type;
            };
            void Destroy()
            {
                MemoryNode *n = Next;
                MemoryNode *p = Prev;
                if (Prev)
                    p->Next = n;
                if (Next)
                    n->Prev = p;
				if(t != nullptr)
				{
	                delete t;
					t = nullptr;
				};
                Next = 0;
                Prev = 0;
            };
            ~MemoryNode()
            {
				Destroy();
            };
        };
        MemoryNode *List;
    public:
		//!Iterator is an array iteration class
		/*!
			\author Nuno Miguel Azevedo Lopes Da Silva
			\version 1.0
			\date 6-8-2008
		*/
		class Iterator
		{
			friend class DynamicArray;
		private:
			DynamicArray<type> *Self;
			long CurrMemberID;
		public:
			Iterator()
			{
				Self = nullptr;
				CurrMemberID = -1;
			};
			//!operator++ will move the iterator one member to the front
			inline void operator++()
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				if(CurrMemberID + 1 < Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			inline void operator++(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				if(CurrMemberID + 1 < (long)Self->Size())
				{
					CurrMemberID++;
				}
				else
				{
					CurrMemberID = -1;
				};
			};
			//!operator-- will move the iterator one member to the back
			inline void operator--()
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};
			inline void operator--(int)
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				if(CurrMemberID > 0)
				{
					CurrMemberID--;
				};
			};

			inline type *operator->()
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				FRASSERT(CurrMemberID >= 0, "Invalid member access!");
				if(CurrMemberID < (long)Self->Size())
				{
					return &((*Self)[CurrMemberID]);
				};
				return nullptr;
			};

			inline type* Get()
			{
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				FRASSERT(CurrMemberID >= 0, "Invalid member access!");
				if(CurrMemberID < (long)Self->Size())
				{
					return &((*Self)[CurrMemberID]);
				};
				return nullptr;
			};

			inline operator bool()
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
				FRASSERT(Self, "Attempted to access a non-existing DynamicArray iterator!");
				if(CurrMemberID != -1 && CurrMemberID < (long)Self->Size())
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
        //!Constructor
        DynamicArray()
        {
            AllocatedSize = 0;
            List = nullptr;
        };
        //!Copy Constructor
        DynamicArray(const DynamicArray &Other)
        {
            AllocatedSize = 0;
            List = nullptr;
            *this = Other;
        };

		DynamicArray(unsigned long Size)
		{
			AllocatedSize = 0;
			List = nullptr;
			Allocate(Size);
		};

		DynamicArray<type> &operator=(const DynamicArray<type> &o)
		{
			Clear();
			if(o.Size() != 0)
			{
				Allocate(o.Size());
				DynamicArray<type> &realo = const_cast<DynamicArray<type>& >(o);
				MemoryNode *Node = List;
				for(unsigned long i = 0; i < realo.Size(); i++)
				{
					(*this)[i] = realo[i];
					Node = Node->Next;
				};
			}
			return *this;
		};

		void operator+=(const DynamicArray<type> &Other)
		{
			Resize(Size() + Other.Size());
			if(Other.Size())
			{
				DynamicArray<type> &realo = const_cast<DynamicArray<type>& >(Other);
				for(unsigned long i = 0; i < realo.Size(); i++)
				{
					(*this)[Size() - Other.Size() + i] = realo[i];
				};
			};
		};

		void operator+=(const type &Other)
		{
			New();
			Last() = Other;
		};

		//!New adds a new element to the array
		void New()
		{
			Resize(Size() + 1);
		};

		//!RemoveLast will remove the last element of the array
		void RemoveLast()
		{
			if(Size() > 1)
			{
				Resize(Size() - 1);
			}
			else
			{
				Clear();
			};
		};

		//!GetLast returns the last element of the array
		inline type &Last()
		{
			FRASSERT(Size() > 0, "Empty Array!");
			MemoryNode *Node = List;
            while(Node->Next != nullptr)
            {
                Node = Node->Next;
            };
			return *Node->t;
		};

		//!BinarySearch will search for a member in the Array
		/*!
			\param SearchFunction is a function pointer that should return -1 
				if the member should be to the left, 1 if the member should be to the right, 
				and 0 if the member was found.
			\param Object is the Object to pass to SearchFunction
			\note the Array must be sorted left to right
			\return 0xFFFFFFFF on failure, member index on success
		*/
		unsigned long BinarySearch(short (*SearchFunction)(type *t, void* Object), void* Object)
		{
			unsigned long Match = 0xFFFFFFFF;
			unsigned long i = 0, j = Size();
			DynamicArray<type> &self = *this;
			while(i < j)
			{
				unsigned long m = (i + j) / 2;
				short Validation = SearchFunction(&self[m], Object);
				bool Break = false;
				switch(Validation)
				{
				case -1:
					{
						i = m + 1;
					}
					break;
				case 0:
					{
						Match = m;
						Break = true;
					}
					break;
				case 1:
					{
						j = m;
					}
					break;
				};
				if(Break)
					break;
			};
			return Match;
		};

		//!Copy will copy a piece of an array to another array
		/*!
			\param From is where to start copying
			\param To is where to end copying
			\return an Array with the copy
		*/
		DynamicArray<type> Copy(unsigned long From, unsigned long To)
		{
			DynamicArray<type> Data;
			if(From >= To || From > Size() || To > Size())
				return Data;
			Data.Allocate(To - From);
			for(unsigned long i = From; i < To; i++)
			{
				Data[i - From] = (*this)[i];
			};
			return Data;
		};

		//!Move will move an element from the array
		/*!
			\param From is where the element to move is
			\param To is where to move the element
		*/
		void Move(unsigned long From, unsigned long To)
		{
			if(Size() == 0)
				return;
			DynamicArray<type> Data = *this;
			Data[From] = (*this)[To];
			Data[To] = (*this)[From];
			*this = Data;
		};

        //!Erase erases a element of the array by its number (ID)
        /*!
        	\param ID is the element's ID
        */
        void Erase(unsigned long ID)
        {
            FRASSERT(ID < Size(),"Invalid element ID, \nmake sure you're choosing the right ID, \nit must be less than the total allocated size");
            MemoryNode *Node = List;
            unsigned long OldSize = Size();
            for (unsigned long i=0; i < OldSize; i++)
            {
                if (!Node)
                    return;
                if (i == (unsigned long)ID)
                {
                    if (Node == List)
                        List = Node->Next;
                    AllocatedSize--;
					CacheList.Erase(i);
                    delete Node;
                    Node = 0;
                    return;
                }
                Node = Node->Next;
            };
        };

        //!Resize resizes the total elements on the array
        /*!
        	\param numofobjects is the total ammount of elements to contain in the array
        */
        void Resize(unsigned long numofobjects)
        {
            FRASSERT(numofobjects > 0, "Total Elements to resize to must be bigger than 0"); //Make sure we got a valid number of objects
            if (Size() > 0) //If we've already got at least one object
            {
                if (numofobjects < Size())
                {
                    unsigned long OldSize = Size();
		            MemoryNode *Node = List;
                    for (unsigned long i=0; i < OldSize; i++)
                    {
                        if (i >= numofobjects)
                        {
							MemoryNode *Temp = Node->Next;
                            AllocatedSize--;
							CacheList.Erase(i);
							delete Node;
							Node = Temp;
                        };
		                Node = Node->Next;
                    };
                }
                MemoryNode *Node = List;
                unsigned long OldSize = Size();
				MemoryNode *Temp = nullptr;
				while(Node->Next != nullptr)
				{
					Temp = Node;
					Node = Node->Next;
				};
				CacheList.Resize(numofobjects);
				for (unsigned long i=OldSize; i < numofobjects; i++)
				{
					Temp = Node;
					Node->Next = new MemoryNode;
					Node = Node->Next;
					Node->Create();
					CacheList[i] = Node->t;
					Node->Prev = Temp;
					AllocatedSize++;
				};
            }
            else //we dont have any objects
            {
				Allocate(numofobjects);
            };
        };

        inline const type& operator[](unsigned long num) const
        {
			FRASSERT(num < AllocatedSize, "Out Of Bounds Array Access!");
            return *CacheList[num];
        };

		inline type& operator[](unsigned long num)
        {
			FRASSERT(num < AllocatedSize, "Out Of Bounds Array Access!");
            return *CacheList[num];
        };

		//!Allocate allocates a specified ammount of members of the array
        /*!
        	\param Total is the total elements to allocate
        */
        void Allocate(unsigned long Total)
        {
            FRASSERT(Total > 0, "Total members to allocate must be bigger than 0") //Make sure Total is valid
            Clear();
            MemoryNode *Node = nullptr, *Temp = nullptr;
            List = new MemoryNode;
            List->Create();
			CacheList.Allocate(Total);
			CacheList[0] = List->t;
            AllocatedSize++;
            Node = List;
			Temp = List;
            for (unsigned long i=1; i < Total; i++)
            {
                Node->Next = new MemoryNode;
				Temp = Node;
                Node = Node->Next;
                Node->Create();
				Node->Prev = Temp;
				CacheList[i] = Node->t;
                AllocatedSize++;
            };
        };

        //!Free frees all data allocated
        /*!
        	\sa Erase()
        */
        void Clear()
        {
            MemoryNode *Node = List;
            while (Node != nullptr)
            {
                MemoryNode *Next = Node->Next;
                AllocatedSize--;
                delete Node;
                Node = Next;
            }
			CacheList.Clear();
            List = nullptr;
            AllocatedSize = 0;
        };

        //!Size returns the number of members in the array
        /*!
        	\return Number of members in the array
        */
        inline unsigned long Size() const
        {
            return AllocatedSize; //Return the current number of elements on our pointer
        };

		//!Begin will provide an Iterator for this array
		Iterator Begin()
		{
			Iterator it;
			it.Self = this;
			it.CurrMemberID = (Size() > 0) ? (0) : (-1);
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

        //!Deconstructor
        ~DynamicArray()
        {
            Clear(); //Free everything
        };
    };

	/*!
		@}
	*/
}
#endif
