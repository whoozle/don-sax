%option noyywrap nounput
%option reentrant
%option yylineno
%option 8bit
%option nounistd
%option batch
%option never-interactive
%option prefix="jsonwc"
%option fast
%option perf-report

%top {
#include "grammar/jsonwc.parser.h"
}

%{
#	define PARSER (static_cast<jsonwc::ParserState*>(yyget_extra(yyscanner)))

#	define YY_INPUT(buf,result,max_size) \
      result = PARSER->Read(buf, max_size)

static inline char jsonwc_handle_escape(char c) 
{
	switch(c)
	{
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	default:
		return c;
	}
}

static inline int jsonwc_handle_hex_char(char c)
{
	if (c >= '0' || c <= '9')
		return c - '0';
	c |= 0x20; //lowercasing
	return c - 'a' + 10;
}

static inline char jsonwc_handle_hex_byte(const char *hex)
{
	return (jsonwc_handle_hex_char(hex[0]) << 4) | jsonwc_handle_hex_char(hex[1]);
}

%}

%x DQ_STRING SQ_STRING

IDENTIFIER		[a-zA-Z_$][a-zA-Z0-9_$]*
INTEGER			[+-]?[[:digit:]]+
FRAC			\.[[:digit:]]+
EXP				[eE]{INTEGER}

BYTE			[[:xdigit:]]{2}
WORD			[[:xdigit:]]{4}

TRUE			true
FALSE			false
NULL			null

%%

{INTEGER}({FRAC}|{EXP}|{FRAC}{EXP})			{ PARSER->NumberValue = atof(yytext); return TNUMBER; }
{INTEGER}									{ PARSER->IntegerValue = atoll(yytext); return TINTEGER; }

\'											{ BEGIN(SQ_STRING); PARSER->ResetString(); }
<SQ_STRING>\\[^ux]							{ PARSER->StringBuffer << jsonwc_handle_escape(yytext[1]); }
<SQ_STRING>\\u{WORD}						{ PARSER->StringBuffer << jsonwc_handle_hex_byte(yytext + 1) << jsonwc_handle_hex_byte(yytext + 3); }
<SQ_STRING>\\x{BYTE}						{ PARSER->StringBuffer << jsonwc_handle_hex_byte(yytext + 1); }
<SQ_STRING>\'								{ BEGIN(INITIAL); return TSTRING; }
<SQ_STRING>[^\\\']+							{ PARSER->StringBuffer.write(yytext, yyleng); }

\"											{ BEGIN(DQ_STRING); PARSER->ResetString(); }
<DQ_STRING>\\[^ux]							{ PARSER->StringBuffer << jsonwc_handle_escape(yytext[1]); }
<DQ_STRING>\\u{WORD}						{ PARSER->StringBuffer << jsonwc_handle_hex_byte(yytext + 1) << jsonwc_handle_hex_byte(yytext + 3); }
<DQ_STRING>\\x{BYTE}						{ PARSER->StringBuffer << jsonwc_handle_hex_byte(yytext + 1); }
<DQ_STRING>\"								{ BEGIN(INITIAL); return TSTRING; }
<DQ_STRING>[^\\\"]+							{ PARSER->StringBuffer.write(yytext, yyleng); }

{TRUE}										{ return TTRUE; }
{FALSE}										{ return TFALSE; }
{NULL}										{ return TNULL; }

[[:space:]]+								{ /*skip whitespaces*/ }
.											{ throw jsonwc::Exception("unhandled char"); }
%%
