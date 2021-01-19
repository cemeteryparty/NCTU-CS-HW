module Lab2_half_sub_gate_level(output D, B, input x, y);
	wire    _x;
	
	xor    G0(D, x, y);
	and    G1(B, _x, y);
	not    G3(_x, x);
endmodule