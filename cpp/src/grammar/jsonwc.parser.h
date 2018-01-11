#include <jsonwc.h>
#include <sstream>
#include <functional>

namespace jsonwc
{
	struct ParserState
	{
		IInputStream *		Input;
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

		int GetNextToken();

		ParserState(IInputStream *stream);
		~ParserState();
	};
}