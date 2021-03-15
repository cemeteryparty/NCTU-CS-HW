#include "AST/program.hpp"

// VER.Heart-Under-Blade
ProgramNode::ProgramNode(const uint32_t line, const uint32_t col, const char *p_name,
	std::vector<DeclNode*> *declS, std::vector<FunctionNode*> *funcS, CompoundStatementNode *cmpd_stmt)
	: AstNode{line, col}, name(p_name), declS(declS), funcS(funcS), cmpd_stmt(cmpd_stmt) {}

void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(declS){
		std::vector<DeclNode*> &vr = *declS;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
	if(funcS){
		std::vector<FunctionNode*> &vr = *funcS;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
	if(cmpd_stmt){
		cmpd_stmt->accept(p_visitor);
	}
}

