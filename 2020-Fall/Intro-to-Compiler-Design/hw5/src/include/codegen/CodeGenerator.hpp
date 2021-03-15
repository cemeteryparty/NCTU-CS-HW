#ifndef __CODE_GENERATOR_H
#define __CODE_GENERATOR_H

#include "sema/SymbolTable.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <map>

class CodeGenerator : public AstNodeVisitor {
public:
	CodeGenerator(const char *in_file_name, const char *out_file_name, SymbolManager *symbol_manager);
	~CodeGenerator();

	void dumpInstrs(const char *format, ...);

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

	int fp_offset = -4; // the first block in frame, fp-4 ~ fp
	int parm_id = 0, label_id = 0;
	bool load_addr = true; // false: load value
	std::map<std::string, int> pos_in_stack;
	int find_pos(std::string index) {
		auto search_result = pos_in_stack.find(index);
		if (search_result != pos_in_stack.end()) {
			return search_result->second;
		}
		return -1; // global var
	}
private:
	const char *in_file_name;
	FILE *out_fp;
	SymbolManager *symbol_manager;
};

#endif