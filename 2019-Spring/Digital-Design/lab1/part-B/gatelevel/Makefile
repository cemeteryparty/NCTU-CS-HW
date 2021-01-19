Filename = Lab1_gatelevel

all:
	iverilog -o $(Filename).vvp *.v
	vvp $(Filename).vvp
clean:
	rm *.vvp *.vcd