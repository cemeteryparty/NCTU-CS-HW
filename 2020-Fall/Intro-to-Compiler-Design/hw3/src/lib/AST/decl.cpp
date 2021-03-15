#include "AST/decl.hpp"

// VER.Heart-Under-Blade
DeclNode::DeclNode(const uint32_t line, const uint32_t col, 
	std::vector<VariableNode*> *var_list, const char *decl_type)
	: AstNode{line, col}, var_list(var_list), decl_type(decl_type) {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(var_list){
		std::vector<VariableNode*> &vr = *var_list;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
}
