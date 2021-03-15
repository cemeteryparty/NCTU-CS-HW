#include "codegen/CodeGenerator.hpp"
#include "visitor/AstNodeInclude.hpp"

#include <cassert>
#include <cstdarg>
#include <cstdio>

static const char *kKindStrings[] = {"program",  "function", "parameter", "variable", "loop_var", "constant"};
CodeGenerator::CodeGenerator(const char *in_file_name, const char *out_file_name, SymbolManager *symbol_manager) 
	: in_file_name(in_file_name), symbol_manager(symbol_manager) {
	this->out_fp = fopen(out_file_name, "w");
	assert(this->out_fp != NULL && "fopen() fails");
}

CodeGenerator::~CodeGenerator() {
	fclose(this->out_fp);
}

void CodeGenerator::dumpInstrs(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(this->out_fp, format, args);
	va_end(args);
}

void CodeGenerator::visit(ProgramNode &p_program) {
	// Reconstruct the hash table for looking up the symbol entry
	// Hint: Use symbol_manager->lookup(symbol_name) to get the symbol entry.
	symbol_manager->reconstructHashTableFromSymbolTable(p_program.getSymbolTable());

	// Generate RISC-V instructions for program header
	dumpInstrs("    .file \"%s\"\n    .option nopic\n", this->in_file_name);

	for (auto &decl : p_program.var_decls) {
		decl->accept(*this);
	}

	for (auto &func : p_program.funcs) {
		pos_in_stack.clear();
		fp_offset = -4; // new frame
		// function prologue
		dumpInstrs(".section    .text\n    .align 2\n    .globl %s\n", func->getNameCString());
		dumpInstrs("    .type %s, @function\n%s:\n", func->getNameCString(), func->getNameCString());
		dumpInstrs("    addi sp, sp, -128\n    sw ra, 124(sp)\n");
		dumpInstrs("    sw s0, 120(sp)\n    addi s0, sp, 128\n"); fp_offset -= 8;
		dumpInstrs("\n");
		func->accept(*this); // function parmS & body
		dumpInstrs("\n");
		// function epilogue
		dumpInstrs("    lw ra, 124(sp)\n    lw s0, 120(sp)\n");
		dumpInstrs("    addi sp, sp, 128\n    jr ra\n");
		dumpInstrs("    .size %s, .-%s\n", func->getNameCString(), func->getNameCString());
	}

	// main function prologue
	pos_in_stack.clear();
	fp_offset = -4; // new frame
	dumpInstrs(".section    .text\n    .align 2\n    .globl main\n");
	dumpInstrs("    .type main, @function\nmain:\n");
	dumpInstrs("    addi sp, sp, -128\n    sw ra, 124(sp)\n");
	dumpInstrs("    sw s0, 120(sp)\n    addi s0, sp, 128\n"); fp_offset -= 8;
	dumpInstrs("\n");
	p_program.body->accept(*this); // main function body
	// main function epilogue
	dumpInstrs("\n");
	dumpInstrs("    lw ra, 124(sp)\n    lw s0, 120(sp)\n");
	dumpInstrs("    addi sp, sp, 128\n    jr ra\n    .size main, .-main\n");

	// Remove the entries in the hash table
	symbol_manager->removeSymbolsFromHashTable(p_program.getSymbolTable());
}

void CodeGenerator::visit(DeclNode &p_decl) {
	p_decl.visitChildNodes(*this);
}

