    .file "./advance_cases/test-cases/advLoop2.p"
    .option nopic
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
    addi t0, s0, -12
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
    addi t0, s0, -16
    sw t0, -16(s0)
    addi t0, s0, -16
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
L0h:
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 10
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    blt t1, t0, L0t
    j eL0
L0t:
    addi t0, s0, -20
    sw t0, -20(s0)
    addi t0, s0, -20
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
L1h:
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 10
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    blt t1, t0, L1t
    j eL1
L1t:
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
    lw t0, -12(s0)
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
    j L1h
eL1:
    addi t0, s0, -16
    addi sp, sp, -4
    sw t0, 0(sp)
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
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    j L0h
eL0:

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size main, .-main
