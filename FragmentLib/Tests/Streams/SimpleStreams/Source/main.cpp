#include <Fragment/Fragment.h>
#include <stdlib.h>
#include <stdio.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

#define FILE

#ifdef MEMORY
#define StreamClass IMemoryStream
#elif defined(FILE)
#define StreamClass IStdioFileStream
#define INITIALIZE_STREAM_A ((IStdioFileStream*)Stream.Get())->Create(TONATIVETEXT("test.bin"), FRSA_WRITE);
#define INITIALIZE_STREAM_B ((IStdioFileStream*)Stream.Get())->Create(TONATIVETEXT("test.bin"), FRSA_READ);
#endif

CStream Stream;

int main(int argc, char **argv)
{
	printf("Initializing test.\n");
	CreateDefaultMemoryList();
	Stream.Swap(new StreamClass);
#ifdef INITIALIZE_STREAM_A
	INITIALIZE_STREAM_A
#endif
	printf("Trying to write the string 'banana': %s\n", 
		(Stream->Write("banana", sizeof(char), strlen("banana"))) ? ("OK") : ("FAILURE"));
	unsigned long i = 1234;
	printf("Trying to write the integer '1234': %s\n", 
		(Stream->Write(&i, sizeof(unsigned long), 1)) ? ("OK") : ("FAILURE"));
	Array<char> Data(Stream->Size());
	Stream->Seek();
#ifdef INITIALIZE_STREAM_B
	INITIALIZE_STREAM_B
#endif
	printf("Reading stream content: %s\n", 
		(Stream->Read(Data.Get(), sizeof(char), Data.Size())) ? ("OK") : ("FAILURE"));
	printf("Displaying content of Stream: '%s'\n", Data.Get());
	printf("End of test. Press any key to continue.\n");
	getchar();
	return 0;
};
