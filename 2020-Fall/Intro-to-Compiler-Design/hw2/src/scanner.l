%{
#include <stdint.h>

#include "parser.h"

#define LIST strCat(yytext)
#define TOKEN(t) { LIST; if (opt_tok) printf("<%s>\n", (t)); }
#define TOKEN_STRING(t, s) { LIST; if (opt_tok) printf("<%s: %s>\n", #t, (s)); }
#define TOKEN_KW(t) { LIST; if (opt_tok) printf("<KW%s>\n", (t)); }
#define MAX_LINE_LENG 512

uint32_t line_num = 1;
char buffer[MAX_LINE_LENG];

static int32_t opt_src = 1;
static int32_t opt_tok = 1;
static char *buffer_ptr = buffer;

static void strCat(const char *Text);

%}
Type "boolean"|"integer"|"real"|"string"
Bool "true"|"false"
Identifier [A-Za-z][A-Za-z0-9]*
OCT_INT 0[0-7]+
DEC_INT [1-9][0-9]*|0
FracPart 0|[0-9]*[1-9]

%x COMMENT
%%
	/*Muti Line Comments */
"/*" { LIST; BEGIN COMMENT; }
<COMMENT>. { LIST; }
<COMMENT>"*/" { LIST; BEGIN INITIAL; }

	/* Pseudocomments */
"//&S+".* { opt_src = 1; LIST; }
"//&S-".* { opt_src = 0; LIST; }
"//&T+".* { opt_tok = 1; LIST; }
"//&T-".* { opt_tok = 0; LIST; }

	/* Single Line Comment */
"//".* { LIST; }

	/* String Constants */
[\42]([^\42\n]|[\42]{2})*[\42] {
	LIST;
	char yytext_n[yyleng];
	int i = 1, j = 0;
	while(i < yyleng - 1){
		if(yytext[i] == 34 && yytext[i + 1] == 34)
			i++;
		yytext_n[j++] = yytext[i++];
	}
	yytext_n[j] = '\0';
	if (opt_tok) printf("<string: %s>\n", yytext_n);
	return STR;
}

	/* Delimiters */
"," { TOKEN(yytext); return ','; }
";" { TOKEN(yytext); return ';'; }
":" { TOKEN(yytext); return ':'; }
"(" { TOKEN(yytext); return '('; }
")" { TOKEN(yytext); return ')'; }
"[" { TOKEN(yytext); return '['; }
"]" { TOKEN(yytext); return ']'; }

	/* Operators */
"+" { TOKEN(yytext); return '+'; }
"-" { TOKEN(yytext); return '-'; }
"*" { TOKEN(yytext); return '*'; }
"/" { TOKEN(yytext); return '/'; }
":=" { TOKEN(yytext); return ASSIGN; }
"<" { TOKEN(yytext); return LT; }
"<=" { TOKEN(yytext); return LE; }
"<>" { TOKEN(yytext); return NE; }
">=" { TOKEN(yytext); return GE; }
">" { TOKEN(yytext); return GT; }
"=" { TOKEN(yytext); return EQ; }
"mod" { TOKEN(yytext); return MOD; }
"and" { TOKEN(yytext); return AND; }
"or" { TOKEN(yytext); return OR; }
"not" { TOKEN(yytext); return NOT; }

	/* Keywords */
{Type} { TOKEN_KW(yytext); return TYPE; }
{Bool} { TOKEN_KW(yytext); return BOOLCONST; }
"array" { TOKEN_KW(yytext); return ARR; }
"begin" { TOKEN_KW(yytext); return BEG; }
"end" { TOKEN_KW(yytext); return END; }
"def" { TOKEN_KW(yytext); return DEF; }
"if" { TOKEN_KW(yytext); return IF; }
"then" { TOKEN_KW(yytext); return THEN; }
"else" { TOKEN_KW(yytext); return ELSE; }
"do" { TOKEN_KW(yytext); return DO; }
"for" { TOKEN_KW(yytext); return FOR; }
"while" { TOKEN_KW(yytext); return WHILE; }
"of" { TOKEN_KW(yytext); return OF; }
"print" { TOKEN_KW(yytext); return PRINT; }
"read" { TOKEN_KW(yytext); return READ; }
"to" { TOKEN_KW(yytext); return TO; }
"return" { TOKEN_KW(yytext); return RETURN; }
"var" { TOKEN_KW(yytext); return VAR; }

	/* Identifiers */
{Identifier} { TOKEN_STRING(id, yytext); return ID; }

	/* Scientific Notations */
{DEC_INT}("."{FracPart})?(E|e)("+"|-)?{DEC_INT} { TOKEN_STRING(scientific, yytext); return SCI; }

	/* Floating-Point Constants */
{DEC_INT}"."{FracPart} { TOKEN_STRING(float, yytext); return FP; }

	/* Integer Constants */
{OCT_INT} { TOKEN_STRING(oct_integer, yytext); return OCT; }
{DEC_INT} { TOKEN_STRING(integer, yytext); return DEC; }

	/* Whitespace */
[\t ]+ { LIST; }

	/* Newline */
<INITIAL,COMMENT>\n {
	if (opt_src) {
		printf("%d: %s\n", line_num, buffer);
	}
	++line_num;
	buffer[0] = '\0';
	buffer_ptr = buffer;
}

	/* Catch the character which is not accepted by rules above */
. {
	printf("Error at line %d: bad character \"%s\"\n", line_num, yytext);
	exit(-1);
}

%%

static void strCat(const char *Text) {
	while (*Text) {
		*buffer_ptr++ = *Text++;
	}
	*buffer_ptr = '\0';
}