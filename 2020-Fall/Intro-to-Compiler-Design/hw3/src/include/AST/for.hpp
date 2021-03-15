#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/assignment.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class ForNode : public AstNode {
public:
	ForNode(const uint32_t line, const uint32_t col,
		DeclNode *decl, AssignmentNode *assign, ExpressionNode *expr,
		CompoundStatementNode *cmpd_stmt);
	~ForNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	DeclNode *decl;
	AssignmentNode *assign;
	ExpressionNode *expr;
	CompoundStatementNode *cmpd_stmt;
};

#endif
