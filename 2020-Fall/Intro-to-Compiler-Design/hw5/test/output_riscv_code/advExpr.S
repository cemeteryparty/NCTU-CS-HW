    .file "./advance_cases/test-cases/advExpr.p"
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
    addi t0, s0, -16
    sw t0, -16(s0)
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 3
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 5
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
    mul t0, t1, t0
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
    addi t0, s0, -16
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 3
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    mul t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 5
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    sub t0, t1, t0
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
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
    addi t0, s0, -12
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 1
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 2
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 3
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 3
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 5
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
    mul t0, t1, t0
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
    li t0, 12
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 37
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    add t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 49
    addi sp, sp, -4
    sw t0, 0(sp)
    li t0, 7
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    div t0, t1, t0
    addi sp, sp, -4
    sw t0, 0(sp)
    lw t0, 0(sp)
    addi sp, sp, 4
    lw t1, 0(sp)
    addi sp, sp, 4
    div t0, t1, t0
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
    lw t0, -16(s0)
    addi sp, sp, -4
    sw t0, 0(sp)
    lw a0, 0(sp)
    addi sp, sp, 4
    jal ra, printInt
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
    rem t0, t1, t0
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
