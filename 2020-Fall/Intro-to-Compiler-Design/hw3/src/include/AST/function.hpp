#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/variable.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <cstring>
#include <vector>
// VER.RetConstCharPtr (Solve Dangling-pointer-dereference error)
class FunctionNode : public AstNode {
public:
	FunctionNode(const uint32_t line, const uint32_t col,
		const char *f_name, const char *RetType,
		std::vector<DeclNode*> *declS, CompoundStatementNode *cmpd_stmt);
	~FunctionNode() = default;

	const char *getNameCString() const { return name.c_str(); }
	const char *getPrototypeCString() {// boolean (integer, integer, string)
		std::vector<std::string> form_arg_type;
		std::string Prototype = RetType;
		Prototype += " (";
		if(declS){
			std::vector<DeclNode*> &vr = *declS;
			for(unsigned int i = 0; i < vr.size(); i++){
				for(int j = 0; j < (vr[i])->getVarSLength(); j++){
					form_arg_type.push_back(vr[i]->getDeclTypeCString());
				}
			}
			Prototype += form_arg_type[0];
			for(unsigned int i = 1; i < form_arg_type.size(); i++){
				Prototype += (", " + form_arg_type[i]);
			}
		}
		Prototype += ")";
		char *ptr = new char[Prototype.length() + 1];
		std::strcpy(ptr, Prototype.c_str());
		return ptr;
	}
	void visitChildNodes(AstNodeVisitor &p_visitor);
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
private:
	const std::string name, RetType;
	std::vector<DeclNode*> *declS;
	CompoundStatementNode *cmpd_stmt;
};

#endif
