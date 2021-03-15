#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <vector>
// VER.Heart-Under-Blade
class VariableReferenceNode : public ExpressionNode {
public:
	// array reference
	VariableReferenceNode(const uint32_t line, const uint32_t col,
		const char *vr_name, std::vector<ExpressionNode*> *offsets);
	// normal reference
	// VariableReferenceNode(const uint32_t line, const uint32_t col, const char *vr_name);
	~VariableReferenceNode() = default;
	
	const char *getNameCString() const { return name.c_str(); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

private:
	const std::string name;
	std::vector<ExpressionNode*> *offset_list;
};

#endif
