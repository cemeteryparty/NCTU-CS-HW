module t_Lab3_Mealy();
    wire z;
    reg x,clk,rst;
    Lab3_Mealy_state_diagram G(z,x,clk,rst);
    //Lab3_Mealy_structural G(z,x,clk,rst);
    initial begin
        clk = 1'b0;forever #5 clk = ~clk;
    end
    initial fork
        rst = 1'b0;//s0
        #1 rst = 1'b1;
        #2 x = 1'b0;//s1
        #12 x = 1'b1;//s3
        #22 x = 1'b1;//s0
        #32 x = 1'b1;//s2
        #42 x = 1'b0;//s1
        #52 x = 1'b0;//s0
        #62 x = 1'b1;//s2
        #72 x = 1'b1;//s3
        #82 x = 1'b0;//s0
        #91 x = 1'b1;//s2
        #93 rst = 1'b0;//s0
    join
    initial #100 $finish;
endmodule