void CodeGenerator::visit(VariableNode &p_variable) {
	const SymbolEntry *se = symbol_manager->lookup(p_variable.getName());
	std::string sekind = kKindStrings[static_cast<uint32_t>(se->getKind())];
	unsigned long selv = se->getLevel();
	if (selv == 0) { // global
		if(sekind == "variable"){
			dumpInstrs(".comm %s, 4, 4\n", se->getNameCString());
		}
		else if(sekind == "constant"){
			dumpInstrs(".section    .rodata\n    .align 2\n    .globl %s\n    .type %s, @object\n", 
				se->getNameCString(), se->getNameCString());
			dumpInstrs("%s:\n    .word %s\n", 
				se->getNameCString(), p_variable.getConstantPtr()->getConstantValueCString());
		}
	}
	else { // local
		int variable_size = 1;
		pos_in_stack[p_variable.getName()] = fp_offset;
		// case ARRAY: suppose no global array
		std::vector<uint64_t> dim_t = p_variable.type->getDimensions();
		for (int i = 0; i < (int)dim_t.size(); i++){ variable_size *= ((int)dim_t[i]); }
		if (sekind == "constant") {
			dumpInstrs("    addi t0, s0, %d\n", fp_offset);
			dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
			p_variable.constant->accept(*this);
			dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
			dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
			dumpInstrs("    sw t0, 0(t1)\n");
		}
		else if (sekind == "parameter") {
			variable_size = 1;
			if (parm_id >= 8) {
				dumpInstrs("    lw t0, %d(s0)\n", (parm_id - 8) * 4);
				dumpInstrs("    sw t0, %d(s0)\n", fp_offset); 
			}
			else { dumpInstrs("    sw a%d, %d(s0)\n", parm_id, fp_offset); }
			parm_id++;
		}
		else { // sekind == "variable" or "loop_var"
			dumpInstrs("    addi t0, s0, %d\n", fp_offset);
			dumpInstrs("    sw t0, %d(s0)\n", fp_offset);
		}
		fp_offset -= 4;
		for (int i = 0; i < (int)dim_t.size(); i++) {
			dumpInstrs("    li t0, %d\n", (int)dim_t[i]);
			dumpInstrs("    sw t0, %d(s0)\n", fp_offset);
			fp_offset -= 4;
		}
		if (variable_size > 1) { fp_offset -= (4 * variable_size); }
	}
}

void CodeGenerator::visit(ConstantValueNode &p_constant_value) {
	std::string value = p_constant_value.getConstantValueCString();
	if (value == "true") { value = "1"; }
	else if ( value == "false" ) { value = "0"; }
	dumpInstrs("    li t0, %s\n", value.c_str());
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of expr
}

void CodeGenerator::visit(FunctionNode &p_function) {
	// Reconstruct the hash table for looking up the symbol entry
	symbol_manager->reconstructHashTableFromSymbolTable(p_function.getSymbolTable());

	parm_id = 0;
	for (auto &parameter : p_function.parameters) {
		parameter->accept(*this);
	}
	if (p_function.body) {
		p_function.body->accept(*this);
	}

	// Remove the entries in the hash table
	symbol_manager->removeSymbolsFromHashTable(p_function.getSymbolTable());
}

void CodeGenerator::visit(CompoundStatementNode &p_compound_statement) {
	// Reconstruct the hash table for looking up the symbol entry
	symbol_manager->reconstructHashTableFromSymbolTable(p_compound_statement.getSymbolTable());
	
	p_compound_statement.visitChildNodes(*this);

	// Remove the entries in the hash table
	symbol_manager->removeSymbolsFromHashTable(p_compound_statement.getSymbolTable());
}

void CodeGenerator::visit(PrintNode &p_print) {
	load_addr = false;
	p_print.visitChildNodes(*this);
	load_addr = true;
	dumpInstrs("    lw a0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    jal ra, printInt\n");
}

void CodeGenerator::visit(BinaryOperatorNode &p_bin_op) {
	load_addr = false;
	p_bin_op.left->accept(*this);
	load_addr = false; // accept left may change to "true"
	p_bin_op.right->accept(*this);
	load_addr = true;
	
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	std::string op = p_bin_op.getOpCString();
	bool compare = false;
	if (op == "+") { dumpInstrs("    add t0, t1, t0\n"); }
	else if (op == "-") { dumpInstrs("    sub t0, t1, t0\n"); }
	else if (op == "*") { dumpInstrs("    mul t0, t1, t0\n"); }
	else if (op == "/") { dumpInstrs("    div t0, t1, t0\n"); }
	else if (op == "mod") { dumpInstrs("    rem t0, t1, t0\n"); }
	else if (op == "and") { dumpInstrs("    and t0, t1, t0\n"); }
	else if (op == "or") { dumpInstrs("    or t0, t1, t0\n"); }
	else if (op == "<") { dumpInstrs("    blt t1, t0, L%dt\n", label_id); compare = true; }
	else if (op == "<=") { dumpInstrs("    ble t1, t0, L%dt\n", label_id); compare = true; }
	else if (op == "=") { dumpInstrs("    beq t1, t0, L%dt\n", label_id); compare = true; }
	else if (op == ">=") { dumpInstrs("    bge t1, t0, L%dt\n", label_id); compare = true; }
	else if (op == ">") { dumpInstrs("    bgt t1, t0, L%dt\n", label_id); compare = true; }
	else if (op == "<>") { dumpInstrs("    bne t1, t0, L%dt\n", label_id); compare = true; }
	else { dumpInstrs("    # what the fuck: \'%s\'\n", p_bin_op.getOpCString()); return; }
	if (compare) {
		dumpInstrs("    li t0, 0\n    j eL%d\n", label_id);
		dumpInstrs("L%dt:\n    li t0, 1\neL%d:\n", label_id, label_id);
		label_id++;
	}
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of expr
}

