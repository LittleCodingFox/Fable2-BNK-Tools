#include <Fragment/Fragment.h>
namespace Fragment
{
	struct TranslationHeader
	{
	public:
		unsigned char ID[3]; //'F' 'R' 'T'
		unsigned long Version;
		unsigned long BlockCount;
		bool Unicode; //StringW or StringA?
	};

	bool ITranslationInfo::Serialize(CStream Stream)
	{
		if(Blocks.Size() == 0)
			return false;
		if(!Stream.Get())
			return false;
		TranslationHeader Header;
		Header.ID[0] = 'F';
		Header.ID[1] = 'R';
		Header.ID[2] = 'T';
		Header.Version = 1;
#ifdef FRPLATFORM_UNICODE
		Header.Unicode = true;
#else
		Header.Unicode = false;
#endif
		Header.BlockCount = Blocks.Size();
		if(!Stream->Write(&Header, sizeof(Header), 1))
		{
			return false;
		};
		for(unsigned long i = 0; i < Blocks.Size(); i++)
		{
			unsigned long Length = Blocks[i].FieldID.Length();
			if(!Stream->Write(&Length, sizeof(unsigned long), 1))
			{
				return false;
			};

			if(Length)
			{
				if(!Stream->Write(Blocks[i].FieldID.Get(), 
					(Header.Unicode) ? (sizeof(wchar_t)) : (sizeof(char)), Length))
				{
					return false;
				};
			};

			Length = Blocks[i].Text.Length();
			if(!Stream->Write(&Length, sizeof(unsigned long), 1))
			{
				return false;
			};

			if(Length)
			{
				if(!Stream->Write(Blocks[i].Text.Get(), 
					(Header.Unicode) ? (sizeof(wchar_t)) : (sizeof(char)), Length))
				{
					return false;
				};
			};
		};
		return true;
	};

	bool ITranslationInfo::Deserialize(CStream Stream)
	{
		if(!Stream.Get())
			return false;
		TranslationHeader Header;
		if(!Stream->Read(&Header, sizeof(Header), 1))
		{
			return false;
		};

		if(Header.ID[0] != 'F' || Header.ID[1] != 'R' ||
			Header.ID[2] != 'T' || Header.Version != 1)
		{
			return false;
		};

		Blocks.Allocate(Header.BlockCount);
		for(unsigned long i = 0; i < Blocks.Size(); i++)
		{
			unsigned long Length = 0;
			if(!Stream->Read(&Length, sizeof(unsigned long), 1))
			{
				return false;
			};

			if(Length)
			{
				if(Header.Unicode)
				{
					Array<wchar_t> Temp(Length);
					if(!Stream->Read(Temp.Get(), sizeof(wchar_t), Length))
					{
						return false;
					};
#ifdef FRPLATFORM_UNICODE
					Blocks[i].FieldID = Temp.Get();
#else
					Blocks[i].FieldID = StringW(Temp.Get());
#endif
				}
				else
				{
					Array<char> Temp(Length);
					if(!Stream->Read(Temp.Get(), sizeof(char), Length))
					{
						return false;
					};
#ifndef FRPLATFORM_UNICODE
					Blocks[i].FieldID = Temp.Get();
#else
					Blocks[i].FieldID = StringA(Temp.Get());
#endif
				};
			};

			Length = Blocks[i].Text.Length();
			if(!Stream->Read(&Length, sizeof(unsigned long), 1))
			{
				return false;
			};

			if(Length)
			{
				if(Header.Unicode)
				{
					Array<wchar_t> Temp(Length);
					if(!Stream->Read(Temp.Get(), sizeof(wchar_t), Length))
					{
						return false;
					};
#ifdef FRPLATFORM_UNICODE
					Blocks[i].Text = Temp.Get();
#else
					Blocks[i].Text = StringW(Temp.Get());
#endif
				}
				else
				{
					Array<char> Temp(Length);
					if(!Stream->Read(Temp.Get(), sizeof(char), Length))
					{
						return false;
					};
#ifndef FRPLATFORM_UNICODE
					Blocks[i].Text = Temp.Get();
#else
					Blocks[i].Text = StringA(Temp.Get());
#endif
				};
			};
		};
		return true;
	};

	NativeString ITranslationInfo::FindBlock(NativeString FieldID)
	{
		for(unsigned long i = 0; i < Blocks.Size(); i++)
		{
			if(Blocks[i].FieldID.Find(FieldID) == 0)
			{
				return Blocks[i].Text;
			}
		};
		return NativeString();
	};

	ITranslationInfo::ITranslationBlock::ITranslationBlock()
	{
	}

	ITranslationInfo::ITranslationBlock::ITranslationBlock(NativeString FieldID, NativeString Text)
	{
		this->FieldID = FieldID;
		this->Text = Text;
	}
};
