module t_Lab3_Pos_Edge_D_FF_gatelevel();
    wire Q,_Q;
    reg D,clock;
    Lab3_Pos_Edge_D_FF_gatelevel G(Q,_Q,D,clock);
    initial begin
        clock = 1'b0;forever #10 clock = ~clock;
    end
    initial fork
        D = 1'b0;
        #15 D = 1'b1;
        #35 D = 1'b0;
        #65 D = 1'b1;
        #88 D = 1'b0;
        #125 D = 1'b1;
        #130 D = 1'b0;
    join
    initial #150 $finish;
endmodule



