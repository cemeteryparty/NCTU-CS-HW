#ifndef __AST_RETURN_NODE_H
#define __AST_RETURN_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class ReturnNode : public AstNode {
public:
	ReturnNode(const uint32_t line, const uint32_t col, ExpressionNode *retval);
	~ReturnNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	ExpressionNode *retval;
};

#endif
