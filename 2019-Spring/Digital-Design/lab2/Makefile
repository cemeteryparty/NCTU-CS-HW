# lab2 Makefile
all: project

project:
	make -C half_sub/
	make -C full_sub/
	make -C 4_bit_sub/
	make -C 7segment_decoder/
project-clean:
	${MAKE} clean -C half_sub/
	${MAKE} clean -C full_sub/
	${MAKE} clean -C 4_bit_sub/
	${MAKE} clean -C 7segment_decoder/
clean:	project-clean