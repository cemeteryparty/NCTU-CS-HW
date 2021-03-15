    .file "./basic_cases/test-cases/specExample.p"
    .option nopic
.comm a, 4, 4
.section    .rodata
    .align 2
    .globl d
    .type d, @object
d:
    .word 5
.section    .text
    .align 2
    .globl sum
    .type sum, @function
sum:
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
    add t0, t1, t0
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
    .size sum, .-sum
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
    li t0, 5
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
    li t0, 6
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, a
    addi sp, sp, -4
    sw t0, 0(sp)
    jal ra, readInt
    lw t0, 0(sp)
    addi sp, sp, 4
    sw a0, 0(t0)
    la t0, a
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    la t0, a
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, d
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, sum
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, a
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    la t0, a
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
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, d
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    mul t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, a
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    la t0, a
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 40
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    ble t1, t0, L1t
    li t0, 0
    j eL1
L1t:
    li t0, 1
eL1:
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    beq t1, t0, L0t
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    j eL0
L0t:
    la t0, a
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
eL0:
L2h:
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 8
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    blt t1, t0, L3t
    li t0, 0
    j eL3
L3t:
    li t0, 1
eL3:
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
    j eL2
L2t:
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    j L2h
eL2:
    addi t0, s0, -20
    sw t0, -20(s0)
    addi t0, s0, -20
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
L4h:
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 13
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    blt t1, t0, L4t
    j eL4
L4t:
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    addi t0, s0, -20
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    j L4h
eL4:

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size main, .-main
