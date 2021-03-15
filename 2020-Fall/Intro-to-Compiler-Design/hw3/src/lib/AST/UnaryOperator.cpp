#include "AST/UnaryOperator.hpp"

// VER.Heart-Under-Blade
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col,
	const char *op_type, ExpressionNode *operand)
    : ExpressionNode{line, col}, op(op_type), opd(operand) {}

void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(opd){
		opd->accept(p_visitor);	
	}
}
