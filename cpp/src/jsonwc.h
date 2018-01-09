#ifndef JSONWC_H
#define JSONWC_H

#include <string>
#include <exception>

#ifndef JSONWC_NUMBER_TYPE
#	define JSONWC_NUMBER_TYPE double
#endif

#ifndef JSONWC_INTEGER_TYPE
#	define JSONWC_INTEGER_TYPE long long
#endif

namespace jsonwc
{
	using IntegerType	= JSONWC_INTEGER_TYPE;
	using NumberType	= JSONWC_NUMBER_TYPE;

	struct IJsonArrayReceiver;
	struct IJsonObjectReceiver;
	struct IObjectReceiver;

	struct IReceiver
	{
		virtual ~IReceiver() { }

		virtual IReceiver *Finish() = 0; //return parent
	};

	struct IJsonValueReceiver : public virtual IReceiver
	{
		virtual void OnNull() = 0;
		virtual void OnBool(bool value) = 0;
		virtual void OnInteger(IntegerType value) = 0;
		virtual void OnNumber(NumberType value) = 0;
		virtual void OnString(std::string && value) = 0;

		virtual IJsonArrayReceiver * OnArray() = 0;
		virtual IJsonObjectReceiver * OnObject() = 0;
	};

	struct IJsonObjectReceiver : public virtual IReceiver
	{
		virtual IJsonValueReceiver * OnProperty(std::string && name) = 0;
	};

	struct IValueReceiver : public virtual IJsonValueReceiver
	{
		virtual IObjectReceiver * OnObject(std::string && type) = 0;
	};

	struct IObjectReceiver : public virtual IJsonObjectReceiver
	{
		virtual IValueReceiver * OnProperty(std::string && name) = 0;
	};

	struct Exception : public std::exception
	{ using std::exception::exception; };

	class Parser
	{
		IReceiver * _current;

	public:
		Parser(IObjectReceiver *root);

		void Feed(const void *data, size_t size);
	};


}

#endif
