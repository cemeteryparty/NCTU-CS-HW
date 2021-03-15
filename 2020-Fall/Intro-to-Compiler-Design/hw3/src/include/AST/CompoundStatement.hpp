#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <vector>
// VER.Heart-Under-Blade
class CompoundStatementNode : public AstNode {
public:
	CompoundStatementNode(const uint32_t line, const uint32_t col, 
		std::vector<DeclNode*> *declS, std::vector<AstNode*> *stmtS);
	~CompoundStatementNode() = default;

	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	std::vector<DeclNode*> *declS; // DeclarationList
	std::vector<AstNode*> *stmtS; // StatementList
};

#endif
