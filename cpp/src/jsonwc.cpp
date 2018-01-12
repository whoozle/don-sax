#include <jsonwc.h>
#include "grammar/jsonwc.parser.h"
#include <string>
#include <sstream>

namespace jsonwc
{
	namespace
	{
		std::string ToString(int token)
		{
			switch(token)
			{
				case TNULL:
					return "null";
				case TFALSE:
					return "false";
				case TTRUE:
					return "true";
				case TINTEGER:
					return "integer";
				case TNUMBER:
					return "number";
				case TSTRING:
					return "string";
				case TIDENTIFIER:
					return "identifier";
				case TOBJECTBEGIN:
					return "{";
				case TOBJECTEND:
					return "}";
				case TARRAYBEGIN:
					return "[";
				case TARRAYEND:
					return "]";
				case TSEPARATOR:
					return "separator(, or ;)";
				case TCOLON:
					return ":";
				default:
					return "unknown token";
			}
		}
	}

	Parser::Parser(IValueReceiver *root)
	{ }

	void Parser::Parse(IInputStream &stream)
	{
		jsonwc::ParserState state(&stream);
		state.Parse();
	}

	std::string ParserError::FormatMessage(Location begin, Location end, const std::string &msg)
	{
		std::stringstream ss;
		if (begin.first != begin.second)
			ss << begin.first << '-' << begin.second;
		else
			ss << begin.first;
		ss << ':';
		if (end.first != end.second)
			ss << end.first << '-' << end.second;
		else
			ss << end.first;
		ss << ": " << msg;
		return ss.str();
	}

}
