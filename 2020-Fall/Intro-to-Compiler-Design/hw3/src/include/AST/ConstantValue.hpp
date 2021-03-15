#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <cstring>
// VER.RetConstCharPtr (Solve Dangling-pointer-dereference error)
class ConstantValueNode : public ExpressionNode {
public:
	ConstantValueNode(const uint32_t line, const uint32_t col, const char *v_const, short int c_type);
	~ConstantValueNode() = default;

	void formArrayType(const char *aoff, const char *atype){ // tricky method, value as type
		if(aoff){
			value += "[";
			value += aoff;
			value += "]";
		}
		if(atype){
			std::string arrType = atype;
			arrType += " ";
			arrType += value;
			value = arrType; 
		}
	}
	const char *getValueCString() const {
		if(ConstType == 2){
			std::string rstr = "";
			int fpprec = -10000;
			for(unsigned int i = 0; i < value.length() && fpprec < 6; i++){
				rstr += value[i];
				fpprec++;
				if(value[i] == '.'){
					fpprec = 0;
				}
			}
			for(int i = 0; i < 6 - fpprec; i++){
				rstr += '0';
			}
			char *ptr = new char[rstr.length() + 1];
			std::strcpy(ptr, rstr.c_str());
			return ptr;
		}
		else{
			return value.c_str();	
		}
	}
	const char *getConstantTypeCString() const {
		if(ConstType == 0)
			return "boolean";
		else if(ConstType == 1)
			return "integer";
		else if(ConstType == 2)
			return "real";
		else if(ConstType == 3)
			return "string";
		else // include array type
			return value.c_str();
	}
	short int getConstTypeCODE(){ return ConstType; }
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

private:
	std::string value;
	short int ConstType;
};

#endif
