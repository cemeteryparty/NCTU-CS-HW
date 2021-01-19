F_dataflow = Lab2_BCD_7segment_decoder_dataflow
F_gatelevel = Lab2_BCD_7segment_decoder_gatelevel
F_behavior = Lab2_BCD_7segment_decoder_behavior

all: dataflow gatelevel behavior

dataflow:
	iverilog -o $(F_dataflow).vvp *$(F_dataflow).v
	vvp $(F_dataflow).vvp
gatelevel:
	iverilog -o $(F_gatelevel).vvp *$(F_gatelevel).v
	vvp $(F_gatelevel).vvp
behavior:
	iverilog -o $(F_behavior).vvp *$(F_behavior).v
	vvp $(F_behavior).vvp
clean:
	rm *.vvp *.vcd