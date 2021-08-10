#include <Fragment/Fragment.h>
#ifndef FRPLATFORM_WINDOWS
#include <dlfcn.h>
#include <unistd.h>
#endif
#include <stdlib.h>
#include <stdio.h>
namespace Fragment
{
	DynamicLibrary::DynamicLibrary()
	{
		Handle = nullptr;
	};

	DynamicLibrary::~DynamicLibrary()
	{
		if(Handle)
		{
#ifdef FRPLATFORM_WINDOWS
			FreeLibrary((HMODULE)Handle);
#else
			dlclose(Handle);
#endif
		};
	};

	bool DynamicLibrary::Load(NativeString FileName)
	{
		if(Handle)
		{
#ifdef FRPLATFORM_WINDOWS
			FreeLibrary((HMODULE)Handle);
#else
			dlclose(Handle);
#endif
		};
#ifdef FRPLATFORM_WINDOWS
		Handle = LoadLibrary(FileName);
#else
		StringA RealFileName = FileName;
		Handle = dlopen(RealFileName, RTLD_NOW | RTLD_GLOBAL );
#endif
		if(!Handle)
			return false;
		return true;
	};

	void* DynamicLibrary::GetAddressAt(NativeString ProcName)
	{
		SILENTFRASSERT(Handle && ProcName.Length());
#ifdef FRPLATFORM_WINDOWS
		return (void*)GetProcAddress((HMODULE)Handle, StringA(ProcName));
#else
		return dlsym(Handle, StringA(ProcName));
#endif
	};

};
