module t_Lab2_BCD_7segment_decoder();
	wire    [6:0]A;
	reg     [3:0]D;
	reg     [3:0]i;
	Lab2_BCD_7segment_decoder_behavior G(A,D);
	
	initial begin
		$dumpfile("Lab2_BCD_7segment_decoder_behavior.vcd");
		$dumpvars(0, G);
		for(i = 0; i < 10; i = i + 1) 
		begin
			{D[3], D[2], D[1], D[0]} = i;
			#10;
		end
	end
	initial #100 $finish;
endmodule