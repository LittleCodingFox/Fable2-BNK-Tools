#include <Fragment/Fragment.h>
using namespace Fragment;
#include "Endian.h"
namespace Fable2Mod
{
	int IsBigEndian = -1;
	void EndianInit()
	{
		short int word = 0x0001;
		char *byte = (char *) &word;
		IsBigEndian = (byte[0]) ? (0) : (1);
	}

	void EndianConvert(void *Data, unsigned int Size, bool Reverse)
	{
		unsigned char *RealData = (unsigned char*)Data;
		if(IsBigEndian == -1)
			EndianInit();
		if(IsBigEndian == !Reverse)
		{
			register int i = 0;
			register int j = Size-1;
			unsigned char Tmp;
			while (i<j)
			{
				Tmp = RealData[i];
				RealData[i] = RealData[j];
				RealData[j] = Tmp;
				i++, j--;
			}
		};
	}
};
