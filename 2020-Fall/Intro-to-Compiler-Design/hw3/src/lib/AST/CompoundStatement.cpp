#include "AST/CompoundStatement.hpp"

// VER.Heart-Under-Blade
CompoundStatementNode::CompoundStatementNode(const uint32_t line, const uint32_t col, 
	std::vector<DeclNode*> *declS, std::vector<AstNode*> *stmtS)
	: AstNode{line, col}, declS(declS), stmtS(stmtS) {}

void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(declS){
		std::vector<DeclNode*> &vr = *declS;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
	if(stmtS){
		std::vector<AstNode*> &vr = *stmtS;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
}
