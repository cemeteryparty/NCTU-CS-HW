module Lab3_Mealy_structural(output z, input x,clock,reset);
	wire A,B,_A,_B,JA,KA,JB,KB;
	assign JA = x;
	assign KA = ~JA;
	assign JB = ~(x | B) | (A & ~B) | (x & ~A & B);
	assign KB = ~JB;
	assign z = ~((A ^ B) ^ x); 
	JK_ff_AR G0(A,_A,JA,KA,clock,reset);
	JK_ff_AR G1(B,_B,JB,KB,clock,reset);
endmodule