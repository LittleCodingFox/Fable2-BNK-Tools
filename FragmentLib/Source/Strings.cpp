#define _CRT_NON_CONFORMING_SWPRINTFS
#include <Fragment/Fragment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
namespace Fragment
{
	StringW::StringW()
	{
	};

	StringW::StringW(const StringA &String)
	{
		if(String.Length() > 0)
		{
			StringData.Allocate(String.StringData.Size());
#ifdef FRCOMPILER_MSVC
			size_t dummy;
			mbstowcs_s(&dummy, StringData.Get(), String.StringData.Size(), 
				String.StringData.Get(), StringData.Size());
#else
			mbstowcs(StringData.Get(), String.StringData.Get(), StringData.Size());
#endif
		};
	};

	StringW::StringW(const StringW &String)
	{
		this->StringData = String.StringData;
	};

	StringW::StringW(const wchar_t *String)
	{
		unsigned long Curr = 0;
		while(String[Curr] != L'\0')
		{
			Curr++;
		};

		if(Curr)
		{
			StringData.Allocate(Curr + 1);
			for(unsigned long i = 0; i < Curr; i++)
			{
				StringData[i] = String[i];
			};
			StringData[Curr] = L'\0';
		};
	};

	StringW::operator wchar_t*() const
	{
		return Get();
	};

	unsigned long StringW::Length() const
	{
		return (StringData.Size() > 0) ? (StringData.Size() - 1) : (0);
	};

	wchar_t &StringW::operator[](const unsigned long Index)
	{
		return Get()[Index];
	};

	const wchar_t &StringW::operator[](const unsigned long Index) const
	{
		return Get()[Index];
	};

	bool StringW::operator==(const StringW &String)
	{
		return PartialMatch(String);
	};

	bool StringW::operator==(const wchar_t *String)
	{
		return PartialMatch(StringW(String));
	};

	bool StringW::operator!=(const StringW &String)
	{
		return !PartialMatch(String);
	};

	bool StringW::operator!=(const wchar_t *String)
	{
		return !PartialMatch(StringW(String));
	};

	StringW& StringW::operator=(const StringW &o)
	{
		StringData.Clear();
		if(o.Length())
		{
			this->StringData = o.StringData;
		};
		return *this;
	};

	StringW& StringW::operator=(const StringA &o)
	{
		return *this = StringW(o);
	};

	StringW& StringW::operator=(const wchar_t *String)
	{
		StringData.Clear();
		unsigned long Curr = 0;
		while(String[Curr] != L'\0')
		{
			Curr++;
		};
		if(Curr)
		{
			StringData.Allocate(Curr + 1);
			for(unsigned long i = 0; i < Curr; i++)
			{
				StringData[i] = String[i];
			};
			StringData[Curr] = L'\0';
		};
		return *this;
	};

