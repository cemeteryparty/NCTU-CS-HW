all: project

project:
	make -C dataflow/
	make -C gatelevel/
	make -C gatelevel_UDP/
project-clean:
	${MAKE} clean -C dataflow/
	${MAKE} clean -C gatelevel/
	${MAKE} clean -C gatelevel_UDP/
clean:	project-clean