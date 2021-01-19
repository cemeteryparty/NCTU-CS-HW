module t_Lab2_half_sub();
	wire    D, B;
	reg     x, y, z;
	reg     [2:0]i;
	Lab2_full_sub G(D, B, x, y, z);

	initial begin
		$dumpfile("Lab2_full_sub.vcd");
		$dumpvars(0, G);
		for (i = 0; i < 8; i = i + 1) 
		begin
			{x, y, z} = i;
			#10;
		end
	end
	initial #80 $finish;
endmodule