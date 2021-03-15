#include "AST/VariableReference.hpp"

// VER.Heart-Under-Blade
VariableReferenceNode::VariableReferenceNode(const uint32_t line, const uint32_t col,
	const char *vr_name, std::vector<ExpressionNode*> *offsets)
	: ExpressionNode{line, col}, name(vr_name), offset_list(offsets) {}

void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(offset_list){
		std::vector<ExpressionNode*> &vr = *offset_list;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
		// for(auto &expr : offset_list)
		//	expr->accept(p_visitor);
	}
}
