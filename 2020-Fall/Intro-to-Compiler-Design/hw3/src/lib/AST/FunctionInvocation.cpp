#include "AST/FunctionInvocation.hpp"

// VER.Heart-Under-Blade
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line, const uint32_t col,
	const char *f_name, std::vector<ExpressionNode*> *parm)
	: ExpressionNode{line, col}, name(f_name), expr_list(parm) {}

void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if(expr_list){
		std::vector<ExpressionNode*> &vr = *expr_list;
		for(unsigned int i = 0; i < vr.size(); i++){
			vr[i]->accept(p_visitor);
		}
	}
}
