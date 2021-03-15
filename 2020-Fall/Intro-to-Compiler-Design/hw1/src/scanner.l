%{
#include <stdint.h>

#define LIST strCat(yytext)
#define TOKEN(t) { LIST; if (opt_tok) printf("<%s>\n", (t)); }
#define TOKEN_CHAR(t) { LIST; if (opt_tok) printf("<%c>\n", (t)); }
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
Delimiter ","|";"|":"|"("|")"|"["|"]"
Operator "+"|"-"|"*"|"/"|"mod"|":="|"<"|"<="|"<>"|">="|">"|"="|"and"|"or"|"not"
Keyword "array"|"begin"|"boolean"|"def"|"do"|"else"|"end"|"false"|"for"|"integer"|"if"|"of"|"print"|"read"|"real"|"string"|"then"|"to"|"true"|"return"|"var"|"while"
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
}
	/* Delimiters */
{Delimiter} { TOKEN(yytext); }
	/* Operators */
{Operator} { TOKEN(yytext); }
	/* Keywords */
{Keyword} { TOKEN_KW(yytext); }
	/* Identifiers */
{Identifier} { TOKEN_STRING(id, yytext); }
	/* Scientific Notations */
{DEC_INT}("."{FracPart})?(E|e)("+"|-)?{DEC_INT} { TOKEN_STRING(scientific, yytext); }
	/* Floating-Point Constants */
{DEC_INT}"."{FracPart} { TOKEN_STRING(float, yytext); }
	/* Integer Constants */
{OCT_INT} { TOKEN_STRING(oct_integer, yytext); }
{DEC_INT} { TOKEN_STRING(integer, yytext); }
	/* Whitespace */
[\t ]+ { LIST; }

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

int main(int argc, const char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./scanner [filename]\n");
		exit(-1);
	}

	yyin = fopen(argv[1], "r");
	if (yyin == NULL) {
		fprintf(stderr, "Open file error\n");
		exit(-1);
	}

	yylex();

	return 0;
}
