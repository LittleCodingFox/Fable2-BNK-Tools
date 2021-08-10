#ifndef FRAGMENTLIB_PLATFORM_H
#define FRAGMENTLIB_PLATFORM_H
#if defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64)
    #if defined (_WIN32) || defined (WIN32)
        #define FRPLATFORM_WIN32
    #else
        #define FRPLATFORM_WIN64
    #endif

	#define FRPLATFORM_WINDOWS

	#define FRPLATFORM_PATHSPLIT '\\'
	#define FRPLATFORM_PATHSPLITSTRING "\\"

#elif defined(__linux__)
    #define FRPLATFORM_LINUX

	#define FRPLATFORM_PATHSPLIT '/'
	#define FRPLATFORM_PATHSPLITSTRING "/"

#elif defined(__APPLE__)
	#define FRPLATFORM_MACOSX

	#define FRPLATFORM_PATHSPLIT '/'
	#define FRPLATFORM_PATHSPLITSTRING "/"

#else
	#error Unknown or unsupported platform
#endif

#ifdef _DEBUG
	#define FRPLATFORM_DEBUG
#endif

#if defined(_UNICODE) || defined(UNICODE)
	#define FRPLATFORM_UNICODE
	#define NativeString Fragment::StringW
	#define NativeText(a) L##a
#else
	#define NativeString Fragment::StringA
	#define NativeText(a) a
#endif

#ifdef __GNUC__
    #define FRCOMPILER_GCC
	#define FRCOMPILER_VERSION_MAJOR __GNUC__
	#define FRCOMPILER_VERSION_MINOR __GNUC_MINOR__
	#define FRCOMPILER_VERSION_BUILD __GNUC_PATCHLEVEL__
#elif defined(_MSC_VER)
    #define FRCOMPILER_MSVC
	#define FRCOMPILER_VERSION _MSC_VER
/*
    #pragma warning(disable:4313)
    #pragma warning(disable:4239)
    #pragma warning(disable:4201)
    #ifndef NO_DISABLE_POSSIBLE_BUG_DETECTING_WARNINGS
        #pragma warning(disable:4706)
        #pragma warning(disable:4100)
        #pragma warning(disable:4127)
		#pragma warning(disable:4512)
    #endif
*/
#else
    #error Unknown or unsupported compiler
#endif
#endif
