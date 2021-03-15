#ifndef __AST_PROGRAM_NODE_H
#define __AST_PROGRAM_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class ProgramNode : public AstNode {
public:
	ProgramNode(const uint32_t line, const uint32_t col, const char *p_name,
		std::vector<DeclNode*> *declS, std::vector<FunctionNode*> *funcS, CompoundStatementNode *cmpd_stmt);
	~ProgramNode() = default;

	const char *getNameCString() const { return name.c_str(); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	const std::string name;
	std::vector<DeclNode*> *declS;
	std::vector<FunctionNode*> *funcS;
	CompoundStatementNode *cmpd_stmt; 
};

#endif
