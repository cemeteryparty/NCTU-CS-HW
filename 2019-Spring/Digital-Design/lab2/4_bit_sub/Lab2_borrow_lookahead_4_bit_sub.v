module Lab2_borrow_lookahead_sub(output [3:0]Diff, output Bout, input [3:0]X, Y, input Bin);
	wire    [3:1]B;
	wire    [3:0]P, G;

	//i = 0
	assign P[0] = X[0] ^ Y[0];
	assign G[0] = ~X[0] & Y[0];
	assign Diff[0] = P[0] ^ Bin;
	assign B[1] = (Bin & ~P[0]) | G[0];
	//i = 1
	assign P[1] = X[1] ^ Y[1];
	assign G[1] = ~X[1] & Y[1];
	assign Diff[1] = P[1] ^ B[1];
	assign B[2] = (B[1] & ~P[1]) | G[1];
	//i = 2
	assign P[2] = X[2] ^ Y[2];
	assign G[2] = ~X[2] & Y[2];
	assign Diff[2] = P[2] ^ B[2];
	assign B[3] = (B[2] & ~P[2]) | G[2];
	//i = 3
	assign P[3] = X[3] ^ Y[3];
	assign G[3] = ~X[3] & Y[3];
	assign Diff[3] = P[3] ^ B[3];
	assign Bout = (B[3] & ~P[3]) | G[3];
endmodule