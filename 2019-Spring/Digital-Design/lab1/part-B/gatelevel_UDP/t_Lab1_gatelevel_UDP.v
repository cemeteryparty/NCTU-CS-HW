`timescale 1ns/1ns
module t_Lab1_gatelevel_UDP();
	wire    F;
	reg     A,B,C,D;
	reg     [4:0]i;
	Lab1_gatelevel_UDP G(F, A, B, C, D);

	initial begin
		$dumpfile("Lab1_gatelevel_UDP.vcd");
		$dumpvars(0, G);

		for (i = 0; i < 16; i = i + 1) 
		begin
			{A, B, C, D} = i;
			#10;
		end
	end
	initial #200 $finish;
endmodule
