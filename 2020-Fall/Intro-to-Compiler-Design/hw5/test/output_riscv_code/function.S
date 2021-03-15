    .file "./basic_cases/test-cases/function.p"
    .option nopic
.comm gv, 4, 4
.section    .rodata
    .align 2
    .globl gc
    .type gc, @object
gc:
    .word 2
.section    .text
    .align 2
    .globl product
    .type product, @function
product:
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
    mul t0, t1, t0
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
    .size product, .-product
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
    .globl dot
    .type dot, @function
dot:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128

    sw a0, -12(s0)
    sw a1, -16(s0)
    sw a2, -20(s0)
    sw a3, -24(s0)
    addi t0, s0, -28
    sw t0, -28(s0)
    addi t0, s0, -28
    addi sp, sp, -4
    sw t0, 0(sp)
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
    jal ra, product
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -20(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -24(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, product
    mv t0, a0
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
    lw t0, -28(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    mv a0, t0

    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .size dot, .-dot
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
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, gv
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, gv
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, gv
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, gc
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, product
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, gv
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
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
    jal ra, product
    mv t0, a0
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
    la t0, gv
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    la t0, gv
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, gv
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    la t0, gc
    lw t1, 0(t0)
    mv t0, t1
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -12(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a3, 0(sp)
    addi sp, sp, 4
    lw a2, 0(sp)
    addi sp, sp, 4
    lw a1, 0(sp)
    addi sp, sp, 4
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, dot
    mv t0, a0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sw t0, 0(t1)
    la t0, gv
    lw t1, 0(t0)
    mv t0, t1
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
