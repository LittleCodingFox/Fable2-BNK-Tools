#ifndef FABLE2MOD_BNKFILE_H
#define FABLE2MOD_BNKFILE_H
namespace Fable2Mod
{
	class IBNKHeader : public IUnknown
	{
	public:
		~IBNKHeader();
		unsigned long Offset;
		char Unknown[4]; //Probably Version
		unsigned char CompressFileData; //I'm pretty sure this is a bool for compressing the file data
		unsigned long CompressedTableSize;
		unsigned long DecompressedTableSize;
		CMemoryStream DecompressedTable;
		bool DeSerialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKHeader);

	class IBNKFileEntry : public IUnknown
	{
	public:
		StringA FileName;
		unsigned long Offset;
		unsigned long Size;
		bool DeSerialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKFileEntry);

	class IBNKCompressedFileEntry : public IUnknown
	{
	public:
		StringA FileName;
		unsigned long Offset;
		unsigned long DecompressedSize;
		unsigned long CompressedSize;
		Array<unsigned long> DecompressedSizes;
		bool DeSerialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKCompressedFileEntry);

	class IBNKFileTable : public IUnknown
	{
	public:
		DynamicArray<CBNKFileEntry> Entries;
		bool DeSerialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKFileTable);

	class IBNKCompressedFileTable : public IUnknown
	{
	public:
		DynamicArray<CBNKCompressedFileEntry> Entries;
		bool DeSerialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKCompressedFileTable);

	class IBNKArchive : public IUnknown
	{
	public:
		CBNKHeader Header;
		CBNKFileTable DecompressedFileTable;
		CBNKCompressedFileTable CompressedFileTable;
		CStream SourceStream;
		~IBNKArchive();
		bool Scan(CStream Stream);
		Array<StringA> FileNames();
		CMemoryStream Fetch(StringA Name);
		bool Compressed();
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(BNKArchive);
};
#endif
