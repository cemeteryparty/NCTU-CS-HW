#include "sema/SemanticAnalyzer.hpp"
#include "visitor/AstNodeInclude.hpp"

extern int ERROR_DETECT;
extern int opt_symtable;

void SemanticAnalyzer::visit(ProgramNode &p_program) {
	SymbolTable tb;
	tb_stack.push_back(tb);
	tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry(p_program.getNameCString(), 
		"program", tb_stack.size() - 1, p_program.getTypeCString(), "")); // prog_name
	p_program.visitChildNodes(*this); // decls and func can't get in here
	tb_stack.back().dumpTable(opt_symtable);
	tb_stack.pop_back();
}

void SemanticAnalyzer::visit(DeclNode &p_decl) {
	p_decl.visitChildNodes(*this);
}

void SemanticAnalyzer::visit(VariableNode &p_variable) {
	IsWriteValid = true;
	
	std::string varKind = "variable", varName = p_variable.getNameCString();
	if(tb_stack.size() >= 2 && tb_stack[tb_stack.size() - 2].content.back().Attr == "ForScope"){
		varKind = "loop_var";
		IsWriteValid = false;
	}

	bool RedeclError = false;
	for(int i = (int)tb_stack.size() - 1; i >= 0 && !RedeclError; i--){ // redecl check
		for(int j = 0; j < (int)tb_stack[i].content.size() && !RedeclError; j++){
			if(i == (int)tb_stack.size() - 1){// redecl in same scope
				if(tb_stack[i].content[j].Name == varName)
					RedeclError = true;
			}
			else{
				if(tb_stack[i].content[j].Name == varName && tb_stack[i].content[j].Kind == "loop_var")
					RedeclError = true;
			}
		}
	}
	if(RedeclError){
		IsWriteValid = false;
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_variable.getLocation().line << ", column " 
			<< p_variable.getLocation().col << ": symbol \'" << varName << "\' is redeclared\n";
		this->dumpSTDERR(p_variable.getLocation().line, p_variable.getLocation().col);
	}
	bool VarDeclInvalid = p_variable.isTypeInvaild();
	if(VarDeclInvalid){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_variable.getLocation().line << ", column " << p_variable.getLocation().col 
			<< ": \'" << varName << "\' declared as an array with an index that is not greater than 0\n";
		this->dumpSTDERR(p_variable.getLocation().line, p_variable.getLocation().col);
	}

	if(!RedeclError){
		if(!VarDeclInvalid){ // legal decl
			tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry(p_variable.getNameCString(), 
				varKind, tb_stack.size() - 1, p_variable.getTypeCString(), ""));
		}
		else{
			tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry(p_variable.getNameCString(), 
				varKind, tb_stack.size() - 1, p_variable.getTypeCString(), "", "Invalid"));
		}
	}
	
	p_variable.visitChildNodes(*this);
	IsWriteValid = false;
}

void SemanticAnalyzer::visit(ConstantValueNode &p_constant_value) {
	if(IsWriteValid){
		int index = tb_stack[tb_stack.size() - 1].content.size() - 1;
		tb_stack[tb_stack.size() - 1].content[index].Kind = "constant";
		tb_stack[tb_stack.size() - 1].content[index].Attr = p_constant_value.getConstantValueCString();
	}
	std::string constType = p_constant_value.getTypePtr()->getPTypeCString();
	type_stack.push_back(Expression(constType, p_constant_value.getLocation().line, 
		p_constant_value.getLocation().col));
}

