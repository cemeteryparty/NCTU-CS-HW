#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class IfNode : public AstNode {
public:
	IfNode(const uint32_t line, const uint32_t col,
		ExpressionNode *condition, CompoundStatementNode *t_stmt, CompoundStatementNode *f_stmt);
	~IfNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	ExpressionNode *condition;
	CompoundStatementNode *t_stmt, *f_stmt;
};

#endif
