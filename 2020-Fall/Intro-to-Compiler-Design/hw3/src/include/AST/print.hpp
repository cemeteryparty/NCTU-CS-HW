#ifndef __AST_PRINT_NODE_H
#define __AST_PRINT_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
// VER.Heart-Under-Blade
class PrintNode : public AstNode {
public:
	PrintNode(const uint32_t line, const uint32_t col, ExpressionNode *display);
	~PrintNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	ExpressionNode *display;
};

#endif