void SemanticAnalyzer::visit(FunctionNode &p_function) {
	std::string varName = p_function.getNameCString();

	bool RedeclError = false;
	for(int i = 0; i < (int)tb_stack.back().content.size() && !RedeclError; i++){
		if(tb_stack.back().content[i].Name == varName)
			RedeclError = true;
	}
	if(RedeclError){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_function.getLocation().line << ", column " 
			<< p_function.getLocation().col << ": symbol \'" << varName << "\' is redeclared\n";
		this->dumpSTDERR(p_function.getLocation().line, p_function.getLocation().col);
	}
	else{ // legal func_name decl
		tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry(varName, "function", 
			tb_stack.size() - 1, p_function.getTypeCString(), p_function.getAttributeCString()));
	}
	
	SymbolTable tb;
	tb_stack.push_back(tb);
	func_cmpd_quota = true;
	p_function.visitChildNodes(*this); // parmS and cmpd_stmt
	for(int i = 0; i < p_function.getParmCount(); i++)
		tb_stack[tb_stack.size() - 1].content[i].Kind = "parameter";
	tb_stack.back().dumpTable(opt_symtable);
	tb_stack.pop_back();
}

void SemanticAnalyzer::visit(CompoundStatementNode &p_compound_statement) {
	if(func_cmpd_quota){
		func_cmpd_quota = false;
		p_compound_statement.visitChildNodes(*this);
	}
	else{
		tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry("DummyScope", "DummyScope", 
			tb_stack.size() - 1, "DummyScope", "DummyScope")); // cmpd_stmt
		SymbolTable tb;
		tb_stack.push_back(tb);
		p_compound_statement.visitChildNodes(*this);
		tb_stack.back().dumpTable(opt_symtable);
		tb_stack.pop_back();
	}
}

void SemanticAnalyzer::visit(PrintNode &p_print) {
	p_print.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression exp = type_stack.back();
	type_stack.pop_back();
	if(exp.type != "integer" && exp.type != "real" && exp.type != "string" 
		&& exp.type != "boolean" && exp.type != "ANY"){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << exp.line << ", column "
			<< exp.col << ": expression of print statement must be scalar type\n";
		this->dumpSTDERR(exp.line, exp.col);
	}
}

void SemanticAnalyzer::visit(BinaryOperatorNode &p_bin_op) {
	bool bin_node_err = false;
	p_bin_op.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression lexp = type_stack[type_stack.size() - 2], rexp = type_stack[type_stack.size() - 1];
	type_stack.pop_back();
	type_stack.pop_back();
	std::string newType = this->TypeCombine(rexp.type, lexp.type), op = p_bin_op.getOpCString();

	if(newType == "ERROR"){
		bin_node_err = true;
		newType = "ANY";
	}
	if(op == "+" || op == "-" || op == "*" || op == "/"){
		if(newType != "integer" && newType != "real" && newType != "ANY")
			bin_node_err = true;
		if(op == "+" && newType == "string")
			bin_node_err = false;
	}
	else if(op == "mod"){
		if(newType != "integer" && newType != "ANY")
			bin_node_err = true;
	}
	else if(op == "and" || op == "or"){
		if(newType != "boolean" && newType != "ANY")
			bin_node_err = true;
	}
	else if(op == "<" || op == "<=" || op == "=" || op == ">=" || op == ">" || op == "<>"){
		if(newType != "integer" && newType != "real" && newType != "ANY")
			bin_node_err = true;
		else if(newType == "integer" || newType == "real")
			newType = "boolean";
	}

	if(bin_node_err){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_bin_op.getLocation().line << ", column "
			<< p_bin_op.getLocation().col << ": invalid operands to binary operator \'"
			<< op << "\' (\'" << lexp.type << "\' and \'" << rexp.type << "\')\n";
		this->dumpSTDERR(p_bin_op.getLocation().line, p_bin_op.getLocation().col);
		newType = "ANY";
	}
	type_stack.push_back(Expression(newType, p_bin_op.getLocation().line, p_bin_op.getLocation().col));
}

