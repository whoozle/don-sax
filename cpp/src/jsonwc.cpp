#include <jsonwc.h>
#include "grammar/jsonwc.parser.h"
#include <string>
#include <sstream>

namespace jsonwc
{
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
