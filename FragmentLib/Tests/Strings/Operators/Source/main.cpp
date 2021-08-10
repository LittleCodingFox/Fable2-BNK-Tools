#include <Fragment/Fragment.h>
#include <stdio.h>
#include <stdlib.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

int main(int argc, char **argv)
{
	unsigned long ULNumber = 100;

	float FNumber = 10.0f;
#ifndef NO_UNICODE_TEST
	wchar_t* Word = L"Test";

	StringW Base;

	wprintf(L"Starting Unicode (UTF-16) String Operator Test\n");

	wprintf(L"Unsigned Long Number: %i; Float Number: %f; String: '%s'\n", ULNumber,
		FNumber, Word);

	wprintf(L"Testing Operator+:\n");

	Base = Base + ULNumber;

	wprintf(L"\tULNumber: '%s'\n", Base.Get());

	Base = StringW() + FNumber;

	wprintf(L"\tFNumber: '%s'\n", Base.Get());

	Base = StringW() + Word;

	wprintf(L"\tWord: '%s'\n", Base.Get());

	wprintf(L"End of Unicode (UTF-16) String Operator Test\n");

#else
#endif

	wprintf(L"Press any key to continue.");
	getchar();

	return 0;
};
