#include <Fragment/Fragment.h>
namespace Fragment
{
	short MemoryList::MemoryListHandleFindFunction(MemoryList::MemoryObject *Self, void* Object)
	{
		unsigned long RealHandle = *(unsigned long*)Object;
		if(Self->HandleID == RealHandle)
		{
			return 0;
		}
		else if(Self->HandleID < RealHandle)
		{
			return -1;
		}
		return 1;
	};

	MemoryList *HostList = nullptr;
	MemoryClient HostClient;

	MemoryList::MemoryObject::MemoryObject()
	{
		HandleID = 0;
		t = nullptr;
		Client = nullptr;
	};

	MemoryList::MemoryObject::~MemoryObject()
	{
		if(t)
		{
			delete t;
			HandleID = 0;
		};
	};

	MemoryList::MemoryList()
	{
		CurrHandleID = 0;
	};

	MemoryList::~MemoryList()
	{
	};

	void MemoryList::RegisterClient(MemoryClient *Client)
	{
		MutexLocker m(ListMutex);
		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == Client)
				return;
		};
		Clients.New();
		Clients.Last() = Client;
	};

	unsigned long MemoryList::Add(Fragment::IUnknown* Address)
	{
		MutexLocker m(ListMutex);
		FRASSERT(Address != nullptr, "Invalid Address!");

		bool FoundClient = false;
		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == &HostClient)
			{
				FoundClient = true;
				break;
			};
		};

		if(!FoundClient)
			return 0;

		for(unsigned long i = 0; i < List.Size(); i++)
		{
			if(List[i].t == Address)
			{
				return List[i].HandleID;
			};
		};

		for(unsigned long i = 0; i < ExclusiveList.Size(); i++)
		{
			if(ExclusiveList[i].t == Address)
			{
				return ExclusiveList[i].HandleID;
			};
		};

		List.New();
		List.Last().HandleID = ++CurrHandleID;
		List.Last().t = Address;
		List.Last().Client = &HostClient;
		return List.Last().HandleID;
	};

	unsigned long MemoryList::AddExclusive(Fragment::IUnknown* Address)
	{
		MutexLocker m(ListMutex);
		FRASSERT(Address != nullptr, "Invalid Address!");

		bool FoundClient = false;
		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == &HostClient)
			{
				FoundClient = true;
				break;
			};
		};

		if(!FoundClient)
			return 0;

		for(unsigned long i = 0; i < List.Size(); i++)
		{
			if(List[i].t == Address)
			{
				return List[i].HandleID;
			};
		};

		for(unsigned long i = 0; i < ExclusiveList.Size(); i++)
		{
			if(ExclusiveList[i].t == Address)
			{
				return ExclusiveList[i].HandleID;
			};
		};

		ExclusiveList.New();
		ExclusiveList.Last().HandleID = ++CurrHandleID;
		ExclusiveList.Last().t = Address;
		ExclusiveList.Last().Client = &HostClient;
		return ExclusiveList.Last().HandleID;
	};

	unsigned long MemoryList::Find(Fragment::IUnknown* Address)
	{
		MutexLocker m(ListMutex);
		for(unsigned long i = 0; i < List.Size(); i++)
		{
			if(List[i].t == Address)
			{
				return List[i].HandleID;
			};
		};

		for(unsigned long i = 0; i < ExclusiveList.Size(); i++)
		{
			if(ExclusiveList[i].t == Address)
			{
				return ExclusiveList[i].HandleID;
			};
		};

		return 0;
	};

	void MemoryList::Remove(unsigned long Handle)
	{
		MutexLocker m(ListMutex);
		FRASSERT(Handle != 0, "Invalid Handle!");

		{
			unsigned long ListMatch = List.BinarySearch(MemoryListHandleFindFunction, &Handle);
			
			if(ListMatch != 0xFFFFFFFF)
			{
				List.Erase(ListMatch);
				return;
			};
		};

		{
			unsigned long ListMatch = ExclusiveList.BinarySearch(MemoryListHandleFindFunction,
				&Handle);

			if(ListMatch != 0xFFFFFFFF)
			{
				ExclusiveList.Erase(ListMatch);
				return;
			};
		};
	};

	bool MemoryList::Exists(unsigned long Handle)
	{
		MutexLocker m(ListMutex);
		FRASSERT(Handle != 0, "Invalid Handle!");

		{
			unsigned long ListMatch = List.BinarySearch(MemoryListHandleFindFunction, &Handle);
			
			if(ListMatch != 0xFFFFFFFF)
			{
				return true;
			};
		};

		{
			unsigned long ListMatch = ExclusiveList.BinarySearch(MemoryListHandleFindFunction,
				&Handle);

			if(ListMatch != 0xFFFFFFFF)
			{
				ExclusiveList.Erase(ListMatch);
				return true;
			};
		};
		return false;
	};

	Fragment::IUnknown* MemoryList::Get(unsigned long Handle)
	{
		MutexLocker m(ListMutex);
		FRASSERT(Handle != 0, "Invalid Handle!");

		{
			unsigned long ListMatch = List.BinarySearch(MemoryListHandleFindFunction, &Handle);
			
			if(ListMatch != 0xFFFFFFFF)
			{
				return List[ListMatch].t;
			};
		};

		{
			unsigned long ListMatch = ExclusiveList.BinarySearch(MemoryListHandleFindFunction,
				&Handle);

			if(ListMatch != 0xFFFFFFFF)
			{
				return ExclusiveList[ListMatch].t;
			};
		};
		return nullptr;
	};

	void MemoryList::RemoveCurrentClient()
	{
		MutexLocker m(ListMutex);
		if(List.Size())
		{
			for(DynamicArray<MemoryObject>::Iterator it = List.Begin(); it != List.End(); it++)
			{
				if(it->Client == &HostClient)
				{
					it.Erase();
				};
			};
		};
		if(ExclusiveList.Size())
		{
			for(DynamicArray<MemoryObject>::Iterator it = ExclusiveList.Begin(); 
				it != ExclusiveList.End(); it++)
			{
				if(it->Client == &HostClient)
				{
					it.Erase();
				};
			};
		};

		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == &HostClient)
			{
				Clients.Erase(i);
				break;
			};
		};
		if(Clients.Size() == 0)
		{
			HostList = nullptr;
			delete this;
		};
	};

	MemoryClient::MemoryClient()
	{
	};

	MemoryClient::~MemoryClient()
	{
		if(GetMemoryList())
		{
			GetMemoryList()->RemoveCurrentClient();
		};
	};

	void FeedMemoryList(MemoryList *List)
	{
		if(HostList)
		{
			HostList->RemoveCurrentClient();
		};
		HostList = List;
		HostList->RegisterClient(&HostClient);
	};

	MemoryList *GetMemoryList()
	{
		return HostList;
	};

	void CreateDefaultMemoryList()
	{
		FeedMemoryList(new MemoryList);
	};
};
