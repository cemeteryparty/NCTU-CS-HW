#include "AST/while.hpp"

// VER.Heart-Under-Blade
WhileNode::WhileNode(const uint32_t line, const uint32_t col,
	ExpressionNode *condition, CompoundStatementNode *cmpd_stmt)
	: AstNode{line, col}, condition(condition), cmpd_stmt(cmpd_stmt) {}

void WhileNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(condition){
		condition->accept(p_visitor);
	}
	if(cmpd_stmt){
		cmpd_stmt->accept(p_visitor);
	}
}
