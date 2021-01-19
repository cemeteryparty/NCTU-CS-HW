module t_Lab3_SbRb_Latch_gatelevel();
    wire Q,_Q;
    reg Sb,Rb;
    Lab3_SbRb_Latch_gatelevel G(Q,_Q,Sb,Rb);

    initial begin
        S = 1'b1;R = 1'b0; 
        #10 S = 1'b1;R = 1'b1;
        #10 S = 1'b0;R = 1'b1;
        #10 S = 1'b1;R = 1'b1;
        #10 S = 1'b0;R = 1'b0;
        #10 S = 1'b1;R = 1'b1;
        #10 S = 1'b1;R = 1'b0;
    end
    initial #100 $finish;
endmodule



