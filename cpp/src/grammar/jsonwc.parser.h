#include <jsonwc.h>
#include <sstream>
#include <functional>

#include "grammar/jsonwc.tab.h"
#include "grammar/jsonwc.lex.h"

namespace jsonwc
{
	struct ParserState
	{
		IInputStream *		Input;

		union {
			IntegerType		IntegerValue;
			NumberType		NumberValue;
		};
		std::stringstream StringBuffer;

		void ResetString()
		{
			StringBuffer.str(std::string());
			StringBuffer.clear();
		}

		std::string GetString()
		{ return StringBuffer.str(); }

		ParserState(IInputStream *stream);
		~ParserState();

		void Parse();
		void OnError(JSONWCLTYPE *loc, const char *msg);
	};

	inline void _parseError(JSONWCLTYPE *loc, jsonwc::ParserState * state, const char *msg)
	{ state->OnError(loc, msg); }
}
