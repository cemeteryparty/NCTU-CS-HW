#include "AST/read.hpp"

// VER.Heart-Under-Blade
ReadNode::ReadNode(const uint32_t line, const uint32_t col, VariableReferenceNode *varref)
    : AstNode{line, col}, varref(varref) {}

void ReadNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(varref){
		varref->accept(p_visitor);	
	}
}
