module t_Lab2_half_sub();
	wire    D, B;
	reg     x, y;
	reg     [1:0]i;
	Lab2_half_sub_dataflow G(D, B, x, y);

	initial begin
		$dumpfile("Lab2_half_sub_dataflow.vcd");
		$dumpvars(0, G);
		for(i = 0; i < 4; i = i + 1) 
		begin
			{x, y} = i;
			#10;
		end
	end
	initial #40 $finish;
endmodule