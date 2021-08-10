#include <Fragment/Fragment.h>
using namespace Fragment;
#include <stdlib.h>
#include <stdio.h>
#include "BNKFile.h"
using namespace Fable2Mod;

StringA FileName;

int main(int argc, char **argv)
{
	CreateDefaultMemoryList();

	if(argc != 2)
	{
		printf("Usage: %s file\n", argv[0]);
		return 1;
	};

	FileName = argv[1];

	printf("Preparing to read Archive '%s'.\n", FileName.Get());

	CBNKArchive Archive(new IBNKArchive);
	CStdioFileStream Stream(new IStdioFileStream);

	if(!Stream->Create(FileName, FRSA_READ))
	{
		return 1;
	};

	bool OK = Archive->Scan(Stream.Handle());

	printf("Reading Archive '%s': %s\n", FileName.Get(), 
		(OK) ? ("Success") : ("Failure"));

	if(!OK)
		return 1;

	CStdioFileStream OutStream(new IStdioFileStream);

	if(!OutStream->Create(NativeText("files.txt"), FRSA_WRITE | FRSA_TEXT))
	{
		return 1;
	};

	if(Archive->Compressed())
	{
		NativeString Message;
		Message = Message + NativeString(NativeText("Uncompressed Archive '")) +
			FileName + NativeString(NativeText("'(")) +
			Archive->CompressedFileTable->Entries.Size() + 
			NativeString(NativeText(" Entries).\n\n"));
		OutStream->Write(Message.Get(), 1, Message.Length());

		for(unsigned long i = 0; i < Archive->CompressedFileTable->Entries.Size(); i++)
		{
			Message = NativeString();
			Message = Message + i + NativeString(NativeText(": ")) +
				Archive->CompressedFileTable->Entries[i]->FileName + NativeString(NativeText(" (")) +
				Archive->CompressedFileTable->Entries[i]->DecompressedSize + NativeString(NativeText(" bytes)\n"));
			OutStream->Write(Message.Get(), 1, Message.Length());
		};
	}
	else
	{
		NativeString Message;
		Message = Message + NativeString(NativeText("Uncompressed Archive '")) +
			FileName + NativeString(NativeText("'(")) +
			Archive->DecompressedFileTable->Entries.Size() + 
			NativeString(NativeText(" Entries).\n\n"));
		OutStream->Write(Message.Get(), 1, Message.Length());

		for(unsigned long i = 0; i < Archive->DecompressedFileTable->Entries.Size(); i++)
		{
			Message = NativeString();
			Message = Message + i + NativeString(NativeText(": ")) +
				Archive->DecompressedFileTable->Entries[i]->FileName + NativeString(NativeText(" (")) +
				Archive->DecompressedFileTable->Entries[i]->Size + NativeString(NativeText(" bytes)\n"));
			OutStream->Write(Message.Get(), 1, Message.Length());
		};
	};

	return 0;
};
