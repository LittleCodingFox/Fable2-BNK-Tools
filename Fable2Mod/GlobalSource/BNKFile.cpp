#include <Fragment/Fragment.h>
using namespace Fragment;
#include <zlib/zlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "Endian.h"
#include "BNKFile.h"
namespace Fable2Mod
{
	IBNKArchive::~IBNKArchive()
	{
		Header.Dispose();
		CompressedFileTable.Dispose();
		DecompressedFileTable.Dispose();
	};

	IBNKHeader::~IBNKHeader()
	{
		DecompressedTable.Dispose();
	};

	bool IBNKArchive::Scan(CStream Stream)
	{
		Header.Dispose();
		CompressedFileTable.Dispose();
		DecompressedFileTable.Dispose();
		Header.Swap(new IBNKHeader);
		SILENTFRASSERT(Header->DeSerialize(Stream));
		if(Compressed())
		{
			CompressedFileTable.Swap(new IBNKCompressedFileTable);
			SILENTFRASSERT(CompressedFileTable->DeSerialize(Header->DecompressedTable.Handle()));
		}
		else
		{
			DecompressedFileTable.Swap(new IBNKFileTable);
			SILENTFRASSERT(DecompressedFileTable->DeSerialize(Header->DecompressedTable.Handle()));
		};
		SourceStream = Stream;
		return true;
	};

	bool IBNKArchive::Compressed()
	{
		return (Header.Get()) ? (Header->CompressFileData == 1) : (false);
	};

#define READV(object, size, count)\
	if(!Stream->Read(&object, size, count))\
		return false;\
	EndianConvert(&object, size * count, true);

#define READVNE(object, size, count)\
	if(!Stream->Read(&object, size, count))\
		return false;

	bool IBNKHeader::DeSerialize(CStream Stream)
	{
		unsigned long CompressedSize = 0, DecompressedSize = 0;
		z_stream ZStream;
		DecompressedTable.Dispose();
		DecompressedTable.Swap(new IMemoryStream);

		Stream->Seek(0);
		READV(Offset, sizeof(unsigned long), 1);
		READV(Unknown, sizeof(char), 4);
		READV(CompressFileData, sizeof(unsigned char), 1);

		READV(CompressedSize, sizeof(unsigned long), 1);
		READV(DecompressedSize, sizeof(unsigned long), 1);

		memset(&ZStream, 0, sizeof(z_stream));
		inflateInit(&ZStream);

		while(CompressedSize)
		{
			Array<unsigned char> DecompressedData(DecompressedSize);
			Array<unsigned char> CompressedData(CompressedSize);
			READVNE(CompressedData[0], sizeof(unsigned char), CompressedSize);

			ZStream.next_in = (Bytef *) CompressedData.Get();
			ZStream.next_out = (Bytef *)DecompressedData.Get();
			ZStream.avail_in = CompressedSize;
			ZStream.avail_out = DecompressedSize;
			if(inflate(&ZStream, Z_SYNC_FLUSH))
			{
				inflateEnd(&ZStream);
				FRASSERT(0, "Failed to inflate ZStream");
			};

			DecompressedTable->Write(DecompressedData.Get(), sizeof(unsigned char), 
				DecompressedData.Size());

			READV(CompressedSize, sizeof(unsigned long), 1);
			READV(DecompressedSize, sizeof(unsigned long), 1);
		};
		inflateEnd(&ZStream);
		DecompressedTable->Seek(0);
		return true;
	};

	bool IBNKFileTable::DeSerialize(CStream Stream)
	{
		unsigned long FileCount = 0;
		READV(FileCount, sizeof(unsigned long), 1);
		for(unsigned long i = 0; i < FileCount; i++)
		{
			Entries += CBNKFileEntry(new IBNKFileEntry);
			if(!Entries.Last()->DeSerialize(Stream.Handle()))
			{
				return false;
			};
		};
		return true;
	};

	bool IBNKFileEntry::DeSerialize(CStream Stream)
	{
		unsigned long NameSize = 0;
		READV(NameSize, sizeof(unsigned long), 1);
		Array<char> Temp(NameSize);
		READVNE(Temp[0], sizeof(char), NameSize);
		FileName = Temp.Get();
		READV(Offset, sizeof(unsigned long), 1);
		READV(Size, sizeof(unsigned long), 1);
		return true;
	};

