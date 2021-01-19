F_behavior = Lab2_half_sub_behavior
F_dataflow = Lab2_half_sub_dataflow
F_gate_level = Lab2_half_sub_gate_level

all: behavior dataflow gate_level

behavior:
	iverilog -o $(F_behavior).vvp *$(F_behavior).v
	vvp $(F_behavior).vvp
dataflow:
	iverilog -o $(F_dataflow).vvp *$(F_dataflow).v
	vvp $(F_dataflow).vvp
gate_level:
	iverilog -o $(F_gate_level).vvp *$(F_gate_level).v
	vvp $(F_gate_level).vvp
clean:
	rm *.vvp *.vcd