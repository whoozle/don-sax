#include "grammar/jsonwc.lex.h"
#include "grammar/jsonwc.parser.h"

namespace jsonwc
{
	ParserState::ParserState(IInputStream *stream): Input(stream)
	{
		if (jsonwclex_init_extra(this, &Lexer) != 0)
			throw Exception("jsonwclex_init failed");
	}

	int ParserState::GetNextToken()
	{ return jsonwclex(Lexer); }

	ParserState::~ParserState()
	{
		jsonwclex_destroy(Lexer);
	}
}
