#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include "AST/ast.hpp"
#include "AST/variable.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <vector>
// VER.Heart-Under-Blade
class DeclNode : public AstNode {
public:
	DeclNode(const uint32_t line, const uint32_t col, 
		std::vector<VariableNode*> *var_list, const char *decl_type);
	~DeclNode() = default;

	std::string getDeclTypeCString() { return decl_type; }
	int getVarSLength() { return var_list->size(); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

private:
	std::vector<VariableNode*> *var_list; // variables
	const std::string decl_type;
};

#endif
