#include "AST/return.hpp"

// VER.Heart-Under-Blade
ReturnNode::ReturnNode(const uint32_t line, const uint32_t col, ExpressionNode *retval)
	: AstNode{line, col}, retval(retval) {}

void ReturnNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(retval){
		retval->accept(p_visitor);
	}
}
