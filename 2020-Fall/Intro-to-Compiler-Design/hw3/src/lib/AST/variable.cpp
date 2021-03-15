#include "AST/variable.hpp"

// VER.Heart-Under-Blade
VariableNode::VariableNode(const uint32_t line, const uint32_t col, 
	const char *v_name, const char *v_type, ConstantValueNode *constval)
	: AstNode{line, col}, name(v_name), VarType(v_type), constval(constval) {}

void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(constval){
		constval->accept(p_visitor);
	}
}
