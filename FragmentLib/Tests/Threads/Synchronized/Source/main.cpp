#include <Fragment/Fragment.h>
using namespace Fragment;
#include <cstdio>
#include <cstdlib>
#ifdef FRPLATFORM_WINDOWS
#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

Mutex m;
Thread t1, t2;

#ifdef FRPLATFORM_WINDOWS
unsigned long Thread1Func(void* Object)
#else
void* Thread1Func(void* Object)
#endif
{
	while(true)
	{
		MutexLocker _m(m);
		printf("%i\n", 0);
	};
	return nullptr;
};

#ifdef FRPLATFORM_WINDOWS
unsigned long Thread2Func(void* Object)
#else
void* Thread2Func(void* Object)
#endif
{
	while(true)
	{
		MutexLocker _m(m);
		printf("%i\n", 1);
	};
	return nullptr;
};

int main(int argc, char **argv)
{
	CreateDefaultMemoryList();
	t1.Initialize(Thread1Func);
	t2.Initialize(Thread2Func);
#ifdef FRPLATFORM_WINDOWS
	Sleep(10000);
#else
#endif
	return 0;
};