	StringW& StringW::operator=(float f)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%f", f);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(double d)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%lf", d);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(unsigned int i)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%u", i);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(unsigned long l)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%lu", l);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(unsigned long long ll)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%llu", ll);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(unsigned short s)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%u", s);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(int i)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%i", i);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(long l)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%l", l);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(long long ll)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%ll", ll);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(short s)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%i", s);
		return *this = StringW(Buffer.Get());
	};

	StringW& StringW::operator=(wchar_t w)
	{
		StringData.Allocate(2);
		StringData[0] = w;
		StringData.Last() = L'\0';
		return *this;
	};

	StringW StringW::operator+(const StringW &o)
	{
		StringW Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += o.StringData;
		return Str;
	};

	StringW StringW::operator+(const StringA &o)
	{
		StringW Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += StringW(o).StringData;
		return Str;
	};

	StringW StringW::operator+(const wchar_t *String)
	{
		StringW Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += StringW(String).StringData;
		return Str;
	};

	StringW StringW::operator+(float f)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%f", f);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(double d)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%lf", d);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(unsigned int i)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%u", i);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(unsigned long l)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%lu", l);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(unsigned long long ll)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%llu", ll);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(unsigned short s)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%u", s);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(int i)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%i", i);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(long l)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%li", l);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(long long ll)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%lli", ll);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(short s)
	{
		Array<wchar_t> Buffer(250);
		swprintf(Buffer.Get(), 250, L"%i", s);
		return *this + StringW(Buffer.Get());
	};

	StringW StringW::operator+(wchar_t w)
	{
		StringW Str = *this;
		Str.StringData.Last() = w;
		Str.StringData.New();
		Str.StringData.Last() = L'\0';
		return Str;
	};

	void StringW::operator+=(const StringW &o)
	{
		*this = *this + o;
	};

	void StringW::operator+=(const StringA &o)
	{
		*this = *this + o;
	};

	void StringW::operator+=(const wchar_t *String)
	{
		*this = *this + String;
	};

	void StringW::operator+=(float f)
	{
		*this = *this + f;
	};

	void StringW::operator+=(double d)
	{
		*this = *this + d;
	};

	void StringW::operator+=(unsigned int i)
	{
		*this = *this + i;
	};

	void StringW::operator+=(unsigned long l)
	{
		*this = *this + l;
	};

	void StringW::operator+=(unsigned long long ll)
	{
		*this = *this + ll;
	};

	void StringW::operator+=(unsigned short s)
	{
		*this = *this + s;
	};

	void StringW::operator+=(int i)
	{
		*this = *this + i;
	};

	void StringW::operator+=(long l)
	{
		*this = *this + l;
	};

	void StringW::operator+=(long long ll)
	{
		*this = *this + ll;
	};

	void StringW::operator+=(short s)
	{
		*this = *this + s;
	};

	void StringW::operator+=(wchar_t w)
	{
		*this = *this + w;
	};

	unsigned long StringW::Compare(StringW String)
	{
		unsigned long Count = 0;
		unsigned long To = Length();
		if(String.Length() > Length())
		{
			Count += String.Length() - Length();
		}
		else if(String.Length() < Length())
		{
			Count += Length() - String.Length();
			To = String.Length();
		};

		for(unsigned long i = 0; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				Count++;
			};
		};
		return Count;
	};

	unsigned long StringW::Compare(unsigned long From, unsigned long To, StringW String)
	{
		unsigned long Count = 0;
		if(String.Length() > To)
		{
			Count += String.Length() - To;
			To = Count;
		}
		else if(String.Length() < From)
		{
			Count += From - String.Length();
			To = Count;
		};

		if(To == From)
		{
			return 0;
		};

		for(unsigned long i = From; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				Count++;
			};
		};
		return Count;
	};

	bool StringW::PartialMatch(StringW String)
	{
		unsigned long To = Length();
		if(String.Length() > Length())
		{
			return false;
		}
		else if(String.Length() < Length())
		{
			return false;
		};

		for(unsigned long i = 0; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				return false;
			};
		};
		return true;
	};

	bool StringW::PartialMatch(unsigned long From, unsigned long To, StringW String)
	{
		if(To == From)
		{
			return true;
		};

		for(unsigned long i = From; i < To; i++)
		{
			if(StringData[i] != String.StringData[i - From])
			{
				return false;
			};
		};
		return true;
	};

	DynamicArray<StringW> StringW::Split(StringW Limits)
	{
		DynamicArray<StringW> Strings;
		if(Limits.Length() && Length())
		{
			unsigned long LastFind = 0;
			bool Found = false;
			for(unsigned long i = 0; i < Length(); i++)
			{
				for(unsigned long j = 0; j < Limits.Length(); j++)
				{
					if(Limits[j] == (*this)[i])
					{
						if(long(i) - long(LastFind) > 0)
						{
							Strings.New();
							Strings.Last() = (*this).Copy(LastFind, i);
							Found = true;
						};
						LastFind = i + 1;
					};
				};
				if(Found)
				{
					Found = false;
					continue;
				};
			};

			if(long(Length()) - long(LastFind) > 0)
			{			
				long Diff = long(Length()) - long(LastFind);
				if(Diff == 1)
				{
					for(unsigned long i = 0; i < Limits.Length(); i++)
					{
						if(StringData.Last() == Limits[i])
							return Strings;
					};
				}
				Strings.New();
				Strings.Last() = (*this).Copy(LastFind, Length());
			};

			if(Strings.Size() == 0)
			{
				Strings += (*this);
			};
			return Strings;
		};
		Strings.New();
		Strings.Last() = *this;
		return Strings;
	};

	StringW StringW::Copy(unsigned long From, unsigned long To)
	{
		if(From >= To || To > Length())
		{
			return StringW();
		};
		StringW Str;
		Str.StringData.Allocate((To - From) + 1);
		for(unsigned long i = 0; i < (To - From); i++)
		{
			Str.StringData[i] = StringData[From + i];
		};
		Str.StringData.Last() = L'\0';
		return Str;
	};

	long StringW::Find(wchar_t Character, bool Reverse_Search, unsigned long Start)
	{
		if(Reverse_Search)
		{
			for(unsigned long i = (Start == 0) ? (Length() - 1) : Start; i > 0; i--)
			{
				if(StringData[i] == Character)
				{
					return i;
				};
			};
		}
		else
		{
			for(unsigned long i = Start; i < Length(); i++)
			{
				if(StringData[i] == Character)
				{
					return i;
				};
			};
		};
		return -1;
	};

	long StringW::Find(StringW Str, bool Reverse_Search, unsigned long Start)
	{
		if(Reverse_Search)
		{
			for(long i = Start; (i = Find(Str[(unsigned long)0], true, i)) != -1 &&
				Length() - i >= Str.Length(); i++)
			{
				if(PartialMatch(i, i + Str.Length(), Str))
					return i;
			};
		}
		else
		{
			for(long i = Start; (i = Find(Str[(unsigned long)0], false, i)) != -1 &&
				Length() - i >= Str.Length(); i++)
			{
				if(PartialMatch(i, i + Str.Length(), Str))
					return i;
			};
		};
		return -1;
	};

	wchar_t *StringW::Get() const
	{
		return (StringData.Size() > 0) ? (StringData.Get()) : (nullptr);
	};

	StringA::StringA()
	{
	};

	StringA::StringA(const StringW &String)
	{
		if(String.Length() > 0)
		{
			StringData.Allocate(String.StringData.Size());
#ifdef FRCOMPILER_MSVC
			size_t dummy;
			wcstombs_s(&dummy, StringData.Get(), StringData.Size(), 
				String.StringData.Get(), StringData.Size());
#else
			wcstombs(StringData.Get(), String.StringData.Get(), StringData.Size());
#endif
		};
	};

	StringA::StringA(const StringA &String)
	{
		this->StringData = String.StringData;
	};

	StringA::StringA(const char *String)
	{
		unsigned long Curr = 0;
		while(String[Curr] != '\0')
		{
			Curr++;
		};

		if(Curr)
		{
			StringData.Allocate(Curr + 1);
			for(unsigned long i = 0; i < Curr; i++)
			{
				StringData[i] = String[i];
			};
			StringData[Curr] = '\0';
		};
	};

	StringA::operator char*() const
	{
		return Get();
	};

	unsigned long StringA::Length() const
	{
		return (StringData.Size() > 0) ? (StringData.Size() - 1) : (0);
	};

	char &StringA::operator[](const unsigned long Index)
	{
		return Get()[Index];
	};

	const char &StringA::operator[](const unsigned long Index) const
	{
		return Get()[Index];
	};

	bool StringA::operator==(const StringA &String)
	{
		return PartialMatch(String);
	};

	bool StringA::operator==(const char *String)
	{
		return PartialMatch(StringW(String));
	};

	bool StringA::operator!=(const StringA &String)
	{
		return !PartialMatch(String);
	};

	bool StringA::operator!=(const char *String)
	{
		return !PartialMatch(StringA(String));
	};

	StringA& StringA::operator=(const StringA &o)
	{
		StringData.Clear();
		if(o.Length())
		{
			this->StringData = o.StringData;
		};
		return *this;
	};


	StringA& StringA::operator=(const StringW &o)
	{
		StringData.Clear();
		if(o.Length())
		{
			this->StringData = StringA(o).StringData;
		};
		return *this;
	};

	StringA& StringA::operator=(const char *String)
	{
		StringData.Clear();
		unsigned long Curr = 0;
		while(String[Curr] != '\0')
		{
			Curr++;
		};
		if(Curr)
		{
			StringData.Allocate(Curr + 1);
			for(unsigned long i = 0; i < Curr; i++)
			{
				StringData[i] = String[i];
			};
			StringData[Curr] = '\0';
		};
		return *this;
	};

	StringA& StringA::operator=(float f)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%f", f);
