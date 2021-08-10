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
	wprintf(L"Initializing Array Operator Test\n");
	Array<unsigned int> A(5), B(5), C;

	wprintf(L"A Size: %i\nMembers:\n", A.Size());

	for(unsigned long i = 0; i < A.Size(); i++)
	{
		A[i] = rand() % 1024;
		wprintf(L"Member %i: %i\n", i, A[i]);
	};

	wprintf(L"\n\nB Size: %i\nMembers:\n", B.Size());

	for(unsigned long i = 0; i < B.Size(); i++)
	{
		B[i] = rand() % 1024;
		wprintf(L"Member %i: %i\n", i, B[i]);
	};

	C = A + B;

	wprintf(L"\n\nC Size: %i\nMembers:\n", C.Size());

	for(unsigned long i = 0; i < C.Size(); i++)
	{
		wprintf(L"Member %i: %i\n", i, C[i]);
	};

	wprintf(L"Press any key to continue.");
	getchar();

	return 0;
};
