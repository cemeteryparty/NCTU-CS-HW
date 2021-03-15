#include "AST/for.hpp"

// VER.Heart-Under-Blade
ForNode::ForNode(const uint32_t line, const uint32_t col,
	DeclNode *decl, AssignmentNode *assign, ExpressionNode *expr,
	CompoundStatementNode *cmpd_stmt)
    : AstNode{line, col}, decl(decl), assign(assign), expr(expr), cmpd_stmt(cmpd_stmt) {}

void ForNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(decl){
		decl->accept(p_visitor);
	}
	if(assign){
		assign->accept(p_visitor);
	}
	if(expr){
		expr->accept(p_visitor);
	}
	if(cmpd_stmt){
		cmpd_stmt->accept(p_visitor);
	}
}
