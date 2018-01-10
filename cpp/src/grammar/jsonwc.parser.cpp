#include "grammar/jsonwc.lex.h"
#include "grammar/jsonwc.parser.h"

namespace jsonwc
{
	ParserState::ParserState()
	{
		if (jsonwclex_init(&Lexer) != 0)
			throw Exception("jsonwclex_init failed");
	}

	ParserState::~ParserState()
	{
		jsonwclex_destroy(Lexer);
	}
}
