`include "../half_sub/Lab2_half_sub_gate_level.v"
module Lab2_full_sub(output D, B, input x, y, z);
	wire    DM, BM, BL;
	
	Lab2_half_sub_gate_level HS1(DM, BM, x, y);
	Lab2_half_sub_gate_level HS2(D, BL, DM, z);
	assign B = BM | BL;
endmodule