void CodeGenerator::visit(UnaryOperatorNode &p_un_op) {
	std::string op = p_un_op.getOpCString();
	load_addr = false;
	if (op == "not") { dumpInstrs("    li t0, -1\n"); }
	else if (op == "neg") { dumpInstrs("    li t0, 0\n"); }
	else { dumpInstrs("    # what the fuck: \'%s\'\n", p_un_op.getOpCString()); }
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of left expr
	p_un_op.operand->accept(*this);
	load_addr = true;

	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	if (op == "not") { dumpInstrs("    xor t0, t1, t0\n"); }
	else if (op == "neg") { dumpInstrs("    sub t0, t1, t0\n"); }
	else { dumpInstrs("    # what the fuck: \'%s\'\n", p_un_op.getOpCString()); return; }

	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of expr
}
void CodeGenerator::visit(FunctionInvocationNode &p_func_invocation) {
	// check the argument is called by value of address (array)
	const SymbolEntry *se = symbol_manager->lookup(p_func_invocation.getName());
	const FunctionNode::Decls *parameters = se->getAttribute().parameters();
	std::vector<bool> isPassAddrS;
	for (const auto &parameter : *parameters) {
		for (const auto &var : parameter->getVariables()) {
			isPassAddrS.push_back(!(var->type->getDimensions().empty()));
		}
	}
	//
	int arg_id = 0, n_exceed_arg = 0;
	for (auto &argument : p_func_invocation.arguments) {
		load_addr = isPassAddrS[arg_id];
		argument->accept(*this); // get value of arg
		arg_id++;
	}
	load_addr = true;
		
	if (arg_id > 8) {
		n_exceed_arg = arg_id - 8;
		arg_id = 8;
		dumpInstrs("    add t3, zero, sp\n");
	}
	for (int i = 0; i < n_exceed_arg; i++) { dumpInstrs("    addi sp, sp, 4\n"); }
	while(arg_id--){ dumpInstrs("    lw a%d, 0(sp)\n    addi sp, sp, 4\n", arg_id); }
	for (int i = 0; i < n_exceed_arg; i++) {
		dumpInstrs("    lw t0, 0(t3)\n    addi t3, t3, 4\n");
		dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	}

	dumpInstrs("    jal ra, %s\n    mv t0, a0\n", p_func_invocation.getNameCString());
	for (int i = 0; i < n_exceed_arg; i++) { dumpInstrs("    addi sp, sp, 4\n"); } // pop remain arg
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of expr
}

void CodeGenerator::visit(VariableReferenceNode &p_variable_ref) {
	// offset: length to fp, offset == -1 -> global, ELSE -> local
	int offset = find_pos(p_variable_ref.getName());
	if (load_addr) {
		if (offset == -1) { dumpInstrs("    la t0, %s\n", p_variable_ref.getNameCString()); }
		else { dumpInstrs("    addi t0, s0, %d\n", offset); }
	}
	else {
		if (offset == -1) {
			dumpInstrs("    la t0, %s\n", p_variable_ref.getNameCString());
			dumpInstrs("    lw t1, 0(t0)\n    mv t0, t1\n");
		}
		else { dumpInstrs("    lw t0, %d(s0)\n", offset); }
	}
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n"); // store result of expr
	// Deal with Array Type:
	// before this line, the top of stack is
	//     "the base addr of array type variable reference"
	if (p_variable_ref.indices.empty()) { return; }
	int indice_index = 0;
	for (auto &index : p_variable_ref.indices) {
		index->accept(*this);
		dumpInstrs("    li t0, 4\n");
		dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
		dumpInstrs("    mul t0, t1, t0\n");
		dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
		for (int i = (int)p_variable_ref.indices.size() - indice_index; i >= 2; i--) {
			dumpInstrs("    lw t0, %d(s0)\n", offset - 4 * i);
			dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
			dumpInstrs("    mul t0, t1, t0\n");
			dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
		}
		dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n"); // arr_offset
		dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n"); // array_base_addr
		dumpInstrs("    sub t0, t1, t0\n"); // t0 = array_base_addr + arr_offset
		dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
		indice_index++;
	}
	dumpInstrs("    li t0, %d\n", ((int)p_variable_ref.indices.size() + 1) * 4); // arr_info_space
	dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n"); // array_base_addr + arr_offset
	dumpInstrs("    sub t0, t1, t0\n");

	if (!load_addr) {
		dumpInstrs("    lw t1, 0(t0)\n    mv t0, t1\n"); // t0 = *(array_base_addr + arr_offset) 
	}
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
}

