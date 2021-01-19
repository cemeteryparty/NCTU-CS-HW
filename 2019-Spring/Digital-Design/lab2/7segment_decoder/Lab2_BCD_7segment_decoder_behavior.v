module Lab2_BCD_7segment_decoder_behavior(output reg [6:0]A, input [3:0]D);
	reg    [3:0]nD;
	reg    [15:0] M, m;

	always @(D[0], D[1], D[2], D[3])begin
		// complement
		nD[0] = ~D[0];
		nD[1] = ~D[1];
		nD[2] = ~D[2];
		nD[3] = ~D[3];
		// m
		m[0] = nD[0] & nD[1] & nD[2] & nD[3];
		m[1] = D[0] & nD[1] & nD[2] & nD[3];
		m[2] = nD[0] & D[1] & nD[2] & nD[3];
		m[3] = D[0] & D[1] & nD[2] & nD[3];
		m[4] = nD[0] & nD[1] & D[2] & nD[3];
		m[5] = D[0] & nD[1] & D[2] & nD[3];
		m[6] = nD[0] & D[1] & D[2] & nD[3];
		m[7] = D[0] & D[1] & D[2] & nD[3];
		m[8] = nD[0] & nD[1] & nD[2] & D[3];
		m[9] = D[0] & nD[1] & nD[2] & D[3];
		// M
		M[0] = D[0] | D[1] | D[2] | D[3];
		M[1] = nD[0] | D[1] | D[2] | D[3];
		M[2] = D[0] | nD[1] | D[2] | D[3];
		M[3] = nD[0] | nD[1] | D[2] | D[3];
		M[4] = D[0] | D[1] | nD[2] | D[3];
		M[5] = nD[0] | D[1] | nD[2] | D[3];
		M[6] = D[0] | nD[1] | nD[2] | D[3];
		M[7] = nD[0] | nD[1] | nD[2] | D[3];
		M[8] = D[0] | D[1] | D[2] | nD[3];
		M[9] = nD[0] | D[1] | D[2] | nD[3];
		// sop pos
		A[0] = M[1] & M[4];
		A[1] = M[5] & M[6];
		A[2] = M[2];
		A[3] = M[1] & M[4] & M[7];
		A[4] = m[0] | m[2] | m[6] | m[8];
		A[5] = M[1] & M[2] & M[3] & M[7];
		A[6] = M[0] & M[1] & M[7];
	end
endmodule