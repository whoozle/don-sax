#include <jsonwc.h>
#include <sstream>
#include <functional>

namespace jsonwc
{
	struct ParserState
	{
		yyscan_t			Lexer;

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

		std::function<size_t (void *, size_t)> Read;

		ParserState();
		~ParserState();
	};
}