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
		struct IState;

		struct Result
		{
			IState *	NewState;
			size_t		ReadData;
		};

		struct IState
		{
			virtual ~IState() { }
			virtual Result Feed(const char *data, size_t size) { return Result { this, size }; }
		};

		template<typename ReceiverType>
		struct State : public IState
		{
			ReceiverType * Receiver;

			State(ReceiverType *recv = nullptr) : Receiver(recv) { }
		};

		IState * _currentState;

		class StringState : public State<IJsonValueReceiver>
		{ } _stringState;
		class IntegerState : public State<IJsonValueReceiver>
		{ } _integerState;
		class NumberState : public State<IJsonValueReceiver>
		{ } _numberState;
		class JsonObjectState : public State<IJsonObjectReceiver>
		{
			using State::State;
		} _jsonObjectState;
		class ObjectState : public State<IObjectReceiver>
		{ } _objectState;
		class ArrayState : public State<IJsonArrayReceiver>
		{ } _arrayState;

	public:
		Parser(IObjectReceiver *root);

		void Feed(const char *data, size_t size);
	};


}

#endif