	bool IBNKCompressedFileTable::DeSerialize(CStream Stream)
	{
		unsigned long FileCount = 0;
		READV(FileCount, sizeof(unsigned long), 1);
		for(unsigned long i = 0; i < FileCount; i++)
		{
			Entries += CBNKCompressedFileEntry(new IBNKCompressedFileEntry);
			if(!Entries.Last()->DeSerialize(Stream))
			{
				return false;
			};
		};
		return true;
	};

	bool IBNKCompressedFileEntry::DeSerialize(CStream Stream)
	{
		unsigned long NameSize = 0;
		READV(NameSize, sizeof(unsigned long), 1);
		Array<char> Temp(NameSize);
		READVNE(Temp[0], sizeof(char), NameSize);
		FileName = Temp.Get();
		READV(Offset, sizeof(unsigned long), 1);
		READV(DecompressedSize, sizeof(unsigned long), 1);
		READV(CompressedSize, sizeof(unsigned long), 1);
		unsigned long DecompressedCount = 0;
		READV(DecompressedCount, sizeof(unsigned long), 1);
		DecompressedSizes.Allocate(DecompressedCount);
		for(unsigned long i = 0; i < DecompressedSizes.Size(); i++)
		{
			unsigned long Size = 0;
			READV(Size, sizeof(unsigned long), 1);
			DecompressedSizes[i] = Size;
		};
		return true;
	};

	CMemoryStream IBNKArchive::Fetch(StringA FileName)
	{
		if(!SourceStream.Get())
			return CMemoryStream();

		if(Compressed())
		{
			for(unsigned long i = 0; i < CompressedFileTable->Entries.Size(); i++)
			{
				if(CompressedFileTable->Entries[i]->FileName.PartialMatch(FileName))
				{
					CMemoryStream Stream(new IMemoryStream);
					CBNKCompressedFileEntry &Entry = CompressedFileTable->Entries[i];
					Array<unsigned char> CompressedData(Entry->
						CompressedSize);
					SourceStream->Seek(Entry->Offset + 
						Header->Offset);
					SourceStream->Read(CompressedData.Get(), sizeof(unsigned char), 
						CompressedData.Size());
					for(unsigned long i = 0; i < Entry->DecompressedSizes.Size(); i++)
					{
						z_stream ZStream;
						Array<unsigned char> Data(Entry->DecompressedSizes[i]);
						memset(&ZStream, 0, sizeof(z_stream));
						inflateInit(&ZStream);
						ZStream.next_out = Data.Get();
						ZStream.next_in = CompressedData.Get() + i * 0x8000;
						ZStream.avail_in = (CompressedData.Size() - i * 0x8000 > 0x8000) ? 
							(0x8000) : (CompressedData.Size() - i * 0x8000);
						ZStream.avail_out = Data.Size();
						if(inflate(&ZStream, Z_SYNC_FLUSH))
						{
							inflateEnd(&ZStream);
							FRASSERT(0, "Failed to inflate ZStream");
						};
						Stream->Write(Data.Get(), sizeof(unsigned char), Data.Size());
						Stream->Seek();
					};
					return Stream;
				};
			};
		}
		else
		{
			for(unsigned long i = 0; i < DecompressedFileTable->Entries.Size(); i++)
			{
				if(DecompressedFileTable->Entries[i]->FileName.PartialMatch(FileName))
				{
					CMemoryStream Stream(new IMemoryStream);
					CBNKFileEntry &Entry = DecompressedFileTable->Entries[i];
					Array<unsigned char> Data(Entry->Size);
					SourceStream->Seek(Entry->Offset + Header->Offset);
					SourceStream->Read(Data.Get(), sizeof(unsigned char), Data.Size());
					Stream->Write(Data.Get(), sizeof(unsigned char), Data.Size());
					return Stream;
				};
			};
		};
		return CMemoryStream();
	};

	Array<StringA> IBNKArchive::FileNames()
	{
		if(!SourceStream.Get())
			return Array<StringA>();

		Array<StringA> Names;
		if(Compressed())
		{
			Names.Allocate(CompressedFileTable->Entries.Size());
			for(unsigned long i = 0; i < CompressedFileTable->Entries.Size(); i++)
			{
				Names[i] = CompressedFileTable->Entries[i]->FileName;
			};
			return Names;
		}
		else
		{
			Names.Allocate(DecompressedFileTable->Entries.Size());
			for(unsigned long i = 0; i < DecompressedFileTable->Entries.Size(); i++)
			{
				Names[i] = DecompressedFileTable->Entries[i]->FileName;
			};
			return Names;
		};
	};
};
