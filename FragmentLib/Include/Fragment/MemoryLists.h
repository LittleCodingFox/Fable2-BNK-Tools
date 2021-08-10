#ifndef FRAGMENTLIB_MEMORYLIST_H
#define FRAGMENTLIB_MEMORYLIST_H
namespace Fragment
{
	/*!
		\addtogroup memory Memory Services
		@{
	*/

	//!IUnknown is an interface to every object in Fragment
	class IUnknown
	{
	public:
		virtual ~IUnknown() {};
	};

	class MemoryClient;

	//!MemoryList is a class to store objects as handles and re-use them with Objects and ScopedObjects
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 5.0
		\date 25-3-2008
	*/
	class MemoryList
	{
	private:
		Mutex ListMutex;
		//!MemoryObject contains information about an object in the Memory List
		class MemoryObject
		{
		public:
			Fragment::IUnknown *t;
			unsigned long HandleID;
			MemoryClient *Client;
			MemoryObject();
			~MemoryObject();
		};
		DynamicArray<MemoryObject> List;
		DynamicArray<MemoryObject> ExclusiveList;
		Array<MemoryClient*> Clients;
		unsigned long CurrHandleID;
		static short MemoryListHandleFindFunction(MemoryObject *Self, 
			void* Object);
	public:
		MemoryList();
		~MemoryList();
		//!RegisterClient will register a client on the memory list
		/*!
			\param Client is the client to register
		*/
		void RegisterClient(MemoryClient *Client);
		//!Add adds an object to the Memory Pool
		/*!
			\param Address is what to add to the memory pool
			\return a handle to the object, or 0 on failure
		*/
		unsigned long Add(Fragment::IUnknown* Address);
		//!AddExclusive adds an objec tot the memory pool which will only be released after all other objects have been released.
		/*!
			\param Address is what to add to the memory pool
			\return a handle to the object, or 0 on failure
		*/
		unsigned long AddExclusive(Fragment::IUnknown *Address);
		//!Find finds a handle from an address
		/*!
			\param Address is the object to find
			\return a handle to the object, or 0 on failure
		*/
		unsigned long Find(Fragment::IUnknown* Address);

		//!Remove removes an object from the memory pool, and deletes it
		/*!
			\param Handle is the handle to remove
		*/
		void Remove(unsigned long Handle);
		//!Exists checks if a handle is still in the memory pool
		/*!
			\param Handle is the handle to check if it is still in the memory pool
			\return true on success, false on failure
		*/
		bool Exists(unsigned long Handle);

		//!RemoveCurrentClient will remove all objects from the current host memory client and remove the client from the list
		void RemoveCurrentClient();

		//!Get returns the object's address from a handle
		/*!
			\param Handle is the handle
			\return an address or nullptr on failure
		*/
		Fragment::IUnknown* Get(unsigned long Handle);
	};

	//!MemoryClient is a memory list client class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 2.0
		\date 25-3-2008
	*/
	class MemoryClient
	{
	public:
		MemoryClient();
		~MemoryClient();
	};

	//!FeedMemoryList will tell which memory list will be used globally
	/*!
		\param List is the list
	*/
	void FeedMemoryList(MemoryList *List);
	
	//!GetMemoryList will return the address of the current memory pool
	MemoryList *GetMemoryList();

	//!CreateDefaultMemoryList will create the default Memory List
	void CreateDefaultMemoryList();

	//!Object is a Memory List object holder
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 4.0
		\date 25-3-2008
	*/
	template<typename type>
	class Object
	{
	private:
		unsigned long HandleID;
	public:
		Object()
		{
			HandleID = 0;
		};

		//!Add an address to the memory list and object holder
		/*!
			\param Address is the address that will be added to this object holder and the memory list
		*/
		Object(type* Address)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = GetMemoryList()->Add(Address);
			FRASSERT(HandleID != 0, "Memory Error");
		};

