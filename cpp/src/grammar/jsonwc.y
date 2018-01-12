%locations
%pure-parser
%error-verbose
%defines
%define api.prefix {jsonwc}

%{
#	include <jsonwc.h>
#	include "grammar/jsonwc.parser.h"
#	include "grammar/jsonwc.lex.h"
%}

%union {
	jsonwc::IntegerType i;
	jsonwc::NumberType f;
	std::string *s;
}

%parse-param	{ void * scanner }
%lex-param		{ void * scanner }

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

array_elements
	: array_elements TSEPARATOR value		{ }
	| value									{ }
	;

array
	: TARRAYBEGIN TARRAYEND					{ }
	| TARRAYBEGIN array_elements TARRAYEND	{ }
	;

json_value
	: TNULL					{ }
	| TFALSE				{ }
	| TTRUE					{ }
	| TINTEGER				{ }
	| TNUMBER				{ }
	| TSTRING				{ }
	| array					{ }
	| json_object			{ }
	;

value
	: json_value
	| object
	;

object_property
	: TSTRING TCOLON value			{ }
	| TIDENTIFIER TCOLON value		{ }
	;

object_property_list
	: object_property_list TSEPARATOR object_property
	| object_property
	;

object
	: TIDENTIFIER TOBJECTBEGIN TOBJECTEND									{ }
	| TIDENTIFIER TOBJECTBEGIN object_property_list TOBJECTEND				{ }
	| TIDENTIFIER TOBJECTBEGIN object_property_list TSEPARATOR TOBJECTEND	{ }
	;

json_object_property
	: TSTRING TCOLON json_value		{ }
	;

json_property_list
	: json_property_list TSEPARATOR json_object_property
	| json_object_property
	;

json_object
	: TOBJECTBEGIN TOBJECTEND									{ }
	| TOBJECTBEGIN json_property_list TOBJECTEND				{ }
	| TOBJECTBEGIN json_property_list TSEPARATOR TOBJECTEND		{ }
	;

input
	: value											{ }
	;
%%
