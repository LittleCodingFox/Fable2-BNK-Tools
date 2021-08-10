#include <Fragment/Fragment.h>
namespace Fragment
{
#ifndef FRPLATFORM_WINDOWS
	const long MaxPrio = sched_get_priority_max(SCHED_FIFO);
	const long MinPrio = sched_get_priority_min(SCHED_FIFO);
#endif

	long PriorityIDs[] = {
#ifdef FRPLATFORM_WINDOWS
		THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_BELOW_NORMAL,
		THREAD_PRIORITY_HIGHEST, THREAD_PRIORITY_IDLE, 
		THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_NORMAL,
		THREAD_PRIORITY_TIME_CRITICAL
#else
		(long)(MaxPrio / 1.5f) , MaxPrio / 3, MaxPrio - 1, MinPrio + 1, MinPrio, MaxPrio / 2, MaxPrio
#endif
	};

	Thread::Thread()
	{
#ifdef FRPLATFORM_WINDOWS
		ThreadHandle = nullptr;
#else
		Created = false;
#endif
	};

	Thread::~Thread()
	{
#ifdef FRPLATFORM_WINDOWS
		if(ThreadHandle)
		{
			TerminateThread(ThreadHandle, 0);
			CloseHandle(ThreadHandle);
		};
		ThreadHandle = nullptr;
#else
		if(Created)
		{
			pthread_cancel(ThreadHandle);
			Created = false;
		}
#endif
	};

	bool Thread::Initialize(ThreadFunctionTemplate Function, void* object)
	{
		FRASSERT(Function, "Invalid Thread Function");
#ifdef FRPLATFORM_WINDOWS
		ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Function, object, 0, NULL);
		return ThreadHandle != INVALID_HANDLE_VALUE;
#else
		pthread_create(&ThreadHandle, nullptr, Function, object);
		Created = true;
#endif
		return true;
	};

	void Thread::Stop()
	{
#ifdef FRPLATFORM_WINDOWS
		if(ThreadHandle)
		{
			TerminateThread(ThreadHandle, 0);
			ThreadHandle = nullptr;
		}
#else
		if(Created)
		{
			pthread_cancel(ThreadHandle);
			Created = false;
		}
#endif
	};

	void Thread::SetPriority(unsigned long Priority)
	{
		FRASSERT(Priority < 7, "Invalid Priority");
#ifdef FRPLATFORM_WINDOWS
		SetThreadPriority(ThreadHandle, PriorityIDs[Priority]);
#else
		sched_param Param;
		Param.sched_priority = PriorityIDs[Priority];
		pthread_setschedparam(ThreadHandle, SCHED_FIFO, &Param);
#endif
	};

	Mutex::Mutex()
	{
		_Locked = false;
#ifdef FRPLATFORM_WINDOWS
		MutexHandle = CreateMutex(nullptr, false, nullptr);
#else
		pthread_mutex_init(&MutexHandle, nullptr);
#endif
	};

	Mutex::~Mutex()
	{
#ifdef FRPLATFORM_WINDOWS
		if(MutexHandle)
		{
			ReleaseMutex(MutexHandle);
			CloseHandle(MutexHandle);
			MutexHandle = nullptr;
		};
#else
		pthread_mutex_destroy(&MutexHandle);
#endif
	};

	void Mutex::Lock()
	{
#ifdef FRPLATFORM_WINDOWS
		WaitForSingleObject(MutexHandle, INFINITE);
#else
		pthread_mutex_lock(&MutexHandle);
#endif
		_Locked = true;
	};

	bool Mutex::Locked()
	{
		return _Locked;
	};

	void Mutex::Unlock()
	{
#ifdef FRPLATFORM_WINDOWS
		ReleaseMutex(MutexHandle);
#else
		pthread_mutex_unlock(&MutexHandle);
#endif
		_Locked = false;
	};

	MutexLocker::MutexLocker(Mutex &m)
	{
		this->m = &m;
		m.Lock();
	};

	MutexLocker::~MutexLocker()
	{
		FRASSERT(m, "Internal Error, Possible Memory Corruption: m cannot be nullptr");
		m->Unlock();
	};
};
