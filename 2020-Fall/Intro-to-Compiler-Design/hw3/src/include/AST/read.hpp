#ifndef __AST_READ_NODE_H
#define __AST_READ_NODE_H

#include "AST/ast.hpp"
#include "AST/VariableReference.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class ReadNode : public AstNode {
public:
	ReadNode(const uint32_t line, const uint32_t col, VariableReferenceNode *varref);
	~ReadNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	VariableReferenceNode *varref;
};

#endif
