#ifndef FRAGMENTLIB_TRANSLATION_H
#define FRAGMENTLIB_TRANSLATION_H
namespace Fragment
{
	/*!
		\addtogroup translation Translation Services
		@{
	*/

	//!ITranslationInfo is a container for program translation information
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 12-8-2008
	*/
	class ITranslationInfo : public Fragment::IUnknown
	{
	public:
		StringW Language;
		//!ITranslationBlock is a container to sort translation information
		/*!
			\author Nuno Miguel Azevedo Lopes Da Silva
			\version 1.0
			\date 12-8-2008
		*/
		class ITranslationBlock
		{
		public:
			ITranslationBlock();
			ITranslationBlock(NativeString FieldID, NativeString Text);
			NativeString FieldID;
			NativeString Text;
		};
		DynamicArray<ITranslationBlock> Blocks;
		//!FindBlock will search for a block's text given a FieldID
		/*!
			\param FieldID is the FieldID to search for
			\return the FieldID's Text or an empty NativeString
		*/
		NativeString FindBlock(NativeString FieldID);
		//!Serialize will store this Translation information into a Stream
		/*!
			\param Stream is the Stream to store the translation info
		*/
		bool Serialize(CStream Stream);
		//!Deserialize will read translation information from a Stream
		/*!
			\param Stream is the Stream to read the translation info from
		*/
		bool Deserialize(CStream Stream);
	};

	FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(TranslationInfo);

#define FRAGMENTLIB_DECLARE_TRANSLATION_OBJECT(Info, language)\
	Info->Language = language;\
	Info->Blocks.Free();

#define FRAGMENTLIB_DECLARE_TRANSLATION_BLOCK(Info, name, text)\
	Info->Blocks += Fragment::ITranslationInfo::ITranslationBlock(name, text);

#define FRAGMENTLIB_FEED_TRANSLATION_BLOCK(Info, name)\
	(Info->FindBlock(name))

#define FRAGMENTLIB_SCAN_TRANSLATION_STREAM(Info, Stream)\
	Info->Deserialize(Stream);

#define FRAGMENTLIB_DUMP_TRANSLATION_STREAM(Info, Stream)\
	Info->Serialize(Stream);

	/*!
		@}
	*/
};
#endif
