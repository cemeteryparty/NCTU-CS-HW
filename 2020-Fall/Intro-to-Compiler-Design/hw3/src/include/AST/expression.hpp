#ifndef __AST_EXPRESSION_NODE_H
#define __AST_EXPRESSION_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class ExpressionNode : public AstNode {
public:
	ExpressionNode(const uint32_t line, const uint32_t col);
	~ExpressionNode() = default;

	virtual void accept(class AstNodeVisitor &p_visitor) = 0;
protected:
	// for carrying type of result of an expression
	// TODO: for next assignment
};

#endif
