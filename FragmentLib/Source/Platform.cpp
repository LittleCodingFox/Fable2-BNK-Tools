#include <Fragment/Fragment.h>
#include <stdio.h>
#include <string.h>
namespace Fragment
{
	void LibWarning(const char* Description, unsigned int Line, const char* FileName,
		const char* Function, const char* Variable)
	{
		Array<char> Buffer(8192);
#ifdef FRCOMPILER_MSVC
		sprintf_s(Buffer.Get(), Buffer.Size(), "Assertion failed on '%s' @ '%s:%s:%i' ('%s')",
			Variable, Function, FileName, Line, Description);
#else
		sprintf(Buffer.Get(), "Assertion failed on '%s' @ '%s:%s:%i' ('%s')",
			Variable, Function, FileName, Line, Description);
#endif
		StringA RealBuffer = Buffer.Get();
#ifdef FRPLATFORM_WINDOWS
		MessageBoxA(GetFocus(), RealBuffer, "Fragment Warning", MB_OK | MB_ICONWARNING);
#endif
		printf("Fragment Warning: %s\n", Buffer.Get());
	};
};
