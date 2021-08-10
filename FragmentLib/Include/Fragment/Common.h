#ifndef FRAGMENTLIB_COMMON_H
#define FRAGMENTLIB_COMMON_H
//Version Info
#define FRAGMENTLIB_VERSION 0x002A //0.0.2 Alpha
#define FRAGMENTLIB_VERSION_MAJOR 0
#define FRAGMENTLIB_VERSION_MINOR 0
#define FRAGMENTLIB_VERSION_BUILD 2
#define FRAGMENTLIB_VERSION_STATE 'A' //Alpha

#define SILENTFRASSERT(var) \
	if(!(var))\
	{\
		return 0;\
	}

#define SILENTVOIDFRASSERT(var) \
	if(!(var))\
	{\
		return;\
	}

#define SILENTFUNCFRASSERT(var, func) \
	if(!(var))\
	{ \
		func;\
	}

#ifdef FRCOMPILER_MSVC
#define FRASSERT(var, desc) \
	if(!(var))\
	{\
		Fragment::LibWarning(desc,__LINE__,__FILE__,__FUNCTION__,#var);\
		__asm{int 3};\
	}
#else
#define FRASSERT(var, desc) \
	if(!(var))\
	{\
		Fragment::LibWarning(desc,__LINE__,__FILE__,__FUNCTION__,#var);\
		throw;\
	}
#endif

#define nullptr 0

namespace Fragment
{
	//!LibWarning will display an error message
	/*!
		\param Description is the error's description
		\param Line is the file's line
		\param FileName is the Filename
		\param Function is the file's function
		\param Variable is the variable that failed an assertion
	*/
	void LibWarning(const char* Description, unsigned int Line, const char* FileName, 
		const char* Function, const char* Variable);
};

#endif
