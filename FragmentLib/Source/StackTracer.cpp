#include <Fragment/Fragment.h>
#include <stdio.h>
namespace Fragment
{
	IStackTracer *Stack = nullptr;

	class IStackClient
	{
	public:
		~IStackClient()
		{
			if(Stack)
			{
				Stack->UnregisterClient(this);
			}
		};
	};

	IStackClient TheStackClient;

	IStackTracer::IStackTracer()
	{
		ScopeLevel = 0;
	};

	void IStackTracer::ClearStack()
	{
		Root.Childs.Clear();
		ScopeLevel = 0;
	};

	void IStackTracer::PushObject(const char* Name, unsigned int Line, const char* File, bool Sub)
	{
		if(Root.Name.Length() == 0)
		{
			Root.Name = Name;
			Root.Line = Line;
			Root.File = File;
			Root.ScopeLevel = 0;
			TracerPath.New();
			TracerPath += &Root;
		}
		else
		{
			if(Sub)
			{
				ScopeLevel++;
				TracerPath.Last()->Childs.New();
				TracerPath.Last()->Childs.Last().Name = Name;
				TracerPath.Last()->Childs.Last().Line = Line;
				TracerPath.Last()->Childs.Last().File = File;
				TracerPath.Last()->Childs.Last().ScopeLevel = ScopeLevel;
				TracerPath += &TracerPath.Last()->Childs.Last();
			}
			else
			{
				TracerPath.Last()->Childs.New();
				TracerPath.Last()->Childs.Last().Name = Name;
				TracerPath.Last()->Childs.Last().Line = Line;
				TracerPath.Last()->Childs.Last().File = File;
				TracerPath.Last()->Childs.Last().ScopeLevel = ScopeLevel;
			};
		};
	};

	void IStackTracer::Pop()
	{
		if(ScopeLevel > 0)
		{
			TracerPath.Resize(TracerPath.Size() - 1);
			ScopeLevel--;
		};
	};

	void IStackTracer::GenTrackStrings(DynamicArray<StringA> &Copy, IStackTracerObject &Self, 
		IStackTracerObject *Parent, bool Histogram)
	{
		if(Parent != nullptr && Self.ScopeLevel != Parent->ScopeLevel)
		{
			Copy += StringA("{\n");
		};
		if(Histogram)
		{
			if(Copy.Size() == 0)
			{
				Copy += Self.Name;
			}
			else if(Copy.Size() % 3 == 0)
			{
				Copy += StringA(" -> ") + Self.Name + StringA("\n");
			}
			else
			{
				Copy += StringA(" -> ") + Self.Name;
			};
		}
		else
		{
			Copy += Self.Name + StringA(":") + Self.Line + //StringA(":") + Self.File + 
				StringA("\n");
		};
		for(unsigned long i = 0; i < Self.Childs.Size(); i++)
		{
			GenTrackStrings(Copy, Self.Childs[i], &Self, Histogram);
		};
		if(Parent != nullptr && Self.ScopeLevel != Parent->ScopeLevel)
		{
			Copy += StringA("}\n");
		};
	};

	const char* IStackTracer::Contents(bool Histogram)
	{
		ContentString = StringA();
		DynamicArray<StringA> Data;
		for(unsigned long i = 0; i < Root.Childs.Size(); i++)
		{
			GenTrackStrings(Data, Root.Childs[i], &Root, Histogram);
		};
		for(unsigned long i = 0; i < Data.Size(); i++)
		{
			ContentString += Data[i];
		};
		return ContentString.Get();
	};

	void IStackTracer::RegisterClient(void* Client)
	{
		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == Client)
			{
				return;
			}
		}
		Clients += Client;
	};

	void IStackTracer::UnregisterClient(void* Client)
	{
		for(unsigned long i = 0; i < Clients.Size(); i++)
		{
			if(Clients[i] == Client)
			{
				Clients.Erase(i);
				break;
			}
		}
		if(Clients.Size() == 0)
		{
			delete this;
		};
	};

	IStackTracer *GetStackTracer()
	{
		return Stack;
	};

	void FeedStackTracer(IStackTracer *Tracer)
	{
		if(Stack)
		{
			Stack->UnregisterClient(&TheStackClient);
		}
		Stack = Tracer;
		Tracer->RegisterClient(&TheStackClient);
	};

	void CreateDefaultStackTracer()
	{
		FeedStackTracer(new IStackTracer);
	};
};
