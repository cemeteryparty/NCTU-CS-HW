module Lab2_BCD_7segment_decoder_dataflow(output [6:0]A, input [3:0]D);
	wire    [3:0]nD;
	wire    [15:0] M, m;

	//complement
	assign nD[0] = ~D[0];
	assign nD[1] = ~D[1];
	assign nD[2] = ~D[2];
	assign nD[3] = ~D[3];
	//m
	assign m[0] = nD[0] & nD[1] & nD[2] & nD[3];
	assign m[1] = D[0] & nD[1] & nD[2] & nD[3];
	assign m[2] = nD[0] & D[1] & nD[2] & nD[3];
	assign m[3] = D[0] & D[1] & nD[2] & nD[3];
	assign m[4] = nD[0] & nD[1] & D[2] & nD[3];
	assign m[5] = D[0] & nD[1] & D[2] & nD[3];
	assign m[6] = nD[0] & D[1] & D[2] & nD[3];
	assign m[7] = D[0] & D[1] & D[2] & nD[3];
	assign m[8] = nD[0] & nD[1] & nD[2] & D[3];
	assign m[9] = D[0] & nD[1] & nD[2] & D[3];
	//M
	assign M[0] = D[0] | D[1] | D[2] | D[3];
	assign M[1] = nD[0] | D[1] | D[2] | D[3];
	assign M[2] = D[0] | nD[1] | D[2] | D[3];
	assign M[3] = nD[0] | nD[1] | D[2] | D[3];
	assign M[4] = D[0] | D[1] | nD[2] | D[3];
	assign M[5] = nD[0] | D[1] | nD[2] | D[3];
	assign M[6] = D[0] | nD[1] | nD[2] | D[3];
	assign M[7] = nD[0] | nD[1] | nD[2] | D[3];
	assign M[8] = D[0] | D[1] | D[2] | nD[3];
	assign M[9] = nD[0] | D[1] | D[2] | nD[3];
	//sop pos
	assign A[0] = M[1] & M[4];
	assign A[1] = M[5] & M[6];
	assign A[2] = M[2];
	assign A[3] = M[1] & M[4] & M[7];
	assign A[4] = m[0] | m[2] | m[6] | m[8];
	assign A[5] = M[1] & M[2] & M[3] & M[7];
	assign A[6] = M[0] & M[1] & M[7];
endmodule