#include <Fragment/Fragment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
namespace Fragment
{
	IMemoryStream::IMemoryStream()
	{
		StreamSize = ReadPos = 0;
	};

	bool IMemoryStream::Read(void* Object, unsigned long long SizePerObject,
			unsigned long long TotalObjects)
	{
		MutexLocker m(StreamMutex);
		FRASSERT(Object, "Invalid Object!");
		FRASSERT(SizePerObject * TotalObjects, "Invalid ammount of bytes to read!");
		if(ReadPos + SizePerObject * TotalObjects > StreamSize)
		{
			return false;
		};
		memcpy(Object, &Data[(unsigned long)ReadPos], (unsigned long)(SizePerObject * TotalObjects));
		ReadPos += SizePerObject * TotalObjects;
		return true;
	};

	bool IMemoryStream::Write(const void* Object, unsigned long long SizePerObject,
			unsigned long long TotalObjects)
	{
		MutexLocker m(StreamMutex);
		FRASSERT(Object, "Invalid Object!");
		FRASSERT(SizePerObject * TotalObjects, "Invalid ammount of bytes to read!");
		Data.Resize(Data.Size() + (unsigned long)(SizePerObject * TotalObjects));
		memcpy(&Data[Data.Size() - (unsigned long)(SizePerObject * TotalObjects)], Object,
			(unsigned long)(SizePerObject * TotalObjects));
		StreamSize += SizePerObject * TotalObjects;
		return true;
	};

	unsigned long long IMemoryStream::Size()
	{
		return StreamSize;
	};

	unsigned long long IMemoryStream::Position()
	{
		return ReadPos;
	};

	bool IMemoryStream::Seek(unsigned long long Position)
	{
		MutexLocker m(StreamMutex);
		if(Position > StreamSize)
		{
			return false;
		};
		ReadPos = Position;
		return true;
	};

	void* IMemoryStream::Get()
	{
		return (Data.Size()) ? (Data.Get()) : (nullptr);
	};

	IStdioFileStream::IStdioFileStream()
	{
		FileHandle = nullptr;
		FileSize = ReadPos = 0;
	};

	IStdioFileStream::~IStdioFileStream()
	{
		Destroy();
	};

	void IStdioFileStream::Destroy()
	{
		if(FileHandle)
		{
			fclose((FILE*)FileHandle);
		};
		FileSize = ReadPos = 0;
		OpenMode = 0;
	};

	bool IStdioFileStream::Create(NativeString FileName, unsigned int OpenMode)
	{
		MutexLocker m(StreamMutex);
		Destroy();

		char OpenModeStr[4] = { '\0', '\0', '\0', '\0' };

		unsigned char CurrID = 0;
		bool Binary = true;

		if(OpenMode & FRSA_WRITE)
		{
			OpenModeStr[CurrID++] = 'w';
			if(OpenMode & FRSA_TEXT)
			{
				Binary = false;
			};
		}
		else if(OpenMode & FRSA_READ)
		{
			OpenModeStr[CurrID++] = 'r';
		};

		if(Binary)
		{
			OpenModeStr[CurrID++] = 'b';
		}
		else
		{
			OpenModeStr[CurrID++] = 't';
		};

#ifdef FRCOMPILER_MSVC
		fopen_s((FILE**)&FileHandle, StringA(FileName), OpenModeStr);
#else
		FileHandle = fopen(StringA(FileName), OpenModeStr);
#endif

		if(!FileHandle)
		{
			return false;
		};

		if(OpenMode & FRSA_READ)
		{
		    #ifdef FRCOMPILER_MSVC
			_fseeki64((FILE*)FileHandle, 0, SEEK_END);
			FileSize = _ftelli64((FILE*)FileHandle);
		    #else
			fseek((FILE*)FileHandle, 0, SEEK_END);
			FileSize = ftell((FILE*)FileHandle);
		    #endif

		    #ifdef FRCOMPILER_MSVC
			_fseeki64((FILE*)FileHandle, 0, SEEK_SET);
		    #else
			fseek((FILE*)FileHandle, 0, SEEK_SET);
		    #endif
		};

		this->OpenMode = OpenMode;

		return true;
	};

