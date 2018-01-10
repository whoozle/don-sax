#include <jsonwc.h>
#include <sstream>
#include <functional>

/* Token type.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
  enum yytokentype
  {
    TNULL = 258,
    TFALSE = 259,
    TTRUE = 259,
    TINTEGER = 260,
    TNUMBER = 261,
    TSTRING = 262,
    TIDENTIFIER = 263,
    TOBJECTBEGIN = 264,
    TOBJECTEND = 265,
    TARRAYBEGIN = 266,
    TARRAYEND = 267,
    TSEPARATOR = 268,
    TCOLON = 269,
  };
#endif

namespace jsonwc
{
	struct ParserState
	{
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
	};
}