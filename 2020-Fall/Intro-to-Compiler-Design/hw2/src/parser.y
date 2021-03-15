%{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int32_t line_num;  /* declared in scanner.l */
extern char buffer[512];  /* declared in scanner.l */
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */

extern int yylex(void); 
static void yyerror(const char *msg);
%}

%token ID SCI FP OCT DEC BOOLCONST STR
%token TYPE ARR BEG END DEF IF THEN ELSE DO FOR WHILE OF PRINT READ TO RETURN VAR
%token ASSIGN
%left GROUP /* (...) */
%left NOT NEG
%left '*' '/' MOD
%left '+' '-'
%left LT LE NE GE GT EQ
%left AND
%left OR

%%

program: program_name ';' decl_scope func_decl_scope compound_stmt END
	;
program_name: ID
	;
decl_scope: %empty | multi_decl
	;
multi_decl: decl multi_decl | decl
	;
decl: VAR id_type_pair ';'
	;
id_type_pair: id_list ':' type_of_decl
	;
id_list: %empty | multi_id_list
	;
multi_id_list: multi_id_list ',' ID | ID
	;
type_of_decl: TYPE | ARR DEC OF array_type | literal_const
	;
array_type: TYPE | ARR DEC OF array_type
	;
literal_const: SCI | FP | OCT | DEC | BOOLCONST | STR
	;
func_decl_scope: %empty | multi_func_decl
	;
multi_func_decl: multi_func_decl func_decl | func_decl
	;
func_decl: ID '(' argument ')' type_of_ret func_body
	;
argument: %empty | multi_args
	;
multi_args: multi_args id_type_pair | id_type_pair
	;
type_of_ret: %empty | ':' TYPE
	;
func_body: ';' | compound_stmt END
	;
compound_stmt: BEG decl_scope stmt_scope END
	;
stmt_scope: %empty | multi_stmt
	;
multi_stmt: stmt multi_stmt | stmt
	;
stmt: compound_stmt | simple_stmt ';' | branch | while_stmt | for_stmt | ret_stmt | proc_call
	;
simple_stmt: var_ref ASSIGN exp | PRINT exp | READ var_ref
	;
var_ref: ID arr_ref
	;
arr_ref: %empty | '[' exp ']' arr_ref
	;
exp: '(' exp ')' %prec GROUP
	| '-' exp %prec NEG | NOT exp
	| exp '*' exp | exp '/' exp | exp MOD exp
	| exp '+' exp | exp '-' exp
	| exp LT exp | exp LE exp | exp NE exp | exp GE exp | exp GT exp | exp EQ exp
	| exp AND exp | exp OR exp
	| var_ref | SCI | FP | OCT | DEC | BOOLCONST | STR | func_call
	;
branch: IF exp THEN compound_stmt branch_body END IF
	;
branch_body: %empty | ELSE compound_stmt
	;
while_stmt: WHILE exp DO compound_stmt END DO
	;
for_stmt: FOR ID ASSIGN DEC TO DEC DO compound_stmt END DO
	;
ret_stmt: RETURN exp ';'
	;
proc_call: func_call ';'
	;
func_call: ID '(' arg2func ')'
	;
arg2func: %empty | multi_exp
	;
multi_exp: multi_exp ',' exp | exp
	;

%%

void yyerror(const char *msg) {
	fprintf(stderr,
			"\n"
			"|-----------------------------------------------------------------"
			"---------\n"
			"| Error found in Line #%d: %s\n"
			"|\n"
			"| Unmatched token: %s\n"
			"|-----------------------------------------------------------------"
			"---------\n",
			line_num, buffer, yytext);
	exit(-1);
}

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./parser <filename>\n");
		exit(-1);
	}

	yyin = fopen(argv[1], "r");
	assert(yyin != NULL && "fopen() fails.");

	yyparse();

	printf("\n"
		   "|--------------------------------|\n"
		   "|  There is no syntactic error!  |\n"
		   "|--------------------------------|\n");
	return 0;
}
