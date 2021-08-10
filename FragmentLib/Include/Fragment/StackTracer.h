#ifndef FRAGMENTLIB_STACKTRACER_H
#define FRAGMENTLIB_STACKTRACER_H
namespace Fragment
{
	/*!
		\addtogroup stackservices Stack Tracking Services
		@{
	*/

	//!IStackTracer is a custom stack tracing container
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 11-7-2008
		\note This is not a true stack tracer, where it automatically tracks the stack, 
			it is merely used to help track down your program's flow.
	*/
	class IStackTracer
	{
	private:
		class IStackTracerObject
		{
		public:
			StringA Name;
			unsigned long Line;
			StringA File;
			Array<IStackTracerObject> Childs;
			unsigned long ScopeLevel;
		};
		IStackTracerObject Root;
		Array<IStackTracerObject*> TracerPath;
		StringA ContentString;
		unsigned int ScopeLevel;
		void GenTrackStrings(DynamicArray<StringA> &Copy, IStackTracerObject &Self, 
			IStackTracerObject *Parent, bool Histogram);
		Array<void*> Clients;
	public:
		IStackTracer();
		/*!
			\note private use, do not use it yourself.
		*/
		void RegisterClient(void* Client);
		/*!
			\note private use, do not use it yourself.
		*/
		void UnregisterClient(void* Client);
		//!ClearStack will clear the stack's contents
		void ClearStack();
		//!PushObject will add an object to the stack
		/*!
			\param Name is the object's name
			\param Line is the object's line in the file
			\param File is the file's name
			\param Sub is whether this is a sub Object
		*/
		void PushObject(const char* Name, unsigned int Line, const char* File, bool Sub = false);
		//!Pop will move the stack one level up if any sub objects were added
		void Pop();
		//!Contents will create a string containing a list of steps during the program's execution
		/*!
			\param Histogram should be set to true if you wish to just a list of object names
			\return nullptr if no content, non-nullptr containing a string on success
		*/
		const char* Contents(bool Histogram = false);
	};

	//!GetStackTracer will return the current stack tracer
	IStackTracer *GetStackTracer();

	//!FeedStackTracer will setup a stack tracer for use
	/*!
		\param Tracer is the stack tracer
	*/
	void FeedStackTracer(IStackTracer *Tracer);

	//!CreateDefaultStackTracer will create the default stack tracer
	void CreateDefaultStackTracer();

#define FRAGMENTLIB_PUSHSTACKOBJECT(Name) \
	((GetStackTracer()) ? (GetStackTracer()->PushObject(Name, __LINE__, __FILE__)) : (0));

#define FRAGMENTLIB_PUSHSTACKFUNCTION(Function) \
	((GetStackTracer()) ? (GetStackTracer()->PushObject(Function, __LINE__, __FILE__)) : (0));

#define FRAGMENTLIB_PUSHSTACKSELF() \
	((GetStackTracer()) ? (GetStackTracer()->PushObject(__FUNCTION__, __LINE__, __FILE__)) : (0));

#define FRAGMENTLIB_PUSHSTACKSUBOBJECT(Name) \
	((GetStackTracer()) ? (GetStackTracer()->PushObject(Name, __LINE__, __FILE__, true)) : (0));

#define FRAGMENTLIB_PUSHSTACKSUBFUNCTION(Name, Arguments) \
	((GetStackTracer()) ? (GetStackTracer()->PushFunction(Name, Arguments, __LINE__, __FILE__, true)) : (0));

#define FRAGMENTLIB_PUSHSTACKSUBSELF() \
	((GetStackTracer()) ? (GetStackTracer()->PushObject(__FUNCTION__, __LINE__, __FILE__, true)) : (0));

#define FRAGMENTLIB_POPSTACK() \
	((GetStackTracer()) ? (GetStackTracer()->Pop()) : (0));

#define FRAGMENTLIB_STACKCONTENTS() \
	((GetStackTracer()) ? (GetStackTracer()->Contents()) : (0))

#define FRAGMENTLIB_STACKCONTENTS_HISTOGRAM() \
	((GetStackTracer()) ? (GetStackTracer()->Contents(true)) : (0))

	/*!
		@}
	*/
};
#endif
