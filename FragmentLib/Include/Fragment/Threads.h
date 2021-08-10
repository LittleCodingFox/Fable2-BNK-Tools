#ifndef FRAGMENT_THREADS_H
#define FRAGMENT_THREADS_H
namespace Fragment
{
	/*!
		\addtogroup threads Threads and Multicore Services
		@{
	*/

#ifdef FRPLATFORM_WINDOWS
	typedef unsigned long (*ThreadFunctionTemplate)(void* Object);
#else
	typedef void*(*ThreadFunctionTemplate)(void* Object);
#endif

	enum ThreadPriorities //!Thread priorities
	{
		FRTP_ABOVE_NORMAL = 0, //!<Above Normal
		FRTP_BELOW_NORMAL, //!<Below Normal
		FRTP_HIGHEST, //!<Highest Priority
		FRTP_IDLE, //!<Idle
		FRTP_LOWEST, //!<Lowest Priority
		FRTP_NORMAL, //!<Normal
		FRTP_TIME_CRITICAL, //!<Time Critical
		FRTP_FORCE_32_BIT = 0xFFFFFFFF //!<Force 32-bit Integer
	};

	//!Thread is a Thread Container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 6-11-2008
	*/
	class Thread
	{
	private:
#ifdef FRPLATFORM_WINDOWS
		HANDLE ThreadHandle;
#else
		bool Created;
		pthread_t ThreadHandle;
#endif
	public:
		Thread();
		~Thread();
		//!Initialize will initialize and execute a Thread
		/*!
			\param Function is the thread's calling function
			\param Object is the thread's calling function's Parameter
		*/
		bool Initialize(ThreadFunctionTemplate Function, void* Object = nullptr);
		//!Stop will stop our thread
		/*!
			\warning C++ destructors will not be called if you call this, 
			and there may be some memory leaks depending on your function.
			Use this only when extremely necessary.
		*/
		void Stop();
		//!SetPriority will change the Thread's Priority
		/*!
			\param Priority is one of FRTP_*
		*/
		void SetPriority(unsigned long Priority);
	};

	//!CurrentThread is our active thread
	extern Thread CurrentThread();

	//!Mutex is a Mutual Exclusion Synchronization Object
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 6-11-2008
	*/
	class Mutex
	{
	private:
		bool _Locked;
#ifdef FRPLATFORM_WINDOWS
		HANDLE MutexHandle;
#else
		pthread_mutex_t MutexHandle;
#endif
	public:
		Mutex();
		~Mutex();
		//!Lock will lock a thread
		void Lock();
		//!Locked will inform the user whether the mutex is already locked
		bool Locked();
		//!Unlock will unlock a thread
		void Unlock();
	};

	//!MutexLocker is a mutex auto locking class
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 6-11-2008
	*/
	class MutexLocker
	{
	private:
		Mutex *m;
	public:
		MutexLocker(Mutex &m);
		~MutexLocker();
	};

	/*!
		@}
	*/
};
#endif