#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <vector>
// VER.Heart-Under-Blade
class FunctionInvocationNode : public ExpressionNode {
public:
	FunctionInvocationNode(const uint32_t line, const uint32_t col,
		const char *f_name, std::vector<ExpressionNode*> *parm);
	~FunctionInvocationNode() = default;

	const char *getNameCString() const { return name.c_str(); }
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

private:
	const std::string name;
	std::vector<ExpressionNode*> *expr_list;
};

#endif