void SemanticAnalyzer::visit(UnaryOperatorNode &p_un_op) {
	bool un_node_err = false;
	p_un_op.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression opdexp = type_stack[type_stack.size() - 1];
	type_stack.pop_back();
	std::string newType = this->TypeCombine(opdexp.type, "ANY"), op = p_un_op.getOpCString();

	if(newType == "ERROR"){
		un_node_err = true;
		newType = "ANY";
	}
	if(op == "-"){
		if(newType != "integer" && newType != "real" && newType != "ANY")
			un_node_err = true;
	}
	else if(op == "not"){
		if(newType != "boolean" && newType != "ANY")
			un_node_err = true;
	}

	if(un_node_err){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_un_op.getLocation().line << ", column "
			<< p_un_op.getLocation().col << ": invalid operand to unary operator \'"
			<< op << "\' (\'" << opdexp.type << "\')\n";
		this->dumpSTDERR(p_un_op.getLocation().line, p_un_op.getLocation().col);
		newType = "ANY";
	}
	type_stack.push_back(Expression(newType, p_un_op.getLocation().line, p_un_op.getLocation().col));
}

void SemanticAnalyzer::visit(FunctionInvocationNode &p_func_invocation) {
	std::string varName = p_func_invocation.getNameCString(), varType = "ANY", parmAttr; // from table
	bool UndeclError = true, InvalidFuncCall = false;
	for(size_t i = 0; i < tb_stack.size(); i++)
		for(size_t j = 0; j < tb_stack[i].content.size(); j++){
			if(tb_stack[i].content[j].Name == varName){
				UndeclError = false;
				if(tb_stack[i].content[j].Kind != "function")
					InvalidFuncCall = true;
				varType = tb_stack[i].content[j].Type;
				parmAttr = tb_stack[i].content[j].Attr + ", ";
			}
		}
	std::vector<std::string> parmType;
	std::string tmp = "";
	for(int i = 0; i < (int)parmAttr.length(); i++){
		if(parmAttr[i] == ' ' && parmAttr[i - 1] == ','){
			if(!tmp.empty())
				parmType.push_back(tmp);
			tmp = "";
		}
		else if(parmAttr[i] != ','){
			tmp += parmAttr[i];
		}
	}

	bool func_call_error = false;
	if(UndeclError){
		func_call_error = true;
		std::cerr << "<Error> Found in line " << p_func_invocation.getLocation().line << ", column " 
			<< p_func_invocation.getLocation().col << ": use of undeclared symbol \'" << varName << "\'\n";
		this->dumpSTDERR(p_func_invocation.getLocation().line, p_func_invocation.getLocation().col);
	}
	if(InvalidFuncCall){
		func_call_error = true;
		std::cerr << "<Error> Found in line " << p_func_invocation.getLocation().line << ", column " 
			<< p_func_invocation.getLocation().col << ": call of non-function symbol \'" << varName << "\'\n";
		this->dumpSTDERR(p_func_invocation.getLocation().line, p_func_invocation.getLocation().col);
	}
	bool UnmatchArgNum = ((int)parmType.size() != p_func_invocation.getArgLength());
	if(!(UndeclError | InvalidFuncCall)){
		if(UnmatchArgNum){
			func_call_error = true;
			std::cerr << "<Error> Found in line " << p_func_invocation.getLocation().line << ", column " 
				<< p_func_invocation.getLocation().col << ": too few/much arguments provided for function \'" << varName << "\'\n";
			this->dumpSTDERR(p_func_invocation.getLocation().line, p_func_invocation.getLocation().col);
		}
	}
	p_func_invocation.visitChildNodes(*this);
	// semantic analyses after get info from child
	std::vector<Expression> argType(p_func_invocation.getArgLength());
	for(int i = p_func_invocation.getArgLength() - 1; i >=0 ; i--){
		argType[i] = type_stack.back();
		type_stack.pop_back();
	}
	if(!(UndeclError | InvalidFuncCall | UnmatchArgNum)){
		for(int i = 0; i < (int)argType.size(); i++){
			if(argType[i].type != parmType[i]){
				func_call_error = true;
				std::cerr << "<Error> Found in line " << argType[i].line << ", column "
					<< argType[i].col << ": incompatible type passing \'" << argType[i].type 
					<< "\' to parameter of type \'" << parmType[i] << "\'\n";
				this->dumpSTDERR(argType[i].line, argType[i].col);
			}
		}
	}

	if(func_call_error){
		ERROR_DETECT = 1;
		varType = "ANY";
	}
	type_stack.push_back(Expression(varType, p_func_invocation.getLocation().line, 
		p_func_invocation.getLocation().col)); // function ret type as exp
}

