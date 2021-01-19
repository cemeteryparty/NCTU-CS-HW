module Lab3_Pos_Edge_D_FF_gatelevel(output Q,NQ, input D,clock);
	wire Sb,Rb,O1,O2;

	nand #2 G0(O1,Sb,O2);
	nand #2 G1(Sb,O1,clock);
	nand #2 G2(Rb,Sb,clock,O2);
	nand #2 G3(O2,Rb,D);
	//sr latch
	nand #2 G4(Q,Sb,NQ);
	nand #2 G5(NQ,Rb,Q);
endmodule