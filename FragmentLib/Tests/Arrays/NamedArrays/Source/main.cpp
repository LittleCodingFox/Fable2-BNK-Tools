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
	wprintf(L"Feeding NamedArrayA data.\n");

	NamedArrayA<StringA> StringsA;
	StringsA["legs"] = "pants";
	StringsA["head"] = "hat";
	StringsA["chest"] = "shirt";

	wprintf(L"Should print 'pants', 'hat', 'shirt'.\nUnnamed:\n\n");

	for(unsigned long i = 0; i < StringsA.Size(); i++)
	{
		printf("%s\n", StringsA[i].Get());
	};

	wprintf(L"\nNamed:\n\n");

	printf("%s\n", StringsA["legs"].Get());
	printf("%s\n", StringsA["head"].Get());
	printf("%s\n", StringsA["chest"].Get());

	wprintf(L"\nFeeding NamedArrayW data.\n");

	NamedArrayW<StringW> StringsW;
	StringsW[L"food"] = L"Sandwich";
	StringsW[L"game"] = L"Monopoly";
	StringsW[L"friend"] = L"Neighbour";

	wprintf(L"Should print 'Sandwich', 'Monopoly', 'Neighbour'.\nUnnamed:\n\n");

	for(unsigned long i = 0; i < StringsW.Size(); i++)
	{
		wprintf(L"%s\n", StringsW[i].Get());
	};

	wprintf(L"\nNamed:\n\n");

	wprintf(L"%s\n", StringsW[L"food"].Get());
	wprintf(L"%s\n", StringsW[L"game"].Get());
	wprintf(L"%s\n", StringsW[L"friend"].Get());

	wprintf(L"\nEnd of all tests.\nPress any key to continue.\n");
	getchar();

	return 0;
};