#else
		sprintf(Buffer.Get(), "%f", f);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(double d)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lf", d);
#else
		sprintf(Buffer.Get(), "%lf", d);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(unsigned int i)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%u", i);
#else
		sprintf(Buffer.Get(), "%u", i);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(unsigned long l)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lu", l);
#else
		sprintf(Buffer.Get(), "%lu", l);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(unsigned long long ll)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%llu", ll);
#else
		sprintf(Buffer.Get(), "%llu", ll);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(unsigned short s)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%u", s);
#else
		sprintf(Buffer.Get(), "%u", s);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(int i)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%i", i);
#else
		sprintf(Buffer.Get(), "%i", i);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(long l)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%li", l);
#else
		sprintf(Buffer.Get(), "%li", l);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(long long ll)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lli", ll);
#else
		sprintf(Buffer.Get(), "%lli", ll);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(short s)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%i", s);
#else
		sprintf(Buffer.Get(), "%i", s);
#endif
		return *this = StringA(Buffer.Get());
	};

	StringA& StringA::operator=(char w)
	{
		StringData.Allocate(2);
		StringData[0] = w;
		StringData.Last() = '\0';
		return *this;
	};

	StringA StringA::operator+(const StringA &o)
	{
		StringA Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += o.StringData;
		return Str;
	};

	StringA StringA::operator+(const StringW &o)
	{
		StringA Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += StringA(o).StringData;
		return Str;
	};

	StringA StringA::operator+(const char *String)
	{
		StringA Str = *this;
		if(Str.StringData.Size())
		{
			Str.StringData.Resize(Str.StringData.Size() - 1);
		};
		Str.StringData += StringA(String).StringData;
		return Str;
	};

	StringA StringA::operator+(float f)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%f", f);
