#include "AST/function.hpp"

// VER.Heart-Under-Blade
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
	const char *f_name, const char *RetType,
	std::vector<DeclNode*> *declS, CompoundStatementNode *cmpd_stmt)
    : AstNode{line, col}, name(f_name), RetType(RetType), declS(declS), cmpd_stmt(cmpd_stmt) {}

void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(declS){
		std::vector<DeclNode*> &vr = *declS;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
	if(cmpd_stmt){
		cmpd_stmt->accept(p_visitor);
	}
}
