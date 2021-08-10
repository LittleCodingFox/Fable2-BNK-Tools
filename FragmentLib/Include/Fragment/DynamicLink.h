#ifndef FRAGMENTLIB_DYNAMICLINK_H
#define FRAGMENTLIB_DYNAMICLINK_H
namespace Fragment
{
	/*!
		\addtogroup dynamiclink Dynamic Linking Services
		@{
	*/

	//!DynamicLibrary is a class for dynamic linking
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 31-5-2008
	*/
	class DynamicLibrary
	{
	private:
		void* Handle;
	public:
		DynamicLibrary();
		~DynamicLibrary();
		//!Load will attempt to load a dynamic linking library from a filename
		/*!
			\param FileName is the File to load
		*/
		bool Load(NativeString FileName);
		//!GetAddressAt will return the address of a function
		/*!
			\param ProcName is the name of the function
		*/
		void* GetAddressAt(NativeString ProcName);
	};

	/*!
		@}
	*/

};
#endif
