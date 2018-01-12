#include "grammar/jsonwc.parser.h"
#include "grammar/jsonwc.lex.h"

namespace jsonwc
{
	ParserState::ParserState(IInputStream *stream): Input(stream)
	{
		if (jsonwclex_init_extra(this, &Lexer) != 0)
			throw Exception("jsonwclex_init failed");
	}

	ParserState::~ParserState()
	{ jsonwclex_destroy(Lexer); }

	void ParserState::Parse()
	{
		jsonwcparse(Lexer);
	}

	void ParserState::OnError(JSONWCLTYPE *loc, const char *msg)
	{
		throw ParserError(std::make_pair(loc->first_line, loc->first_column), std::make_pair(loc->last_line, loc->last_column), msg);
	}

	void _parseError(JSONWCLTYPE *loc, void * scanner, const char *msg)
	{ static_cast<jsonwc::ParserState*>(jsonwcget_extra(scanner))->OnError(loc, msg); }

}
