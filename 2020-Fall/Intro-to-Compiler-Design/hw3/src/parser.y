%{
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"
#include "AST/AstDumper.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
	uint32_t first_line;
	uint32_t first_column;
	uint32_t last_line;
	uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static AstNode *root;
AstDumper p_vistor;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
	class AstNode;
	class ProgramNode;
	class DeclNode;
	class VariableNode;
	class ConstantValueNode;
	class ExpressionNode;
	class FunctionNode;
	class CompoundStatementNode;
	class PrintNode;
	class BinaryOperatorNode;
	class UnaryOperatorNode;
	class FunctionInvocationNode;
	class VariableReferenceNode;
	class AssignmentNode;
	class ReadNode;
	class IfNode;
	class WhileNode;
	class ForNode;
	class ReturnNode;
}

	/* For yylval */
%union {
	/* basic semantic value */
	char *text;

	AstNode *node;
	ProgramNode *n_prog;
	DeclNode *n_decl;
	VariableNode *n_var;
	ConstantValueNode *n_const;
	FunctionNode *n_func;
	CompoundStatementNode *n_cmpdstmt;
	PrintNode *n_print;
	ExpressionNode *n_expr;
	BinaryOperatorNode *n_bop;
	UnaryOperatorNode *n_uop;
	FunctionInvocationNode *n_finvo;
	VariableReferenceNode *n_varref;
	AssignmentNode *n_assign;
	ReadNode *n_read;
	IfNode *n_if;
	WhileNode *n_while;
	ForNode *n_for;
	ReturnNode *n_ret;

	std::vector<DeclNode *> *declS;
	std::vector<FunctionNode *> *funcS;
	std::vector<VariableNode *> *varS;
	std::vector<AstNode *> *stmtS;
	std::vector<ExpressionNode *> *exprS;
};
	
	/* Type of non-terminal */
%type <text> ID ReturnType Type ScalarType ArrType NegOrNot 
%type <text> STRING_LITERAL TRUE FALSE INT_LITERAL REAL_LITERAL
%type <text> BOOLEAN INTEGER REAL STRING
%type <n_prog> Program
%type <declS> DeclarationList Declarations FormalArgList FormalArgs
%type <funcS> FunctionList Functions
%type <n_cmpdstmt> CompoundStatement ElseOrNot
%type <n_decl> Declaration FormalArg
%type <n_func> Function FunctionDeclaration FunctionDefinition
%type <varS> IdList
%type <n_const> LiteralConstant IntegerAndReal StringAndBoolean ArrDecl
%type <node> Statement Simple
%type <n_if> Condition
%type <n_while> While
%type <n_for> For
%type <n_ret> Return
%type <n_finvo> FunctionCall FunctionInvocation
%type <n_varref> VariableReference
%type <exprS> ArrRefList ArrRefs ExpressionList Expressions
%type <n_expr> Expression
%type <stmtS> StatementList Statements


	/* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

	/* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

	/* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

	/* Identifier */
%token ID

	/* Literal */
%token INT_LITERAL
%token REAL_LITERAL
%token STRING_LITERAL

%%
	/*
	   Program Units
					 */

Program:
	ID SEMICOLON
	DeclarationList FunctionList CompoundStatement END {
		root = new ProgramNode(@1.first_line, @1.first_column, $1, $3, $4, $5);
		free($1);
	}
;

DeclarationList:
	Epsilon { $$ = NULL; }
	|
	Declarations { $$ = $1; }
;

Declarations:
	Declaration { $$ = new std::vector<DeclNode*>(); $$->push_back($1); }
	|
	Declarations Declaration { $1->push_back($2); $$ = $1; }
;

FunctionList:
	Epsilon { $$ = NULL; }
	|
	Functions { $$ = $1; }
;

Functions:
	Function { $$ = new std::vector<FunctionNode*>(); $$->push_back($1); }
	|
	Functions Function { $1->push_back($2); $$ = $1; }
;

Function:
	FunctionDeclaration { $$ = $1; }
	|
	FunctionDefinition { $$ = $1; }
;

FunctionDeclaration:
	ID L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON{
		if($5){
			$$ = new FunctionNode(@1.first_line, @1.first_column, $1, $5, $3, NULL);
		}
		else{
			$$ = new FunctionNode(@1.first_line, @1.first_column, $1, "void", $3, NULL);
		}
		free($1);
	}
;

FunctionDefinition:
	ID L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType CompoundStatement END {
		if($5){
			$$ = new FunctionNode(@1.first_line, @1.first_column, $1, $5, $3, $6);
		}
		else{
			$$ = new FunctionNode(@1.first_line, @1.first_column, $1, "void", $3, $6);
		}
		free($1);
	}
