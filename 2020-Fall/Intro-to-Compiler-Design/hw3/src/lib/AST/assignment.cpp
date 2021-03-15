#include "AST/assignment.hpp"

// VER.Heart-Under-Blade
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,
	VariableReferenceNode *lhs, ExpressionNode *rhs)
	: AstNode{line, col}, lhs(lhs), rhs(rhs) {}

void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(lhs){
		lhs->accept(p_visitor);	
	}
	if(rhs){
		rhs->accept(p_visitor);
	}
}
