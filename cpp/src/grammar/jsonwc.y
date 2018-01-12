%locations
%pure-parser
%error-verbose
%defines
%define api.prefix {jsonwc}

%{
#	include <jsonwc.h>
#	include "grammar/jsonwc.parser.h"
%}

%union {
	jsonwc::IntegerType i;
	jsonwc::NumberType f;
	std::string *s;
}

%parse-param { jsonwc::ParserState *parser }
%lex-param { void* parser }

%start input


%token		TNULL
%token		TFALSE
%token		TTRUE
%token <i>	TINTEGER
%token <n>	TNUMBER
%token <s>	TSTRING
%token <s>	TIDENTIFIER
%token		TOBJECTBEGIN
%token		TOBJECTEND
%token		TARRAYBEGIN
%token		TARRAYEND
%token		TSEPARATOR
%token		TCOLON

%%

elements
	: elements TSEPARATOR value 	{ }
	| value							{ }
	;

array
	: TARRAYBEGIN TARRAYEND				{ }
	| TARRAYBEGIN elements TARRAYEND	{ }
	;

value
	: TNULL					{ }
	| TFALSE				{ }
	| TTRUE					{ }
	| TINTEGER				{ }
	| TNUMBER				{ }
	| TSTRING				{ }
	| array					{ }
	| object				{ }
	;

pair
	: TSTRING TCOLON value	{ }
	;

members
	: members TSEPARATOR pair
	| pair
	;

object
	: TOBJECTBEGIN TOBJECTEND				{ }
	| TOBJECTBEGIN members TOBJECTEND		{ }
	;

input
	: value								{ }
	;
%%
