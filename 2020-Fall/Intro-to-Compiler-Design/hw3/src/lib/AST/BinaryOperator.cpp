#include "AST/BinaryOperator.hpp"

// VER.Heart-Under-Blade
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col,
	const char *op_type, ExpressionNode *operand1, ExpressionNode *operand2)
	: ExpressionNode{line, col}, op(op_type), opd_l(operand1), opd_r(operand2) {}

void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(opd_l){
		opd_l->accept(p_visitor);
	}
	if(opd_r){
		opd_r->accept(p_visitor);
	}
}
