module JK_ff_AR(output reg Q,_Q, input J,K,clk,rst);
	wire JK;
	assign JK = (J & ~Q) | (~K & Q);
	always @(posedge clk,negedge rst) begin
		if(!rst)
			Q <= 1'b0;
		else
			Q <= JK;
		_Q = ~Q;
	end
endmodule