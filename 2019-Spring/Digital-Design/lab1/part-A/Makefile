Filename = Simple_Circuit_prop_delay

all:
	iverilog -o $(Filename).vvp *.v
	vvp $(Filename).vvp
clean:
	rm *.vvp *.vcd