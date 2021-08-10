#include <Fragment/Fragment.h>
using namespace Fragment;
#include <stdlib.h>

extern "C" int __declspec(dllexport) Random(int min, int max)
{
	return (rand() % (max - min)) + min;
};
