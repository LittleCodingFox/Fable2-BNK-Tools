#include <Fragment/Fragment.h>
#include <stdio.h>
#include <stdlib.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

short SearchFunction(unsigned long *t, void* Object)
{
	if(*t < *(unsigned long*)Object)
		return -1;
	else if(*t > *(unsigned long*)Object)
		return 1;
	return 0;
};

int main(int argc, char **argv)
{
	wprintf(L"Initializing Array Binary Search Test\n");

	Array<unsigned long> Data(4);

	for(unsigned long i = 0; i < Data.Size(); i++)
	{
		Data[i] = i;
	};

	unsigned long Value = 3;

	wprintf(L"%i is located in element %i\n", Value, Data.BinarySearch(SearchFunction, &Value));

	wprintf(L"Press any key to continue.");
	getchar();
	return 0;
};
