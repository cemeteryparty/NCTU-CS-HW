    .file "./bonus_cases/test-cases/booleantest1.p"
    .option nopic
.section    .text
    .align 2
    .globl larger
    .type larger, @function
larger:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128

    sw a0, -12(s0)
    sw a1, -16(s0)
    addi t0, s0, -20
    sw t0, -20(s0)
    addi t0, s0, -20
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    bgt t1, t0, L0t
    li t0, 0
    j eL0
L0t:
    li t0, 1
eL0:
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    mv a0, t0

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size larger, .-larger
.section    .text
    .align 2
    .globl test
    .type test, @function
test:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128

    sw a0, -12(s0)
    sw a1, -16(s0)
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    beq t1, t0, L1t
    li t0, 0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    mv a0, t0
    j eL1
L1t:
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    mv a0, t0
eL1:

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size test, .-test
.section    .text
    .align 2
    .globl main
    .type main, @function
main:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128

    addi t0, s0, -12
    sw t0, -12(s0)
    addi t0, s0, -16
    sw t0, -16(s0)
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 10
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    addi t0, s0, -16
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 5
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, larger
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    beq t1, t0, L2t
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    j eL2
L2t:
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
eL2:
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, test
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size main, .-main
