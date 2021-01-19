primitive Lab1_UDP(X, A, C, B, D);
	output X;
	input A, C, B, D;
	table
		0 0 0 0 : 0;
		0 0 0 1 : 0;
		0 0 1 0 : 0;
		0 0 1 1 : 0;
		0 1 0 0 : 0;
		0 1 0 1 : 1;
		0 1 1 0 : 1;
		0 1 1 1 : 1;
		1 0 0 0 : 0;
		1 0 0 1 : 1;
		1 0 1 0 : 1;
		1 0 1 1 : 1;
		1 1 0 0 : 0;
		1 1 0 1 : 1;
		1 1 1 0 : 1;
		1 1 1 1 : 1;
	endtable
endprimitive