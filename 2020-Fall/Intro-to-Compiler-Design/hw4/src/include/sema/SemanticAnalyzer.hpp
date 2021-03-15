#ifndef __SEMA_SEMANTIC_ANALYZER_H
#define __SEMA_SEMANTIC_ANALYZER_H

#include "visitor/AstNodeVisitor.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class SymbolEntry{
public:
	std::string Name;
	std::string Kind;
	int Level;
	std::string Type;
	std::string Attr;
	std::string Status;
	SymbolEntry() = default;
	SymbolEntry(std::string name, std::string kind, int lv, std::string type, std::string attr)
		: Name(name), Kind(kind), Level(lv), Type(type), Attr(attr), Status("") {}
	SymbolEntry(std::string name, std::string kind, int lv, std::string type, std::string attr, std::string status)
		: Name(name), Kind(kind), Level(lv), Type(type), Attr(attr), Status(status) {}
	~SymbolEntry() = default;
};
class SymbolTable{
public:
	std::vector<SymbolEntry> content;
	SymbolTable() = default;
	~SymbolTable() = default;
	void dumpDemarcation(const char chr){
		for(size_t i = 0; i < 110; i++) 
			printf("%c", chr);
		printf("\n");
	}
	void dumpTable(int option){
		if(!option)
			return;
		dumpDemarcation('=');
		printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type", "Attribute");
		dumpDemarcation('-');
		for(size_t i = 0; i < content.size(); i++){
			if(content[i].Kind == "DummyScope")
				continue;
			printf("%-33s", content[i].Name.c_str());
			printf("%-11s", content[i].Kind.c_str());
			if(content[i].Level)
				printf("%d%-10s", content[i].Level, "(local)");
			else
				printf("%d%-10s", 0, "(global)");
			printf("%-17s", content[i].Type.c_str());
			printf("%-11s\n", content[i].Attr.c_str());
		}
		dumpDemarcation('-');
	}
};

class Expression {
public:
	std::string type;
	int line, col;
	Expression() = default;
	Expression(std::string type, int line, int col)
		: type(type), line(line), col(col) {}
};
class SemanticAnalyzer : public AstNodeVisitor {
public:
	SemanticAnalyzer() = default;
	~SemanticAnalyzer() = default;

	void visit(ProgramNode &p_program) override;
	void visit(DeclNode &p_decl) override;
	void visit(VariableNode &p_variable) override;
	void visit(ConstantValueNode &p_constant_value) override;
	void visit(FunctionNode &p_function) override;
	void visit(CompoundStatementNode &p_compound_statement) override;
	void visit(PrintNode &p_print) override;
	void visit(BinaryOperatorNode &p_bin_op) override;
	void visit(UnaryOperatorNode &p_un_op) override;
	void visit(FunctionInvocationNode &p_func_invocation) override;
	void visit(VariableReferenceNode &p_variable_ref) override;
	void visit(AssignmentNode &p_assignment) override;
	void visit(ReadNode &p_read) override;
	void visit(IfNode &p_if) override;
	void visit(WhileNode &p_while) override;
	void visit(ForNode &p_for) override;
	void visit(ReturnNode &p_return) override;

	void getProgCode(std::string filename){
		std::ifstream in(filename.c_str());
		progcode.push_back("");
		std::string str;
		while (std::getline(in, str)){
			progcode.push_back(str);
		}
		in.close();
	}
	void dumpSTDERR(int line, int col){
		std::cerr << "    " << progcode[line] << '\n';
		for(int i = 0; i < col + 3; i++)
			std::cerr << ' ';
		std::cerr << "^\n";
	}
	std::string TypeCombine(std::string left, std::string right){
		std::string retType = "ERROR";
		if(left == right)
			retType = left;
		else if(left == "ANY")
			retType = right;
		else if(right == "ANY")
			retType = left;
		else if((left == "integer" && right == "real") || (right == "integer" && left == "real"))
			retType = "real";

		return retType;
	}

	std::vector<SymbolTable> tb_stack;
	std::vector<std::string> progcode;
	bool IsWriteValid = false, func_cmpd_quota = false;
	std::vector<Expression> type_stack;
};

#endif