		//!Set a Handle as the handle of this object
		/*!
			\param handle is the handle to be set
		*/
		Object(unsigned long handle)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			FRASSERT(handle != 0, "Invalid handle");
			HandleID = handle;
		};

		Object(const Object<type> &OtherObject)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = OtherObject.HandleID;
		};

		//!Dispose destroys the object contained in this Object
		void Dispose()
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			SILENTVOIDFRASSERT(HandleID != 0);
			GetMemoryList()->Remove(HandleID);
			HandleID = 0;
		};

		//!Swap swaps this Object's object with another object
		/*!
			\param Address is the new object's address
			\note to add a handle, use the overloaded handle version
		*/
		void Swap(type *Address)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			SILENTVOIDFRASSERT(Address)
			HandleID = GetMemoryList()->Add(Address);
		};

		//!Swap swaps this Object's object with another object
		/*!
			\param handle is the new object's Handle
			\note to add a raw object, use the overlodaded type* version
		*/
		void Swap(unsigned long handle)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = handle;
		};

		~Object()
		{
		};

		//!Handle returns the Handle of this object
		unsigned long Handle() const
		{
			return HandleID;
		};

		Object<type> &operator=(const Object<type> &OtherObject)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = OtherObject.HandleID;
			return *this;
		};

		//!Get returns the Object's object address
		type* Get() const
		{
			SILENTFRASSERT(GetMemoryList() != nullptr);
			SILENTFRASSERT(HandleID != 0)
			return (type*)GetMemoryList()->Get(HandleID);
		};

		type& operator * () const {
			return *(type*)GetMemoryList()->Get(HandleID);
		};

		type* operator -> () const {
			return (type*)GetMemoryList()->Get(HandleID);
		};

		operator void*()
		{
			return (void*)Get();
		};

		operator type*()
		{
			return (type*)Get();
		};

		operator bool()
		{
			return (Get()) ? (true) : (false);
		};
	};

	//!ScopedObject is a Memory List object holder that will destroy the object contained when it goes out of scope
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 6-5-2008
	*/
	template<typename type>
	class ScopedObject
	{
	private:
		unsigned long HandleID;
	public:
		ScopedObject()
		{
			HandleID = 0;
		};

		//!Add an address to the memory list and object holder
		/*!
			\param Address is the address that will be added to this object holder and the memory list
		*/
		ScopedObject(type* Address)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = GetMemoryList()->Add(Address);
			FRASSERT(HandleID != 0, "Memory Error");
		};

		//!Set a Handle as the handle of this object
		/*!
			\param handle is the handle to be set
		*/
		ScopedObject(unsigned long handle)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			FRASSERT(handle != 0, "Invalid handle");
			HandleID = handle;
		};

		ScopedObject(const Object<type> &OtherObject)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = OtherObject.HandleID;
		};

		//!Dispose destroys the object contained in this Object
		void Dispose()
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			SILENTVOIDFRASSERT(HandleID != 0);
			GetMemoryList()->Remove(HandleID);
			HandleID = 0;
		};

		//!Swap swaps this Object's object with another object
		/*!
			\param Address is the new object's address
			\note to add a handle, use the overloaded handle version
		*/
		void Swap(type *Address)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			SILENTVOIDFRASSERT(Address)
			Dispose();
			HandleID = GetMemoryList()->Add(Address);
		};

		//!Swap swaps this Object's object with another object
		/*!
			\param handle is the new object's Handle
			\note to add a raw object, use the overlodaded type* version
		*/
		void Swap(unsigned long handle)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			Dispose();
			HandleID = handle;
		};

		~ScopedObject()
		{
			if(HandleID && GetMemoryList())
			{
				GetMemoryList()->Remove(HandleID);
			};
		};

		//!Handle returns the Handle of this object
		unsigned long Handle() const
		{
			return HandleID;
		};

		ScopedObject<type> &operator=(const Object<type> &OtherObject)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = OtherObject.HandleID;
			return *this;
		};

		ScopedObject<type> &operator=(const unsigned long &OtherHandle)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = OtherHandle;
			return *this;
		};

		//!Get returns the Object's object address
		type* Get() const
		{
			SILENTFRASSERT(GetMemoryList() != nullptr);
			SILENTFRASSERT(HandleID != 0)
			return (type*)GetMemoryList()->Get(HandleID);
		};

		type& operator * () const {
			return *(type*)GetMemoryList()->Get(HandleID);
		};

		type* operator -> () const {
			return (type*)GetMemoryList()->Get(HandleID);
		};

		operator void*()
		{
			return (void*)Get();
		};

		operator type*()
		{
			return (type*)Get();
		};

		operator bool()
		{
			return (Get()) ? (true) : (false);
		};
	};

	//!ReadOnlyObject is a Memory List object holder that will not allow the modification of the Handle contained within
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 16-11-2008
	*/
	template<typename type>
	class ReadOnlyObject
	{
	private:
		unsigned long HandleID;
		ReadOnlyObject(const ReadOnlyObject<type> &Other)
		{
			FRASSERT(nullptr, 
				"Access violation: Attempting to modify a ReadOnly Object");
		};
	public:
		ReadOnlyObject()
		{
			HandleID = 0;
		};

		ReadOnlyObject(const unsigned long &HandleID)
		{
			this->HandleID = HandleID;
		};

		//!Add an address to the memory list and object holder
		/*!
			\param Address is the address that will be added to this object holder and the memory list
		*/
		ReadOnlyObject(type* Address)
		{
			FRASSERT(GetMemoryList() != nullptr, "MemoryList not set");
			HandleID = GetMemoryList()->Add(Address);
			FRASSERT(HandleID != 0, "Memory Error");
		};

		//!Get returns the Object's object address
		type* Get() const
		{
			SILENTFRASSERT(GetMemoryList() != nullptr);
			SILENTFRASSERT(HandleID != 0)
			return (type*)GetMemoryList()->Get(HandleID);
		};

		type& operator * () const {
			return *(type*)GetMemoryList()->Get(HandleID);
		};

		type* operator -> () const {
			return (type*)GetMemoryList()->Get(HandleID);
		};

		operator void*()
		{
			return (void*)Get();
		};

		operator type*()
		{
			return (type*)Get();
		};

		operator bool()
		{
			return (Get()) ? (true) : (false);
		};
	};

#define FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(Name) \
	typedef Object<I##Name> C##Name;\
	typedef ScopedObject<I##Name> CS##Name;\
	typedef ReadOnlyObject<I##Name> CR##Name;

#define FRAGMENTLIB_DECLARE_NON_INTERFACED_OBJECT(Name)\
	typedef I##Name C##Name;

	/*!
		@}
	*/
};
#endif
