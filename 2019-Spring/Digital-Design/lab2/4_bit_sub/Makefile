F_ripple_borrow = Lab2_ripple_borrow_4_bit_sub
F_borrow_lookahead = Lab2_borrow_lookahead_4_bit_sub

all: ripple_borrow borrow_lookahead

ripple_borrow:
	iverilog -o $(F_ripple_borrow).vvp *$(F_ripple_borrow).v
	vvp $(F_ripple_borrow).vvp
borrow_lookahead:
	iverilog -o $(F_borrow_lookahead).vvp *$(F_borrow_lookahead).v
	vvp $(F_borrow_lookahead).vvp
clean:
	rm *.vvp *.vcd