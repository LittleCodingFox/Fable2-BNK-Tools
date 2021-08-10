#include <Fragment/Fragment.h>
using namespace Fragment;
#include "BNKFile.h"
using namespace Fable2Mod;
#include <stdlib.h>
#include <stdio.h>
#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Usage: %s archivename\n", argv[0]);
		return 1;
	};

	CreateDefaultMemoryList();
	CBNKArchive Archive(new IBNKArchive);
	CStdioFileStream Stream(new IStdioFileStream);

	printf("Reading '%s'.\n", argv[1]);
	if(!Stream->Create(StringA(argv[1]), FRSA_READ) || !Archive->Scan(Stream.Handle()))
	{
		printf("Failed. Aborting...\n");
		return 1;
	};

	Array<StringA> Names = Archive->FileNames();
	StringA RootDirectory = StringA(argv[1]).Split(".")[0];

	printf("Preparing to dump %i files.\n", Names.Size());

	CreateDirectory(NativeString(RootDirectory), nullptr);

	printf("Creating Directories...\n");
	for(unsigned long i = 0; i < Names.Size(); i++)
	{
		StringA CurrentDirectory = RootDirectory;
		DynamicArray<StringA> Pieces = Names[i].Split("\\/");
		for(unsigned long j = 0; j < Pieces.Size() - 1; j++)
		{
			CurrentDirectory += StringA("\\") + Pieces[j];
			CreateDirectory(NativeString(CurrentDirectory), nullptr);
		};
	};

	printf("Dumping files...\n");

	for(unsigned long i = 0; i < Names.Size(); i++)
	{
		StringA FileName = RootDirectory + StringA("\\") + Names[i];
		printf("Dumping file %i of %i ('%s')...", i + 1, Names.Size(), Names[i].Get());
		CSStdioFileStream OutStream(new IStdioFileStream);
		if(OutStream->Create(FileName, FRSA_WRITE))
		{
			CSMemoryStream InStream = Archive->Fetch(Names[i]).Handle();
			Array<unsigned char> Data(InStream->Size());
			InStream->Read(Data.Get(), sizeof(unsigned char), Data.Size());
			OutStream->Write(Data.Get(), sizeof(unsigned char), Data.Size());
			printf("Success.\n");
		}
		else
		{
			printf("Failed.\n");
		};
	};

	printf("Completed file dump.\n");
	return 0;
};
