#ifndef FRAGMENTLIB_CLASS_INTERFACE_H
#define FRAGMENTLIB_CLASS_INTERFACE_H
namespace Fragment
{
	/*!
		\addtogroup dynamiclink
		@{
	*/

#define FRAGMENTLIB_DECLARE_CLASS_INTERFACE(classname)\
	class classname\
	{\
	private:\
		class classname##Internal\
		{\
		public:\
			Fragment::IDynamicLibrary Link;\
			static Fragment::Array<NativeString> ExportFuncs;\
			classname##Internal();\
			static Fragment::Array<void*> FuncPtrs;\
		};\
		static classname##Internal Instance;\
	public:\
		~classname();\

#define FRAGMENTLIB_DECLARE_CLASS_INTERFACE_STATIC(classname)\
	class classname\
	{\
	private:\
		static classname Instance;\
		classname();\
	public:\

#define FRAGMENTLIB_DECLARE_CLASS_INTERFACE_FUNCTION(type, name, arguments)\
	static type name arguments;

#define FRAGMENTLIB_COMPLETE_CLASS_INTERFACE_DECLARATION()\
	};

#define FRAGMENTLIB_IMPLEMENT_CLASS_INTERFACE_FUNCTION(classname, type, name, funcname, arguments, argumentnames)\
	type classname:: name arguments\
	{\
		long Location = -1;\
		if(Location == -1)\
		{\
			bool Found = false;\
			for(unsigned long i = 0; i < Instance.ExportFuncs.Size(); i++)\
			{\
				if(Instance.ExportFuncs[i].Compare(NativeString(TONATIVETEXT(#funcname))) == 0)\
				{\
					Location = i;\
					Found = true;\
					break;\
				};\
			};\
			FRASSERT(Found, "Attempting to call an invalid function!");\
		}\
		return ((type (*) arguments)Instance.FuncPtrs[Location]) argumentnames;\
	};

#define FRAGMENTLIB_IMPLEMENT_CLASS_INTERFACE_FUNCTION_STATIC(classname, type, name, funcname, arguments, argumentnames)\
	static type classname:: name arguments\
	{\
		return funcname(argumentnames);\
	};

#define FRAGMENTLIB_LINK_CLASS_INTERFACE(classname)\
	Fragment::Array<void*> classname::classname##Internal::FuncPtrs;\
	Fragment::Array<NativeString> classname::classname##Internal::ExportFuncs;

#define FRAGMENTLIB_START_CLASS_INTERFACE_INITIALIZER_GENERATION(classname)\
	\
	classname::classname##Internal::classname##Internal()\
	{\

#define FRAGMENTLIB_INITIALIZE_CLASS_INTERFACE_METHOD(name)\
		ExportFuncs += NativeString(TONATIVETEXT(#name));\

#define FRAGMENTLIB_COMPLETE_CLASS_INTERFACE_INITIALIZER_GENERATION(classname, DLLName)\
		FRASSERT(Link.Load(TONATIVETEXT(DLLName)), "Failed to load the DLL")\
		\
		if(ExportFuncs.Size())\
		{\
			FuncPtrs.Allocate(ExportFuncs.Size());\
			for(unsigned long i = 0; i < ExportFuncs.Size(); i++)\
			{\
				FuncPtrs[i] = Link.GetAddressAt(ExportFuncs[i]);\
				FRASSERT(FuncPtrs[i] != nullptr, "Failed to load a function");\
			};\
		};\
	};\
	classname::classname##Internal classname::Instance;

#define FRAGMENTLIB_COMPLETE_CLASS_INTERFACE_INITIALIZER_GENERATION_STATIC(classname)\
	};

	/*!
		@}
	*/
};
#endif
