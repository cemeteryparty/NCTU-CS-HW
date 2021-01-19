module Lab2_BCD_7segment_decoder_gatelevel(output [6:0]A, input [3:0]D);
	wire    [3:0]nD;
	wire    [15:0] M,m;

	// complement
	not    nd0(nD[0], D[0]);
	not    nd1(nD[1], D[1]);
	not    nd2(nD[2], D[2]);
	not    nd3(nD[3], D[3]);
	// m
	and    m0(m[0], nD[0], nD[1], nD[2], nD[3]);
	and    m1(m[1], D[0], nD[1], nD[2], nD[3]);
	and    m2(m[2], nD[0], D[1], nD[2], nD[3]);
	and    m3(m[3], D[0], D[1], nD[2], nD[3]);
	and    m4(m[4], nD[0], nD[1], D[2], nD[3]);
	and    m5(m[5], D[0], nD[1], D[2], nD[3]);
	and    m6(m[6], nD[0], D[1], D[2], nD[3]);
	and    m7(m[7], D[0], D[1], D[2], nD[3]);
	and    m8(m[8], nD[0], nD[1], nD[2], D[3]);
	and    m9(m[9], D[0], nD[1], nD[2], D[3]);
	// M
	or     M0(M[0], D[0], D[1], D[2], D[3]);
	or     M1(M[1], nD[0], D[1], D[2], D[3]);
	or     M2(M[2], D[0], nD[1], D[2], D[3]);
	or     M3(M[3], nD[0], nD[1], D[2], D[3]);
	or     M4(M[4], D[0], D[1], nD[2], D[3]);
	or     M5(M[5], nD[0], D[1], nD[2], D[3]);
	or     M6(M[6], D[0], nD[1], nD[2], D[3]);
	or     M7(M[7], nD[0], nD[1], nD[2], D[3]);
	or     M8(M[8], D[0], D[1], D[2], nD[3]);
	or     M9(M[9], nD[0], D[1], D[2], nD[3]);
	// sop pos
	and    A0(A[0], M[1], M[4]);
	and    A1(A[1], M[5], M[6]);
	buf    A2(A[2], M[2]);
	and    A3(A[3], M[1], M[4], M[7]);
	or     A4(A[4], m[0], m[2], m[6], m[8]);
	and    A5(A[5], M[1], M[2], M[3], M[7]);
	and    A6(A[6], M[0], M[1], M[7]);
endmodule