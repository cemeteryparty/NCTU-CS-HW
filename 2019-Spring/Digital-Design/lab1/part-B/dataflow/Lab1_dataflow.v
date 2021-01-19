module Lab1_dataflow(F,A,B,C,D);
	output    F;
	input     A, B, C, D;
	wire      ac, bd, _b, _bc, ad, A1, A2;
	
	assign F = A1 || A2;
	assign A1 = ac && bd;
	assign A2 = _bc && ad;
	assign  _b = !B;
	assign ac = A || C;
	assign bd = B || D;
	assign _bc = _b || C;
	assign ad = A || D;
endmodule