void SemanticAnalyzer::visit(VariableReferenceNode &p_variable_ref) {
	std::string varName = p_variable_ref.getNameCString(), varType = "ANY", varStatus; // from table
	bool UndeclError = true, InvalidVarRef = false;
	for(size_t i = 0; i < tb_stack.size(); i++)
		for(size_t j = 0; j < tb_stack[i].content.size(); j++){
			if(tb_stack[i].content[j].Name == varName){
				UndeclError = false;
				if(tb_stack[i].content[j].Kind == "program" || tb_stack[i].content[j].Kind == "function")
					InvalidVarRef = true;
				varType = tb_stack[i].content[j].Type;
				varStatus = tb_stack[i].content[j].Status;
			}
		}
	std::string varrefType = p_variable_ref.getType(varType);

	bool var_ref_err = false;
	if(UndeclError){
		var_ref_err = true;
		std::cerr << "<Error> Found in line " << p_variable_ref.getLocation().line << ", column " 
			<< p_variable_ref.getLocation().col << ": use of undeclared symbol \'" << varName << "\'\n";
		this->dumpSTDERR(p_variable_ref.getLocation().line, p_variable_ref.getLocation().col);
	}
	if(varStatus == ""){
		if(InvalidVarRef){
			var_ref_err = true;
			std::cerr << "<Error> Found in line " << p_variable_ref.getLocation().line << ", column " 
				<< p_variable_ref.getLocation().col << ": use of non-variable symbol \'" << varName << "\'\n";
			this->dumpSTDERR(p_variable_ref.getLocation().line, p_variable_ref.getLocation().col);
		}
		if(!(UndeclError | InvalidVarRef) & (varrefType == "ANY")){
			var_ref_err = true;
			std::cerr << "<Error> Found in line " << p_variable_ref.getLocation().line << ", column " 
				<< p_variable_ref.getLocation().col << ": there is an over array subscript on \'" << varName << "\'\n";
			this->dumpSTDERR(p_variable_ref.getLocation().line, p_variable_ref.getLocation().col);
		}
	}
	p_variable_ref.visitChildNodes(*this);
	// semantic analyses after get info from child
	std::vector<Expression> indexTypeS(p_variable_ref.getSubscriptLength());
	for(int i = p_variable_ref.getSubscriptLength() - 1; i >=0 ; i--){
		indexTypeS[i] = type_stack.back();
		type_stack.pop_back();
	}
	for(int i = 0; i < p_variable_ref.getSubscriptLength(); i++){
		Expression exp = indexTypeS[i];
		if(exp.type != "integer" && exp.type != "ANY" && varStatus == ""){
			var_ref_err = true;
			std::cerr << "<Error> Found in line " << exp.line << ", column "
				<< exp.col << ": index of array reference must be an integer\n";
			this->dumpSTDERR(exp.line, exp.col);
		}
	}

	if(var_ref_err){
		ERROR_DETECT = 1;
		varrefType = "ANY";
	}
	type_stack.push_back(Expression(varrefType, p_variable_ref.getLocation().line, 
		p_variable_ref.getLocation().col));
}

