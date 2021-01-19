module Lab1_gatelevel(F,A,B,C,D);
	output    F;
	input     A,B,C,D;
	wire      ac, bd, _b, _bc, ad, A1, A2;
	
	or     G0(F, A1, A2);
	and    G1(A1, ac, bd);
	and    G2(A2, _bc, ad);
	not    G3(_b, B);
	or     G4(ac, A, C);
	or     G5(bd, B, D);
	or     G6(_bc, _b, C);
	or     G7(ad, A, D);
endmodule