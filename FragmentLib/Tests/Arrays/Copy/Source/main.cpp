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
	wprintf(L"Initializing Array Copy Test\n");

	Array<unsigned long> Numbers(10);

	wprintf(L"Numbers:\n");
	for(unsigned long i = 0; i < Numbers.Size(); i++)
	{
		wprintf(L"%i%s", i, (i % 5 == 0) ? (L"\n") : (L" "));
		Numbers[i] = i;
	};

	wprintf(L"\n\nCopying Half the Array.\n\n");

	Array<unsigned long> HalfNumbers = Numbers.Copy(5, Numbers.Size());

	wprintf(L"Half Numbers:\n");
	for(unsigned long i = 0; i < HalfNumbers.Size(); i++)
	{
		wprintf(L"%i ", HalfNumbers[i]);
	};
	wprintf(L"\n");

	wprintf(L"Move member 2 to 3:\n\n");

	HalfNumbers.Move(2, 3);

	wprintf(L"Half Numbers:\n");
	for(unsigned long i = 0; i < HalfNumbers.Size(); i++)
	{
		wprintf(L"%i ", HalfNumbers[i]);
	};
	wprintf(L"\n");

	wprintf(L"Move member 4 to 2:\n\n");

	HalfNumbers.Move(4, 2);

	wprintf(L"Half Numbers:\n");
	for(unsigned long i = 0; i < HalfNumbers.Size(); i++)
	{
		wprintf(L"%i ", HalfNumbers[i]);
	};
	wprintf(L"\n");

	wprintf(L"End of all tests.\n");

	wprintf(L"Press any key to continue.");
	getchar();

	return 0;
};