void SemanticAnalyzer::visit(AssignmentNode &p_assignment) {
	p_assignment.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression lexp = type_stack[type_stack.size() - 2], rexp = type_stack[type_stack.size() - 1];
	type_stack.pop_back();
	type_stack.pop_back();
	std::string codeline = progcode[p_assignment.getLocation().line];

	bool Assign2ArrError = false;
	if(lexp.type != "integer" && lexp.type != "real" && lexp.type != "string" && lexp.type != "boolean" && lexp.type != "ANY"){
		Assign2ArrError = true;
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << lexp.line << ", column "
			<< lexp.col << ": array assignment is not allowed\n";
		this->dumpSTDERR(lexp.line, lexp.col);
	}
	bool Assign2StaticError = false;
	if(!Assign2ArrError){
		std::string tmp = "";
		for(int col = 1; col <= (int)codeline.length(); col++){
			if(codeline[col - 1] != ' ' && codeline[col - 1] != ';')
				tmp += codeline[col - 1];
			else{
				if(!tmp.empty()){
					std::string varKind = "";
					for(size_t i = 0; i < tb_stack.size(); i++){
						for(size_t j = 0; j < tb_stack[i].content.size(); j++)
							if(tb_stack[i].content[j].Name == tmp)
								varKind = tb_stack[i].content[j].Kind;
					}
					if(varKind == "constant"){
						Assign2StaticError = true;
						ERROR_DETECT = 1;
						std::cerr << "<Error> Found in line " << p_assignment.getLocation().line << ", column "
							<< col - tmp.length() << ": cannot assign to variable \'" 
							<< tmp << "\' which is a constant\n";
						this->dumpSTDERR(p_assignment.getLocation().line, col - tmp.length());
						break;
					}
					else if(varKind == "loop_var" && tmp != "for"){
						Assign2StaticError = true;
						ERROR_DETECT = 1;
						std::cerr << "<Error> Found in line " << p_assignment.getLocation().line << ", column "
							<< col - tmp.length() << ": the value of loop variable cannot be modified inside the loop body\n"; 
						this->dumpSTDERR(p_assignment.getLocation().line, col - tmp.length());
						break;
					}
				}
			}
		}
	}
	bool AssignSrcIsArrError = false;
	if(!(Assign2ArrError | Assign2StaticError)){
		if(rexp.type != "integer" && rexp.type != "real" && rexp.type != "string" && rexp.type != "boolean" && rexp.type != "ANY"){
			AssignSrcIsArrError = true;
			ERROR_DETECT = 1;
			std::cerr << "<Error> Found in line " << rexp.line << ", column "
				<< rexp.col << ": array assignment is not allowed\n";
			this->dumpSTDERR(rexp.line, rexp.col);
		}
	}
	if(!(Assign2ArrError | Assign2StaticError | AssignSrcIsArrError)){
		std::string assignType = this->TypeCombine(lexp.type, rexp.type);
		if(assignType == "ERROR"){
			ERROR_DETECT = 1;
			std::cerr << "<Error> Found in line " << p_assignment.getLocation().line << ", column "
				<< p_assignment.getLocation().col << ": assigning to \'" << lexp.type 
				<< "\' from incompatible type \'" << rexp.type <<  "\'\n";
			this->dumpSTDERR(p_assignment.getLocation().line, p_assignment.getLocation().col);
		}
	}
}

void SemanticAnalyzer::visit(ReadNode &p_read) {
	p_read.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression exp = type_stack.back();
	type_stack.pop_back();

	if(exp.type != "integer" && exp.type != "real" && exp.type != "string" && exp.type != "boolean" && exp.type != "ANY"){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << exp.line << ", column "
			<< exp.col << ": variable reference of read statement must be scalar type\n";
		this->dumpSTDERR(exp.line, exp.col);
	}
	else{
		std::string codeline = progcode[p_read.getLocation().line];
		int col = 0;
		std::string tmp = "";
		for(col = codeline.find("read") + 5; col <= (int)codeline.length(); col++){
			if(codeline[col - 1] != ' ' && codeline[col - 1] != ';')
				tmp += codeline[col - 1];
			else{
				if(!tmp.empty()){
					std::string varKind = "";
					for(size_t i = 0; i < tb_stack.size(); i++){
						for(size_t j = 0; j < tb_stack[i].content.size(); j++)
							if(tb_stack[i].content[j].Name == tmp)
								varKind = tb_stack[i].content[j].Kind;
					}
					if(varKind == "constant" || varKind == "loop_var"){
						ERROR_DETECT = 1;
						std::cerr << "<Error> Found in line " << p_read.getLocation().line << ", column "
							<< col - tmp.length() << ": variable reference of read statement cannot be a constant or loop variable\n";
						this->dumpSTDERR(p_read.getLocation().line, col - tmp.length());
					}
				}
				tmp = "";
			}
		}
	}
}

