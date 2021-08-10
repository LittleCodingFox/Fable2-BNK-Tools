#include <Fragment/Fragment.h>
#include <stdlib.h>
#include <stdio.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

CStdioFileStream Stream;

#ifdef FRPLATFORM_UNICODE
#define printfunc wprintf
#else
#define printfunc printf
#endif

int main(int argc, char **argv)
{
	printfunc(TONATIVETEXT("Initializing test.\n"));
	CreateDefaultMemoryList();
	Stream.Swap(new IStdioFileStream);

	printfunc(TONATIVETEXT("Initialzing text-based sample.\n"));
	Stream->Create(TONATIVETEXT("out.txt"), FRSA_WRITE | FRSA_TEXT);

	NativeString Str = NativeString() + vec3(1, 2, 3);
	printfunc(TONATIVETEXT("vec3: %s\n"), Str.Get());

	printfunc(TONATIVETEXT("Writing vec3\n"));
	Stream->Write(Str.Get(), 
		1,
		Str.Length());

	printfunc(TONATIVETEXT("Reading vec3\n"));
	Stream->Create(TONATIVETEXT("out.txt"), FRSA_READ | FRSA_TEXT);
	Stream->Seek();
#ifdef FRPLATFORM_UNICODE
	Array<wchar_t> Text(Str.Length());
#else
	Array<char> Text(Str.Length());
#endif
	Stream->Read(Text.Get(), 
		1, 
		Text.Size());
	Str = Text.Get();
	printfunc(TONATIVETEXT("vec3: %s\n"), Str.Get());
	
	printfunc(TONATIVETEXT("End of text-based sample.\n"));
	
	printfunc(TONATIVETEXT("Starting binary-based sample.\n"));
	Stream->Create(TONATIVETEXT("out.bin"), FRSA_WRITE);
	
	vec3 Source(2, 3, 4);
	printfunc(TONATIVETEXT("vec3: (%f, %f, %f)\n"), Source.x, Source.y, Source.z);
	
	printfunc(TONATIVETEXT("Writing vec3\n"));
	Stream->Write(&Source, sizeof(vec3), 1);

	printfunc(TONATIVETEXT("Reading vec3\n"));
	Source = vec3(0, 0, 0);
	printfunc(TONATIVETEXT("Current vec3: (%f, %f, %f)\n"), Source.x, Source.y, Source.z);
	Stream->Create(TONATIVETEXT("out.bin"), FRSA_READ);
	Stream->Read(&Source, sizeof(vec3), 1);
	printfunc(TONATIVETEXT("vec3: (%f, %f, %f)\n"), Source.x, Source.y, Source.z);
	printfunc(TONATIVETEXT("End of test. Press any key to continue.\n"));
	getchar();
	return 0;
};
