#include <jsonwc.h>

namespace jsonwc
{
	Parser::Parser(IObjectReceiver *root): _currentState(&_objectState), _jsonObjectState(root)
	{
	}

	void Parser::Feed(const char *data, size_t size)
	{
		size_t offset = 0;
		while(offset < size)
		{
			auto result = _currentState->Feed(data + offset, size - offset);
			_currentState = result.NewState;
			offset += result.ReadData;
		}
	}

}