void SemanticAnalyzer::visit(IfNode &p_if) {
	p_if.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression exp = type_stack.back();
	type_stack.pop_back();

	if(exp.type != "boolean" && exp.type != "ANY"){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << exp.line << ", column "
			<< exp.col << ": the expression of condition must be boolean type\n";
		this->dumpSTDERR(exp.line, exp.col);
	}
}

void SemanticAnalyzer::visit(WhileNode &p_while) {
	p_while.visitChildNodes(*this);
	// semantic analyses after get info from child
	Expression exp = type_stack.back();
	type_stack.pop_back();
	if(exp.type != "boolean" && exp.type != "ANY"){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << exp.line << ", column "
			<< exp.col << ": the expression of condition must be boolean type\n";
		this->dumpSTDERR(exp.line, exp.col);
	}
}

void SemanticAnalyzer::visit(ForNode &p_for) {
	tb_stack[tb_stack.size() - 1].content.push_back(SymbolEntry("DummyScope", "DummyScope", 
		tb_stack.size() - 1, "DummyScope", "ForScope")); // for_stmt
	SymbolTable tb;
	tb_stack.push_back(tb);
	p_for.visitChildNodes(*this);
	tb_stack.back().dumpTable(opt_symtable);
	tb_stack.pop_back();
	// semantic analyses after get info from child
	type_stack.pop_back();
	std::string codeline = progcode[p_for.getLocation().line];
	int first = 0, second = 0, nextentry;
	for(int i = codeline.find(":=") + 2; i < (int)codeline.length(); i++){
		if('0' <= codeline[i] && codeline[i] <= '9')
			first = first * 10 + (codeline[i] - '0');
		else if(codeline[i] == 't'){
			nextentry = i + 2;
			break;
		}
	}
	for(int i = nextentry; i < (int)codeline.length(); i++){
		if('0' <= codeline[i] && codeline[i] <= '9')
			second = second * 10 + (codeline[i] - '0');
		else if(codeline[i] == 't')
			break;
	}
	if(first > second){
		ERROR_DETECT = 1;
		std::cerr << "<Error> Found in line " << p_for.getLocation().line << ", column "
			<< p_for.getLocation().col << ": the lower bound and upper bound of iteration count must be in the incremental order\n";
		this->dumpSTDERR(p_for.getLocation().line, p_for.getLocation().col);
	}
}

void SemanticAnalyzer::visit(ReturnNode &p_return) {
	p_return.visitChildNodes(*this);
	// semantic analyses after get info from child
	int index = tb_stack[0].content.size() - 1;
	std::string retType = tb_stack[0].content[index].Type, varKind = tb_stack[0].content[index].Kind;
	Expression exp = type_stack.back();
	type_stack.pop_back();

	if(exp.type != "ANY"){
		if(varKind != "function" || (varKind == "function" && retType == "void")){
			ERROR_DETECT = 1;
			std::cerr << "<Error> Found in line " << p_return.getLocation().line << ", column "
				<< p_return.getLocation().col << ": program/procedure should not return a value\n";
			this->dumpSTDERR(p_return.getLocation().line, p_return.getLocation().col);
		}
		else{
			bool CastErr = (this->TypeCombine(retType, exp.type) == "ERROR");
			if(CastErr){
				ERROR_DETECT = 1;
				std::cerr << "<Error> Found in line " << exp.line << ", column "
					<< exp.col << ": return \'" << exp.type << "\' from a function with return type \'"
					<< retType << "\'\n";
				this->dumpSTDERR(exp.line, exp.col);
			}
		}
	}
}
