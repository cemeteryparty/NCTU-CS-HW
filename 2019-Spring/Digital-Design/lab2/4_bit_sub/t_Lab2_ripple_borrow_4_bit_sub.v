module t_Lab2_4_bit_sub();
	wire    [3:0]Diff;
	wire    Bout;
	reg     [3:0]X, Y;
	reg     Bin;
	
	Lab2_ripple_borrow_4_bit_sub G(Diff, Bout, X, Y, Bin);
	
	initial begin
		$dumpfile("Lab2_ripple_borrow_4_bit_sub.vcd");
		$dumpvars(0, G);
		X = 4'b1101; Y = 4'b0101; Bin = 1'b0; 
		#10 X = 4'b1100; Y = 4'b1000; Bin = 1'b1;
		#10 X = 4'b0101; Y = 4'b1101; Bin = 1'b0;
		#10 X = 4'b1000; Y = 4'b1100; Bin = 1'b1;
		#10 X = 4'b0101; Y = 4'b0101; Bin = 1'b0;
		#10 X = 4'b1011; Y = 4'b1011; Bin = 1'b1;
	end
	initial #60 $finish;
endmodule