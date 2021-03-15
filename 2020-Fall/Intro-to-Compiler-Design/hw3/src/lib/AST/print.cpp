#include "AST/print.hpp"

// VER.Heart-Under-Blade
PrintNode::PrintNode(const uint32_t line, const uint32_t col, ExpressionNode *display)
	: AstNode{line, col}, display(display) {}

void PrintNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(display){
		display->accept(p_visitor);	
	}
}