#include <Fragment/Fragment.h>
#include <stdlib.h>
#include <stdio.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

int main(int argc, char **argv)
{
#ifndef NO_TEST_UNICODE
	wprintf(L"Begin Unicode (UTF-16) String Test\n");

	StringW WString(L"Tigah. Tigah tigah tigah.\nBird. Birdy. Birdy-Birdy.\n"
		L"I am a great magician! Your clothes are RED!");

	wprintf(L"Original String: '%s'\n", WString.Get());

	DynamicArray<StringW> WStrings = WString.Split(L" \n.,");

	wprintf(L"Total Substrings: %i\n", WStrings.Size());

	for(unsigned long i = 0; i < WStrings.Size(); i++)
	{
		wprintf(L"String %i: '%s'\n", i, WStrings[i].Get());
	};

	wprintf(L"End Unicode (UTF-16) String Test\n");
#endif

	printf("Begin ANSI String Test\n");

	StringA AString("Tigah. Tigah tigah tigah.\nBird. Birdy. Birdy-Birdy.\n"
		"I am a great magician! Your clothes are RED!");

	printf("Original String: '%s'\n", AString.Get());

	DynamicArray<StringA> AStrings = AString.Split(" \n.,");

	printf("Total Substrings: %i\n", AStrings.Size());

	for(unsigned long i = 0; i < AStrings.Size(); i++)
	{
		printf("String %i: '%s'\n", i, AStrings[i].Get());
	};

	printf("End ANSI String Test\n");

	printf("Press any key to continue.");
	getchar();

	return 0;
};
