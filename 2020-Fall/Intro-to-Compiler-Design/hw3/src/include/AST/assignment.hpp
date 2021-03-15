#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/VariableReference.hpp"
#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class AssignmentNode : public AstNode {
public:
	AssignmentNode(const uint32_t line, const uint32_t col,
		VariableReferenceNode *lhs, ExpressionNode *rhs);
	~AssignmentNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	VariableReferenceNode *lhs;
	ExpressionNode *rhs;
};

#endif
