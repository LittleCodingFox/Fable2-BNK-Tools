#ifndef FRAGMENTLIB_PROPERTY_H
#define FRAGMENTLIB_PROPERTY_H
namespace Fragment
{
	/*!
		\addtogroup property Class Property Services
		@{
	*/

	//!IProperty is a .NET delegate-like object
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 12-8-2008
	*/
	template<typename ObjectType>
	class IProperty
	{
	private:
		virtual void OnEqual(const ObjectType &Object) = 0;
		virtual void OnPlusEqual(const ObjectType &Object) = 0;
		virtual void OnMinusEqual(const ObjectType &Object) = 0;
		virtual void OnMultEqual(const ObjectType &Object) = 0;
		virtual void OnDivEqual(const ObjectType &Object) = 0;
	public:
		virtual ~IProperty() {};
		void operator=(const ObjectType &Object)
		{
			OnEqual(Object);
		};

		void operator+=(const ObjectType &Object)
		{
			OnPlusEqual(Object);
		};

		void operator-=(const ObjectType &Object)
		{
			OnMinusEqual(Object);
		};

		void operator*=(const ObjectType &Object)
		{
			OnMultEqual(Object);
		};

		void operator/=(const ObjectType &Object)
		{
			OnDivEqual(Object);
		};
	};

	/*!
		@}
	*/
};
#endif
