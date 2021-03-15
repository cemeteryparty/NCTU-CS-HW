#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
// VER.Heart-Under-Blade
class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(const uint32_t line, const uint32_t col,
		const char *op_type, ExpressionNode *operand1, ExpressionNode *operand2);
	~BinaryOperatorNode() = default;

	const char *getOperatorCString() const { return op.c_str(); }
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
private:
	const std::string op; // operator
	ExpressionNode *opd_l, *opd_r; // operands 
};

#endif
