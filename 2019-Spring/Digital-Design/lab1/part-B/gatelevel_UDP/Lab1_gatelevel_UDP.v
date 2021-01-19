module Lab1_gatelevel_UDP(F, A, B, C, D);
	output    F;
	input     A,B,C,D;
	wire      _b,A1,A2;

	assign F = A1 || A2;
	Lab1_UDP(A1, A, C, B, D);
	Lab1_UDP(A2, _b, C,A , D);
	assign _b = !B;
endmodule