	bool IStdioFileStream::Read(void* Object, unsigned long long SizePerObject,
			unsigned long long TotalObjects)
	{
		MutexLocker m(StreamMutex);
		FRASSERT(Object, "Invalid Object!");
		FRASSERT(SizePerObject * TotalObjects, "Invalid ammount of bytes to read!");
		FRASSERT(OpenMode & FRSA_READ,
			"Invalid File Stream Opening Type - No READ flag passed");
		if(ReadPos + SizePerObject * TotalObjects > FileSize)
		{
#ifdef _DEBUG
			FRASSERT(0, StringA("Failed to read object at position '") + 
				ReadPos + StringA("' of size '") + SizePerObject * TotalObjects + 
				StringA("'"));
#endif
			return false;
		};

		unsigned long long ReadDataCount = 0;

		if(TotalObjects != (ReadDataCount = (unsigned long)
			fread(Object, (unsigned long)SizePerObject, (unsigned long)TotalObjects,
			(FILE*)FileHandle)))
		{
#ifdef _DEBUG
			FRASSERT(0, StringA("Failed to read object at position '") + 
				ReadPos + StringA("' of size '") + SizePerObject * TotalObjects + 
				StringA("'"));
#endif
			return false;
		};

		ReadPos += SizePerObject * TotalObjects;
		return true;
	};

	bool IStdioFileStream::Write(const void* Object, unsigned long long SizePerObject,
			unsigned long long TotalObjects)
	{
		MutexLocker m(StreamMutex);
		FRASSERT(Object, "Invalid Object!");
		if(OpenMode & FRSA_TEXT)
		{
			FRASSERT(TotalObjects, "Invalid ammount of characters to write");
		}
		else FRASSERT(SizePerObject * TotalObjects, "Invalid ammount of bytes to write!");
		FRASSERT(OpenMode & FRSA_WRITE,
			"Invalid File Stream Opening Type - No FRSA_WRITE flag passed");

		if(OpenMode & FRSA_TEXT)
		{
			char* Self = (char*)Object;
			for(unsigned long i = 0; i < TotalObjects; i++)
			{
				fputc(Self[i], (FILE*)FileHandle);
				if(ferror((FILE*)FileHandle))
				{
#ifdef _DEBUG
				FRASSERT(0, StringA("Failed to write object at position '") + 
					FileSize + StringA("' with character count of '") + TotalObjects + 
					StringA("' (last write at position '") + (FileSize + i) + StringA("')"));
#endif
					return false;
				};
			};
			fflush((FILE*)FileHandle);
			FileSize += TotalObjects;
		}
		else
		{
			if(fwrite(Object, (unsigned long)SizePerObject, (unsigned long)TotalObjects,
				(FILE*)FileHandle) != (unsigned long)TotalObjects)
			{
#ifdef _DEBUG
				FRASSERT(0, StringA("Failed to write object at position '") + 
					FileSize + StringA("' of size '") + SizePerObject * TotalObjects + 
					StringA("'"));
#endif
				return false;
			};
			fflush((FILE*)FileHandle);
			FileSize += SizePerObject * TotalObjects;
		};
		return true;
	};

	bool IStdioFileStream::Seek(unsigned long long Position)
	{
		MutexLocker m(StreamMutex);
		if(Position > FileSize)
		{
			return false;
		};
		FRASSERT(FileHandle, "Invalid FileHandle! Did you use Seek() without loading a file first?");
		#ifdef FRCOMPILER_MSVC
		if(_fseeki64((FILE*)FileHandle, Position, SEEK_SET))
		#else
		if(fseek((FILE*)FileHandle, Position, SEEK_SET))
		#endif
		{
			return false;
		};
		ReadPos = Position;
		return true;
	};

	unsigned long long IStdioFileStream::Size()
	{
		return FileSize;
	};

	unsigned long long IStdioFileStream::Position()
	{
		return (OpenMode & FRSA_WRITE) ? (FileSize) : (ReadPos);
	};
};