;

FormalArgList:
	Epsilon { $$ = NULL; }
	|
	FormalArgs { $$ = $1; }
;

FormalArgs:
	FormalArg { $$ = new std::vector<DeclNode*>(); $$->push_back($1); }
	|
	FormalArgs SEMICOLON FormalArg { $1->push_back($3); $$ = $1; }
;

FormalArg:
	IdList COLON Type {
		std::vector<VariableNode*> &vr = *($1);
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->updateNode($3, NULL);
		}
		$$ = new DeclNode(@1.first_line, @1.first_column, $1, $3);
	}
;

IdList:
	ID {
		$$ = new std::vector<VariableNode*>();
		$$->push_back(new VariableNode(@1.first_line, @1.first_column, $1, "", NULL));
	}
	|
	IdList COMMA ID {
		$1->push_back(new VariableNode(@3.first_line, @3.first_column, $3, "", NULL));
		$$ = $1;
	}
;

ReturnType:
	COLON ScalarType { $$ = $2; }
	|
	Epsilon { $$ = NULL; }
;

	/*
	   Data Types and Declarations
								   */

Declaration:
	VAR IdList COLON Type SEMICOLON {
		std::vector<VariableNode*> &vr = *($2);
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->updateNode($4, NULL);
		}
		$$ = new DeclNode(@1.first_line, @1.first_column, $2, $4);
	}
	|
	VAR IdList COLON LiteralConstant SEMICOLON {
		std::vector<VariableNode*> &vr = *($2);
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->updateNode($4->getConstantTypeCString(), $4);
		}
		$$ = new DeclNode(@1.first_line, @1.first_column, $2, $4->getConstantTypeCString());
	}
;

Type:
	ScalarType { $$ = $1; }
	|
	ArrType { $$ = $1; }
;

ScalarType:
	INTEGER { $$ = $1; }
	|
	REAL { $$ = $1; }
	|
	STRING { $$ = $1; }
	|
	BOOLEAN { $$ = $1; }
;

ArrType:
	ArrDecl ScalarType {
		$1->formArrayType(NULL, $2);
		$$ = strdup($1->getConstantTypeCString());
	}
;

ArrDecl:
	ARRAY INT_LITERAL OF {
		$$ = new ConstantValueNode(@2.first_line, @2.first_column, "", 5);
		$$->formArrayType($2, NULL);
	}
	|
	ArrDecl ARRAY INT_LITERAL OF {
		$1->formArrayType($3, NULL);
		$$ = $1;
	}
;

LiteralConstant:
	NegOrNot IntegerAndReal {
		if($1){
			std::string val = $2->getValueCString();
			val = "-" + val;
			$$ = new ConstantValueNode(@1.first_line, @1.first_column, val.c_str(), $2->getConstTypeCODE());
		}
		else{
			$$ = $2;
		}
	}
	|
	StringAndBoolean { $$ = $1; }
;

NegOrNot:
	Epsilon { $$ = NULL; }
	|
	MINUS %prec UNARY_MINUS { $$ = strdup("-"); }
;

StringAndBoolean:
	STRING_LITERAL { $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1, 3); }
	|
	TRUE { $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1, 0); }
	|
	FALSE { $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1, 0); }
;

IntegerAndReal:
	INT_LITERAL { $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1, 1); }
	|
	REAL_LITERAL { $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1, 2); }
;

	/*
	   Statements
				  */

Statement:
	CompoundStatement { $$ = $1; }
	|
	Simple { $$ = $1; }
	|
	Condition { $$ = $1; }
	|
	While { $$ = $1; }
	|
	For { $$ = $1; }
	|
	Return { $$ = $1; }
	|
	FunctionCall { $$ = $1; }
;

CompoundStatement:
	BEGIN_ DeclarationList StatementList END { $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3); }
;

Simple:
	VariableReference ASSIGN Expression SEMICOLON { $$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3); }
	|
	PRINT Expression SEMICOLON { $$ = new PrintNode(@1.first_line, @1.first_column, $2); }
	|
	READ VariableReference SEMICOLON { $$ = new ReadNode(@1.first_line, @1.first_column, $2); }
;

VariableReference:
	ID ArrRefList {
		if($2){
			$$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, $2);
		}
		else{
			$$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, NULL);
		}
		free($1);
	}
;

ArrRefList:
	Epsilon { $$ = NULL; }
	|
	ArrRefs { $$ = $1; }
;

