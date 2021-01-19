Filename = Lab1_dataflow

all:
	iverilog -o $(Filename).vvp *.v
	vvp $(Filename).vvp
clean:
	rm *.vvp *.vcd