void CodeGenerator::visit(AssignmentNode &p_assignment) {
	p_assignment.lvalue->accept(*this);
	p_assignment.expr->accept(*this); // get expr instrS
	dumpInstrs("    lw t0, 0(sp)\n");
	dumpInstrs("    addi sp, sp, 4\n    lw t1, 0(sp)\n");
	dumpInstrs("    addi sp, sp, 4\n    sw t0, 0(t1)\n");
}

void CodeGenerator::visit(ReadNode &p_read) {
	p_read.visitChildNodes(*this); // get addr
	dumpInstrs("    jal ra, readInt\n    lw t0, 0(sp)\n");
	dumpInstrs("    addi sp, sp, 4\n    sw a0, 0(t0)\n");
}

void CodeGenerator::visit(IfNode &p_if) {
	int lid = label_id++;
	load_addr = false;
	p_if.condition->accept(*this); // branch instrS
	load_addr = true;
	dumpInstrs("    li t0, 1\n    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    beq t1, t0, L%dt\n", lid);
	if (p_if.else_body) { p_if.else_body->accept(*this); } // false behaviour
	dumpInstrs("    j eL%d\n", lid); // jump to label end
	dumpInstrs("L%dt:\n", lid); // label true
	p_if.body->accept(*this); // true behaviour
	dumpInstrs("eL%d:\n", lid); // label end
}

void CodeGenerator::visit(WhileNode &p_while) {
	int lid = label_id++;
	dumpInstrs("L%dh:\n", lid); // label head
	load_addr = false;
	p_while.condition->accept(*this); // branch instrS
	load_addr = true;
	dumpInstrs("    li t0, 1\n    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    beq t1, t0, L%dt\n", lid);
	dumpInstrs("    j eL%d\n", lid); // false behaviour, jump to label end
	dumpInstrs("L%dt:\n", lid); // label true
	p_while.body->accept(*this); // true behaviour
	dumpInstrs("    j L%dh\n", lid); // jump to label head
	dumpInstrs("eL%d:\n", lid); // label end
}

void CodeGenerator::visit(ForNode &p_for) {
	// Reconstruct the hash table for looking up the symbol entry
	symbol_manager->reconstructHashTableFromSymbolTable(p_for.getSymbolTable());
	int lid = label_id++; // no expr node
	std::string loop_var = "";
	const SymbolTable *symbol_table = p_for.getSymbolTable();
	for (const auto &entry_ptr : symbol_table->getEntries()){ loop_var = entry_ptr->getName(); }
	p_for.var_decl->accept(*this); // decl loop_var
	int offset = find_pos(loop_var);

	p_for.initial_statement->accept(*this); // assign loop_var lower_bound
	dumpInstrs("L%dh:\n", lid); // label head
	// branch
	dumpInstrs("    lw t0, %d(s0)\n", offset); 
	dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	p_for.condition->accept(*this);
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    blt t1, t0, L%dt\n", lid);
	//
	dumpInstrs("    j eL%d\n", lid, lid); // false behaviour, jump to label end
	dumpInstrs("L%dt:\n", lid); // label true
	p_for.body->accept(*this); // true behaviour
	// increment loop_var
	dumpInstrs("    addi t0, s0, %d\n", offset); dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    lw t0, %d(s0)\n", offset); dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    li t0, 1\n"); dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    add t0, t1, t0\n"); dumpInstrs("    addi sp, sp, -4\n    sw t0, 0(sp)\n");
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n    lw t1, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    sw t0, 0(t1)\n");
	//
	dumpInstrs("    j L%dh\n", lid); // jump to label head
	dumpInstrs("eL%d:\n", lid); // label end

	// Remove the entries in the hash table
	symbol_manager->removeSymbolsFromHashTable(p_for.getSymbolTable());
}

void CodeGenerator::visit(ReturnNode &p_return) {
	load_addr = false;
	p_return.visitChildNodes(*this); // get return value
	load_addr = true;
	dumpInstrs("    lw t0, 0(sp)\n    addi sp, sp, 4\n");
	dumpInstrs("    mv a0, t0\n");
}
