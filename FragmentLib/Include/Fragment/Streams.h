#ifndef FRAGMENTLIB_STREAMS_H
#define FRAGMENTLIB_STREAMS_H
namespace Fragment
{
	/*!
		\addtogroup streamservices Streaming Services
		@{
	*/

	enum StreamAccessTypes //!Streaming Access Types
	{
		FRSA_READ = 2, //!<Read Access
		FRSA_WRITE = 4, //!<Write Access
		FRSA_TEXT = 8, //!<Textual Access (write only)
		FRSA_FORCE_32_BIT = 0xFFFFFFFF //!<Force 32-bit integer enumeration
	};

	//!IStream is a Stream Container
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 26-3-2008
	*/
	class IStream : public Fragment::IUnknown
	{
	public:
		virtual ~IStream() {};

		//!Read will read objects from a stream
		/*!
			\param Object is the object to be read
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
		*/
		virtual bool Read(void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects) = 0;

		//!Write will write objects to a stream
		/*!
			\param Object is the object to be written
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
		*/
		virtual bool Write(const void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects) = 0;

		//!Seek will seek a read/write position on a Stream
		/*!
			\param Position is the seeking position
		*/
		virtual bool Seek(unsigned long long Position = 0) = 0;

		//!Size will return the size of the data contained in a Stream
		virtual unsigned long long Size() = 0;

		//!Position will return the current read/write position on the Stream
		virtual unsigned long long Position() = 0;
	};

	//!Stream Typedef
	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(Stream);

	//!IMemoryStream is an in-memory stream
	class IMemoryStream : public IStream
	{
	private:
		unsigned long long StreamSize, ReadPos;
		Array<unsigned char> Data;
		Mutex StreamMutex;
	public:
		IMemoryStream();

		//!Read will read objects from this stream
		/*!
			\param Object is the object to be read
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
		*/
		bool Read(void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects);

		//!Write will write objects to this stream
		/*!
			\param Object is the object to be written
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
		*/
		bool Write(const void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects);

		//!Seek will seek a read/write position on this Stream
		/*!
			\param Position is the seeking position
		*/
		bool Seek(unsigned long long Position = 0);

		//!Size will return the size of the data contained in this Stream
		unsigned long long Size();

		//!Position will return the current read/write position on the Stream
		unsigned long long Position();

		//!Get will return a pointer to the data contained in the Memory Stream
		void* Get();
	};

	//!MemoryStream Typedef
	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(MemoryStream);

	//!IStdioFileStream is a file container as a Stream
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 27-3-2008
	*/
	class IStdioFileStream : public IStream
	{
	private:
		void* FileHandle;
		unsigned long long FileSize, ReadPos;
		unsigned int OpenMode;
		void Destroy();
		Mutex StreamMutex;
	public:
		IStdioFileStream();
		~IStdioFileStream();

		//!Create will open a file as a stream
		/*!
			\param FileName is the file to open
			\param OpenMode is one or a bitmask of FRSA_*
		*/
		bool Create(NativeString FileName, unsigned int OpenMode);

		//!Read will read objects from this file
		/*!
			\param Object is the object to be read
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
			\note If you've opened this file as text, and are reading the content to a string, 
			read the content as a StringA, and then convert to a StringW.
			Doing otherwise will lead to undefined behaviour.
		*/
		bool Read(void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects);

		//!Write will write objects to this file
		/*!
			\param Object is the object to be written
			\param SizePerObject is the size in bytes per each object
			\param TotalObjects is the total objects to read
			\note If you've opened this file as text, and are writing the content from a string, 
			convert the content to a StringA.
			Doing otherwise will lead to undefined behaviour.
		*/
		bool Write(const void* Object, unsigned long long SizePerObject, 
			unsigned long long TotalObjects);

		//!Seek will seek a read/write position on this file
		/*!
			\param Position is the seeking position
		*/
		bool Seek(unsigned long long Position = 0);

		//!Size will return the size of the data contained in this file
		unsigned long long Size();

		//!Position will return the current read/write position on the Stream
		unsigned long long Position();
	};

	//!StdioFileStream typedef
	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(StdioFileStream)

	/*!
		@}
	*/

};
#endif
