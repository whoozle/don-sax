#ifndef JSONWC_H
#define JSONWC_H

#include <string>
#include <stdexcept>

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

		virtual IJsonArrayReceiver * OnJsonArray() = 0;
		virtual IJsonObjectReceiver * OnJsonObject() = 0;
	};

	struct IJsonArrayReceiver : public virtual IReceiver
	{
		virtual IJsonValueReceiver * OnArrayValue() = 0;
	};

	struct IJsonObjectReceiver : public virtual IReceiver
	{
		virtual IJsonValueReceiver * OnObjectProperty(std::string && name) = 0;
	};

	struct IValueReceiver : public virtual IJsonValueReceiver
	{
		virtual IObjectReceiver * OnObject(std::string && type) = 0;
	};

	struct IObjectReceiver : public virtual IJsonObjectReceiver
	{
		virtual IValueReceiver * OnObjectProperty(std::string && name) = 0;
	};

	struct Exception : public std::runtime_error
	{ using std::runtime_error::runtime_error; };

	struct ParserError : public Exception
	{
		using Location = std::pair<int, int>;
		Location Begin, End;


		ParserError(Location begin, Location end, const std::string &msg) : Exception(FormatMessage(begin, end, msg)), Begin(begin), End(end)
		{ }

		static std::string FormatMessage(Location begin, Location end, const std::string &msg);
	};

	struct IInputStream
	{
		virtual ~IInputStream() { }
		virtual int Read(void *data, int size) = 0;
	};

	class ParserState;
	class Parser
	{
	public:
	public:
		Parser(IValueReceiver *root);
		void Parse(IInputStream &stream);
	};


}

#endif
