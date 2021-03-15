#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class VariableNode : public AstNode {
public:
	VariableNode(const uint32_t line, const uint32_t col, 
		const char *v_name, const char *v_type, ConstantValueNode *constval);
	~VariableNode() = default;
	void updateNode(const char *v_type, ConstantValueNode *cv_node){
		if(v_type){
			VarType = v_type;
		}
		if(cv_node){
			constval = cv_node;
		}
	}

	const char *getNameCString() const { return name.c_str(); }
	const char *getVariableTypeCString(){ return VarType.c_str(); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

private:
	const std::string name; // variable name, type
	std::string VarType;
	ConstantValueNode *constval; // constant value
};

#endif
