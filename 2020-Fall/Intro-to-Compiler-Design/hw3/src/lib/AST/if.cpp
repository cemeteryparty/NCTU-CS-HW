#include "AST/if.hpp"

// VER.Heart-Under-Blade
IfNode::IfNode(const uint32_t line, const uint32_t col,
	ExpressionNode *condition, CompoundStatementNode *t_stmt, CompoundStatementNode *f_stmt)
	: AstNode{line, col}, condition(condition), t_stmt(t_stmt), f_stmt(f_stmt) {}

void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(condition){
		condition->accept(p_visitor);
	}
	if(t_stmt){
		t_stmt->accept(p_visitor);
	}
	if(f_stmt){
		f_stmt->accept(p_visitor);
	}
}
