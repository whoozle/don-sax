#include "grammar/jsonwc.parser.h"

namespace jsonwc
{
	ParserState::ParserState(IInputStream *stream): Input(stream)
	{ }

	ParserState::~ParserState()
	{ }

	void ParserState::Parse()
	{
		jsonwcparse(this);
	}

	void ParserState::OnError(JSONWCLTYPE *loc, const char *msg)
	{
		throw ParserError(std::make_pair(loc->first_line, loc->first_column), std::make_pair(loc->last_line, loc->last_column), msg);
	}

}
