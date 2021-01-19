Filename = Lab2_full_sub

all:
	iverilog -o $(Filename).vvp *.v
	vvp $(Filename).vvp
clean:
	rm *.vvp *.vcd