#include <jsonwc.h>
#include <sstream>
#include <functional>

#include "grammar/jsonwc.tab.h"

namespace jsonwc
{
	struct ParserState
	{
		IInputStream *		Input;
		void *				Lexer;

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

	void _parseError(JSONWCLTYPE *loc, void * scanner, const char *msg);
}
