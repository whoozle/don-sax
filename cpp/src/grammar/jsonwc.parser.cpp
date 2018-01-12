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
}
