#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"
#include <iostream>
#include <memory>
#include <vector>

class VariableReferenceNode : public ExpressionNode {
public:
	typedef std::vector<std::unique_ptr<ExpressionNode>> Exprs;

	VariableReferenceNode(const uint32_t line, const uint32_t col, const char *p_name);
	VariableReferenceNode(const uint32_t line, const uint32_t col, const char *p_name, Exprs *p_indices);
	~VariableReferenceNode() = default;

	const char *getNameCString() const;
	int getSubscriptLength(){
		return (int)indices.size();
	}
	std::string getType(std::string varType){
		std::string retType;
		int count_arr_subscript = (int)indices.size();
		bool drop = false;
		for(size_t i = 0; i < varType.length(); i++){
			if(varType[i] == '[' && count_arr_subscript > 0)
				drop = true;
			else if(varType[i] == ']' && count_arr_subscript > 0){
				count_arr_subscript--;
				drop = false;
			}
			else if(!drop)
				retType += varType[i];
		}
		if(retType.back() == ' ')
			retType.pop_back();
		if(count_arr_subscript > 0)
			retType = "ANY"; // OverArraySubscript
		
		return retType;
	}
	void accept(AstNodeVisitor &p_visitor) override;
	void visitChildNodes(AstNodeVisitor &p_visitor) override;

private:
	const std::string name;
	Exprs indices;
};

#endif
