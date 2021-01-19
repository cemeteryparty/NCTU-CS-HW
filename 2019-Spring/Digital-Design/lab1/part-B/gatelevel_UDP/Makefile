Filename = Lab1_gatelevel_UDP

all:
	iverilog -o $(Filename).vvp *.v
	vvp $(Filename).vvp
clean:
	rm *.vvp *.vcd