# Easy Spec. of HW5

## Generating RISC-V Instructions 
```assembly
.section    .bss
	# uninitialized global varS
.section    .rodata
	# global constS
.section    .text
	# function
.section    .text
	# main function
```
- Table of Contents
	- [Program](#Program)
	- [Declaration of variable & constant](#Declaration-of-variable-and-constant)
	- [Declaration of function](#Declaration-of-function)
	- Expression
		- [Binary expression](#Binary-expression)
		- [Unary expression](#Unary-expression)
		- [Constant value expression](#Constant-value-expression)
		- [Function invocation expression](#Function-invocation-expression)
		- [Variable reference expression](#Variable-reference-expression)
	- Statement
		- [Assignment statement](#Assignment-statement)
		- [Print statement](#Print-statement)
		- [Read statement](#Read-statement)
		- [Return statement](#Return-statement)
		- [If statement](#If-statement)
		- [While statement](#While-statement)
		- [For statement](#For-statement)
	- Appendix
		- [Array](#Array)
		- [Shortage of reg. to arg. Exception](#Shortage-of-reg-to-arg-Exception)
### Program
```assembly
	.file "PROGRAM_NAME"
	.option nopic
	(declaration of global variable and constant)
	(declaration of function)
.section    .text
	.align 2
	.globl main
	.type main, @function
main:
	addi sp, sp, -128
	sw ra, 124(sp)
	sw s0, 120(sp)
	addi s0, sp, 128
	(body of main function)
	lw ra, 124(sp)
	lw s0, 120(sp)
	addi sp, sp, 128
	jr ra
	.size main, .-main
```

### Declaration of variable and constant
- Global Variable
```assembly
.comm VAR_NAME, 4, 4
```
- Global Constant
```assembly
.section    .rodata
	.align 2
	.globl VAR_NAME
	.type VAR_NAME, @object
VAR_NAME:
	.word 5
```
- Local Parameter
```assembly
	sw aREG_NUM, OFFSET(s0)
```
- Local Constant
```assembly
	addi t0, s0, OFFSET
	addi sp, sp, -4
	sw t0, 0(sp)
	li t0, CONST
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	sw t0, 0(t1)
```
- Local Variable & Loop variable
```assembly
	(instructions of Variable & Loop variable will be generated in Assignment)
```

### Declaration of function
```assembly
	.section    .text
	.align 2
	.globl FUNC_NAME
	.type FUNC_NAME, @function
FUNC_NAME:
	addi sp, sp, -128
	sw ra, 124(sp)
	sw s0, 120(sp)
	addi s0, sp, 128
	(parameter of function)
	(body of function)
	lw ra, 124(sp)
	lw s0, 120(sp)
	addi sp, sp, 128
	jr ra
	.size FUNC_NAME, .-FUNC_NAME
```

### Binary expression
```assembly
	(get LHS value and push to stack)
	(get RHS value and push to stack)
	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
# not comparasion operator:
	OPERATOR t0, t1, t0
#
# comparasion operator:
	OPERATOR t1, t0, LABEL_TRUE
	li t0, 0
	j LABEL_END
LABEL_TRUE:
	li t0, 1
LABEL_END:
#
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Unary expression
```assembly
# "not" operator:
	li t0, -1
#
# "neg" operator:
	li t0, 0
#
	addi sp, sp, -4
	sw t0, 0(sp)
	(get operand value and push to stack)
	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
# "not" operator:
	xor t0, t1, t0
#
# "neg" operator:
	sub t0, t1, t0
#
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Constant value expression
```assembly
	# true = 1; false = 0;
	li t0, CONST
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Function invocation expression
```assembly
# example of 2 arguments
	(get arg0 value and push to stack)
	(get arg1 value and push to stack)
	lw a1, 0(sp)
	addi sp, sp, 4
	lw a0, 0(sp)
	addi sp, sp, 4
#
	jal ra, FUNC_NAME
	mv t0, a0
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Variable reference expression
```assembly
# load_addr:
## global:
	la t0, VARREF_NAME
##
## local:
	addi t0, s0, OFFSET
##
#
# load value:
## global:
	la t0, VARREF_NAME
	lw t1, 0(t0)
	mv t0, t1
##
## local:
	lw t0, OFFSET(s0)
##
#
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Assignment statement
```assembly
	(get dest addr and push to stack)
	(get value and push to stack)
	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	sw t0, 0(t1)
```

### Print statement
```assembly
	(get expr value and push to stack)
	lw a0, 0(sp)
	addi sp, sp, 4
	jal ra, printInt
```

### Read statement
```assembly
	(get dest addr and push to stack)
	jal ra, readInt
	lw t0, 0(sp)
	addi sp, sp, 4
	sw a0, 0(t0)
```

### Return statement
```assembly
	(get expr value and push to stack)
	lw t0, 0(sp)
	addi sp, sp, 4
	mv a0, t0
```

### If statement
```assembly
	(get condition expr value and push to stack)
	li t0, 1 # push a "true"
	addi sp, sp, -4
	sw t0, 0(sp)

	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	beq t1, t0, LABEL_TRUE # compare expr value with "true"
	(get false body)
	j LABEL_END
LABEL_TRUE:
	(get true body)
LABEL_END:
```

### While statement
```assembly
LABEL_HEAD:
	(get condition expr value and push to stack)
	li t0, 1 # push a "true"
	addi sp, sp, -4
	sw t0, 0(sp)

	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	beq t1, t0, LABEL_TRUE # compare expr value with "true"
	j LABEL_END
LABEL_TRUE:
	(get while body)
	j LABEL_HEAD
LABEL_END:
```

### For statement
```assembly
	(assignment of loop_var)
LABEL_HEAD:
	lw t0, OFFSET(s0) # get lower bound
	addi sp, sp, -4
	sw t0, 0(sp)
	(get loop_var upper bound and push to stack)

	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	blt t1, t0, LABEL_TRUE
	j LABEL_END
LABEL_TRUE:
	(get for body)
	# doing loop_var++
	addi t0, s0, OFFSET
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, OFFSET(s0)
	addi sp, sp, -4
	sw t0, 0(sp)
	li t0, 1
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi sp, sp, 4
	lw t1, 0(sp)
	addi sp, sp, 4
	sw t0, 0(t1)
	j LABEL_HEAD
LABEL_END:
```
### Array
date: Fri, Jan 15, 2021 23:00
```p
// test1.p
test1;
begin
// main function
var a : array 2 of array 3 of integer;
end
end

```
Program Structure:
```
-128 +-------------+ <- base sp
	 |    .....    |
-44  +-------------+  
	 |   a[1][2]   |
-40  +-------------+
	 |   a[1][1]   |
-36  +-------------+
	 |   a[1][0]   |
-32  +-------------+
	 |   a[0][2]   |
-28  +-------------+
	 |   a[0][1]   |
-24  +-------------+
	 |   a[0][0]   |
-20  +-------------+
	 |      3      |
-16  +-------------+
	 |      2      |
-12  +-------------+
	 |   s0 - 12   |
-8   +-------------+
	 |   pre s0    |
-4   +-------------+
	 | return addr |
0    +-------------+ <- frame pointer (s0)
```
Variable reference get array value:
```assembly
	# see the previous diagram, OFFSET = s0 - 12
	# suppose we want to do "print a[1][2];"
	lw t0, OFFSET(s0) # t0 = s0 - 12
	addi sp, sp, -4
	sw t0, 0(sp)
	(get first expr value and push to stack) # 0(sp) = 1
	li t0, 4 # sizeof(int) = 4
	lw t1, 0(sp)
	addi sp, sp, 4
	mul t0, t1, t0 # t0 = 1 * 4 = 4
	addi sp, sp, -4
	sw t0, 0(sp)

	lw t0, OFFSET - 8(s0) # t0 = *(s0 - 20) = 3
	lw t1, 0(sp) # t1 = 4
	addi sp, sp, 4
	mul t0, t1, t0 # t0 = 12
	addi sp, sp, -4
	sw t0, 0(sp)

	lw t0, 0(sp) # arr_offset: t0 = 12
	addi sp, sp, 4 
	lw t1, 0(sp) # array_base_addr: t1 = s0 - 12
	addi sp, sp, 4 
	sub t0, t1, t0 # t0 = s0 - 24
	addi sp, sp, -4
	sw t0, 0(sp)

	(get second expr value and push to stack) # 0(sp) = 2
	li t0, 4 # sizeof(int) = 4
	lw t1, 0(sp)
	addi sp, sp, 4
	mul t0, t1, t0 # t0 = 2 * 4 = 8
	addi sp, sp, -4
	sw t0, 0(sp)

	lw t0, 0(sp) # arr_offset: t0 = 8
	addi sp, sp, 4 
	lw t1, 0(sp) # array_base_addr: t1 = s0 - 24
	addi sp, sp, 4 
	sub t0, t1, t0 # t0 = s0 - 32
	addi sp, sp, -4
	sw t0, 0(sp)

	li t0, (NUM_OF_INDICE + 1) * 4 # t0 = 12
	lw t1, 0(sp) # t1 = s0 - 32
	addi sp, sp, 4
	sub t0, t1, t0 # t0 = s0 - 44

	lw t1, 0(t0) # t1 = *(s0 - 44) = a[1][2]
	mv t0, t1 # t0 = a[1][2]
	addi sp, sp, -4
	sw t0, 0(sp)
```

### Shortage of reg. to arg. Exception

```p
argument;

var v: integer;

sum(m0, m1, m2, m3, m4, 
	m5, m6, m7, m8, m9): integer
begin
	...
end
end

begin
...
v := sum(n0, n1, n2, n3, n4, 
	n5, n6, n7, n8, n9);

end
end
```
Structure:
```
+------------+ <- sp           // a0 = n0, a1 = n1, ..., a7 = n7
|     n9     |                 +############+ <- t3
+------------+                 |     n9     |
|     n8     |                 +------------+ <- t3+4
+------------+                 |     n8     |
|     n7     |                 +############+
+------------+                 |     n7     |
|    ....    |                 +------------+
+------------+                 |    ....    |
|     n1     |      ======>    +------------+
+------------+                 |     n1     |
|     n0     |                 +------------+
++++++++++++++ <- s0 - 128     |     n0     |
|            |                 ++++++++++++++ <- sp
+------------+                 |            |
|   ......   |                 +------------+
+------------+                 |   ......   |
|            |                 +------------+
++++++++++++++ <- s0           |            |
                               ++++++++++++++ <- s0
```
Structure (Do function call):
```
+------------+
| *(s0+4)=n9 |
+------------+
|  *(s0)=n8  |
+------------+
|   a7= n7   |
+-----...----+
|   a1= n1   |
+------------+
|   a0= n0   |
+------------+
|  s0(main)  |
+------------+
|  ret addr  |
+############+ <- s0(sum)
| *(t3+4)=n8 |
+------------+
|  *(t3)=n9  |
++++++++++++++
```

```assembly
(skip)
sum:
	(skip)
	sw a0, -12(s0)
	sw a1, -16(s0)
	sw a2, -20(s0)
	sw a3, -24(s0)
	sw a4, -28(s0)
	sw a5, -32(s0)
	sw a6, -36(s0)
	sw a7, -40(s0)
	lw t0, 0(s0)
	sw t0, -44(s0)
	lw t0, 4(s0)
	sw t0, -48(s0)
	(skip)
main:
	(skip)
	add t3, zero, sp
	addi sp, sp, 4
	addi sp, sp, 4

	lw a7, 0(sp)
	addi sp, sp, 4
	lw a6, 0(sp)
	addi sp, sp, 4
	...
	lw a0, 0(sp)
	addi sp, sp, 4

	lw t0, 0(t3)
	addi t3, t3, 4
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t0, 0(t3)
	addi t3, t3, 4
	addi sp, sp, -4
	sw t0, 0(sp)

	jal ra, sum
	mv t0, a0

	addi sp, sp, 4
	addi sp, sp, 4
	(skip)
```
