#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class WhileNode : public AstNode {
public:
	WhileNode(const uint32_t line, const uint32_t col,
		ExpressionNode *condition, CompoundStatementNode *cmpd_stmt);
	~WhileNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	ExpressionNode *condition;
	CompoundStatementNode *cmpd_stmt;
};

#endif
