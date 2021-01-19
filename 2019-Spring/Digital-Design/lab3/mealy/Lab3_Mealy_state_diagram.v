module Lab3_Mealy_state_diagram(output reg z, input x,clock,reset);
	reg [1:0] st,nst;
	parameter s0 = 2'b00,s1 = 2'b01,s2 = 2'b10,s3 = 2'b11;
	always @(posedge clock,negedge reset) begin
		if(!reset) 
			st <= s0;
		else
			st = nst;
	end
	always @(st,x) begin
		case(st)
			s0:
				if(x)
					nst = s2;
				else
					nst = s1;
			s1:
				if(x)
					nst = s3;
				else
					nst = s0;
			s2:
				if(x)
					nst = s3;
				else
					nst = s1;
			s3:
				if(x)
					nst = s2;
				else
					nst = s0;
		endcase
	end
	always @(st,x) begin
		case(st)
			s1,s2:
				z = x;
			s0,s3:
				z = ~x;
		endcase
	end
endmodule