#else
		sprintf(Buffer.Get(), "%f", f);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(double d)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lf", d);
#else
		sprintf(Buffer.Get(), "%lf", d);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(unsigned int i)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%u", i);
#else
		sprintf(Buffer.Get(), "%u", i);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(unsigned long l)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lu", l);
#else
		sprintf(Buffer.Get(), "%lu", l);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(unsigned long long ll)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%llu", ll);
#else
		sprintf(Buffer.Get(), "%llu", ll);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(unsigned short s)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%u", s);
#else
		sprintf(Buffer.Get(), "%u", s);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(int i)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%i", i);
#else
		sprintf(Buffer.Get(), "%i", i);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(long l)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%li", l);
#else
		sprintf(Buffer.Get(), "%li", l);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(long long ll)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%lli", ll);
#else
		sprintf(Buffer.Get(), "%lli", ll);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(short s)
	{
		Array<char> Buffer(250);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "%i", s);
#else
		sprintf(Buffer.Get(), "%i", s);
#endif
		return *this + StringA(Buffer.Get());
	};

	StringA StringA::operator+(char w)
	{
		StringA Str = *this;
		Str.StringData.Last() = w;
		Str.StringData.New();
		Str.StringData.Last() = '\0';
		return Str;
	};

	void StringA::operator+=(const StringA &o)
	{
		*this = *this + o;
	};

	void StringA::operator+=(const StringW &o)
	{
		*this = *this + StringA(o);
	};

	void StringA::operator+=(const char *String)
	{
		*this = *this + String;
	};

	void StringA::operator+=(float f)
	{
		*this = *this + f;
	};

	void StringA::operator+=(double d)
	{
		*this = *this + d;
	};

	void StringA::operator+=(unsigned int i)
	{
		*this = *this + i;
	};

	void StringA::operator+=(unsigned long l)
	{
		*this = *this + l;
	};

	void StringA::operator+=(unsigned long long ll)
	{
		*this = *this + ll;
	};

	void StringA::operator+=(unsigned short s)
	{
		*this = *this + s;
	};

	void StringA::operator+=(int i)
	{
		*this = *this + i;
	};

	void StringA::operator+=(long l)
	{
		*this = *this + l;
	};

	void StringA::operator+=(long long ll)
	{
		*this = *this + ll;
	};

	void StringA::operator+=(short s)
	{
		*this = *this + s;
	};

	void StringA::operator+=(char w)
	{
		*this = *this + w;
	};

	unsigned long StringA::Compare(StringA String)
	{
		unsigned long Count = 0;
		unsigned long To = Length();
		if(String.Length() > Length())
		{
			Count += String.Length() - Length();
		}
		else if(String.Length() < Length())
		{
			Count += Length() - String.Length();
			To = String.Length();
		};

		for(unsigned long i = 0; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				Count++;
			};
		};
		return Count;
	};

	unsigned long StringA::Compare(unsigned long From, unsigned long To, StringA String)
	{
		unsigned long Count = 0;
		if(String.Length() > To)
		{
			Count += String.Length() - To;
			To = Count;
		}
		else if(String.Length() < From)
		{
			Count += From - String.Length();
			To = Count;
		};

		if(To == From)
		{
			return 0;
		};

		for(unsigned long i = From; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				Count++;
			};
		};
		return Count;
	};

	bool StringA::PartialMatch(StringA String)
	{
		unsigned long To = Length();
		if(String.Length() > Length())
		{
			return false;
		}
		else if(String.Length() < Length())
		{
			return false;
		};

		for(unsigned long i = 0; i < To; i++)
		{
			if(StringData[i] != String.StringData[i])
			{
				return false;
			};
		};
		return true;
	};

	bool StringA::PartialMatch(unsigned long From, unsigned long To, StringA String)
	{
		if(To == From)
		{
			return true;
		};

		for(unsigned long i = From; i < To; i++)
		{
			if(StringData[i] != String.StringData[i - From])
			{
				return false;
			};
		};
		return true;
	};

	DynamicArray<StringA> StringA::Split(StringA Limits)
	{
		DynamicArray<StringA> Strings;
		if(Limits.Length() && Length())
		{
			unsigned long LastFind = 0;
			bool Found = false;
			for(unsigned long i = 0; i < Length(); i++)
			{
				for(unsigned long j = 0; j < Limits.Length(); j++)
				{
					if(Limits[j] == (*this)[i])
					{
						if(long(i) - long(LastFind) > 0)
						{
							Strings.New();
							Strings.Last() = (*this).Copy(LastFind, i);
							Found = true;
						};
						LastFind = i + 1;
					};
				};
				if(Found)
				{
					Found = false;
					continue;
				};
			};

			if(long(Length()) - long(LastFind) > 0)
			{			
				long Diff = long(Length()) - long(LastFind);
				if(Diff == 1)
				{
					for(unsigned long i = 0; i < Limits.Length(); i++)
					{
						if(StringData.Last() == Limits[i])
							return Strings;
					};
				}
				Strings.New();
				Strings.Last() = (*this).Copy(LastFind, Length());
			};

			if(Strings.Size() == 0)
			{
				Strings += (*this);
			};
			return Strings;
		};
		Strings.New();
		Strings.Last() = *this;
		return Strings;
	};

	StringA StringA::Copy(unsigned long From, unsigned long To)
	{
		if(From >= To || To > Length())
		{
			return StringA();
		};
		StringA Str;
		Str.StringData.Allocate((To - From) + 1);
		for(unsigned long i = 0; i < (To - From); i++)
		{
			Str.StringData[i] = StringData[From + i];
		};
		Str.StringData.Last() = '\0';
		return Str;
	};

	long StringA::Find(char Character, bool Reverse_Search, unsigned long Start)
	{
		if(Reverse_Search)
		{
			for(unsigned long i = (Start == 0) ? (Length() - 1) : Start; i > 0; i--)
			{
				if(StringData[i] == Character)
				{
					return i;
				};
			};
		}
		else
		{
			for(unsigned long i = Start; i < Length(); i++)
			{
				if(StringData[i] == Character)
				{
					return i;
				};
			};
		};
		return -1;
	};

	long StringA::Find(StringA Str, bool Reverse_Search, unsigned long Start)
	{
		if(Reverse_Search)
		{
			for(long i = Start; (i = Find(Str[(unsigned long)0], true, i)) != -1 &&
				Length() - i >= Str.Length(); i++)
			{
				if(PartialMatch(i, i + Str.Length(), Str))
					return i;
			};
		}
		else
		{
			for(long i = Start; (i = Find(Str[(unsigned long)0], false, i)) != -1 &&
				Length() - i >= Str.Length(); i++)
			{
				if(PartialMatch(i, i + Str.Length(), Str))
					return i;
			};
		};
		return -1;
	};

	char *StringA::Get() const
	{
		return (StringData.Size() > 0) ? (StringData.Get()) : (nullptr);
	};

};
