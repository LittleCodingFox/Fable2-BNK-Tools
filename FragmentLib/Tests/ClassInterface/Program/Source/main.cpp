#include <Fragment/Fragment.h>
using namespace Fragment;
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

//Declare class
FRAGMENTLIB_DECLARE_CLASS_INTERFACE(Randomizer)
FRAGMENTLIB_DECLARE_CLASS_INTERFACE_FUNCTION(int, Random, (int min, int max))
FRAGMENTLIB_COMPLETE_CLASS_INTERFACE_DECLARATION()
//Implement class function Random
FRAGMENTLIB_IMPLEMENT_CLASS_INTERFACE_FUNCTION(Randomizer, int, Random, 
											   Random, (int min, int max), (min, max))
//Link Class (Create instances and fix link references)
FRAGMENTLIB_LINK_CLASS_INTERFACE(Randomizer)
//Generate constructors and destructors
FRAGMENTLIB_START_CLASS_INTERFACE_INITIALIZER_GENERATION(Randomizer)
//Initialize the function (random)
FRAGMENTLIB_INITIALIZE_CLASS_INTERFACE_METHOD(Random)
//Complete constructor and destructor generation
FRAGMENTLIB_COMPLETE_CLASS_INTERFACE_INITIALIZER_GENERATION(Randomizer, "DLL.dll")

int main(int argc, char** argv)
{
	printf("10 random numbers...\n");
	for(unsigned long i = 0; i < 10; i++)
	{
		printf("%i\n", Randomizer::Random(0, 10));
	};
	system("PAUSE");
	return 0;
};