ArrRefs:
	L_BRACKET Expression R_BRACKET { $$ = new std::vector<ExpressionNode*>(); $$->push_back($2); }
	|
	ArrRefs L_BRACKET Expression R_BRACKET { $1->push_back($3); $$ = $1; }
;

Condition:
	IF Expression THEN CompoundStatement ElseOrNot END IF {
		if($5){
			$$ = new IfNode(@1.first_line, @1.first_column, $2, $4, $5);
		}
		else{
			$$ = new IfNode(@1.first_line, @1.first_column, $2, $4, NULL);
		}
	}
;

ElseOrNot:
	ELSE CompoundStatement { $$ = $2; }
	|
	Epsilon { $$ = NULL; }
;

While:
	WHILE Expression DO CompoundStatement END DO { $$ = new WhileNode(@1.first_line, @1.first_column, $2, $4); }
;

For:
	FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
	CompoundStatement END DO {
		std::vector<VariableNode*> *VarList = new std::vector<VariableNode*>();
		VarList->push_back(new VariableNode(@2.first_line, @2.first_column, $2, "integer", NULL));
		DeclNode *it = new DeclNode(@2.first_line, @2.first_column, VarList, "integer");

		VariableReferenceNode *itRef = new VariableReferenceNode(@2.first_line, @2.first_column, $2, NULL);
		ConstantValueNode *valBegin = new ConstantValueNode(@4.first_line, @4.first_column, $4, 1);
		AssignmentNode *itAssign = new AssignmentNode(@3.first_line, @3.first_column, itRef, valBegin);

		ConstantValueNode *valEnd = new ConstantValueNode(@6.first_line, @6.first_column, $6, 1);

		$$ = new ForNode(@1.first_line, @1.first_column, it, itAssign, valEnd, $8);
		free($2);
	}
;

Return:
	RETURN Expression SEMICOLON { $$ = new ReturnNode(@1.first_line, @1.first_column, $2); }
;

FunctionCall:
	FunctionInvocation SEMICOLON { $$ = $1; }
;

FunctionInvocation:
	ID L_PARENTHESIS ExpressionList R_PARENTHESIS { 
		$$ = new FunctionInvocationNode(@1.first_line, @1.first_column, $1, $3);
		free($1);
	}
;

ExpressionList:
	Epsilon { $$ = NULL; }
	|
	Expressions { $$ = $1; }
;

Expressions:
	Expression { $$ = new std::vector<ExpressionNode*>(); $$->push_back($1); }
	|
	Expressions COMMA Expression { $1->push_back($3); $$ = $1; }
;

StatementList:
	Epsilon { $$ = NULL; }
	|
	Statements { $$ = $1; }
;

Statements:
	Statement { $$ = new std::vector<AstNode*>(); $$->push_back($1); }
	|
	Statements Statement { $1->push_back($2); $$ = $1; }
;

Expression:
	L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2; }
	|
	MINUS Expression %prec UNARY_MINUS { $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, strdup("neg"), $2); }
	|
	Expression MULTIPLY Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("*"), $1, $3); }
	|
	Expression DIVIDE Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("/"), $1, $3); }
	|
	Expression MOD Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("mod"), $1, $3); }
	|
	Expression PLUS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("+"), $1, $3); }
	|
	Expression MINUS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("-"), $1, $3); }
	|
	Expression LESS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("<"), $1, $3); }
	|
	Expression LESS_OR_EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("<="), $1, $3); }
	|
	Expression GREATER Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup(">"), $1, $3); }
	|
	Expression GREATER_OR_EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup(">="), $1, $3); }
	|
	Expression EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("="), $1, $3); }
	|
	Expression NOT_EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("<>"), $1, $3); }
	|
	NOT Expression { $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, strdup("not"), $2); }
	|
	Expression AND Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("and"), $1, $3); }
	|
	Expression OR Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, strdup("or"), $1, $3); }
	|
	IntegerAndReal { $$ = $1; }
	|
	StringAndBoolean { $$ = $1; }
	|
	VariableReference { $$ = $1; }
	|
	FunctionInvocation { $$ = $1; }
;

	/*
	   misc
			*/
Epsilon:
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
	if (argc < 2) {
		fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
		exit(-1);
	}

	yyin = fopen(argv[1], "r");
	assert(yyin != NULL && "fopen() fails.");

	yyparse();

	if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
		// root->print();
		root->accept(p_vistor);
	}

	printf("\n"
		   "|--------------------------------|\n"
		   "|  There is no syntactic error!  |\n"
		   "|--------------------------------|\n");

	delete root;
	fclose(yyin);
	yylex_destroy();
	return 0;
}
