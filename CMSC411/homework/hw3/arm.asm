.data

array_a:    .word   1, 2, 3
array_b:    .word   7, 8, 9

.text
main:
    @ Setup registers.
    ldr r0, =array_a
    ldr r1, =array_b
    ldr r2, =array_b + 12

loop:
    @ Get values from memory
    ldr r3, [r0]
    ldr r4, [r1]
    @ Multiply and store in register.
    mul r5, r4, r3
    add r6, r5, r6
    @ Increment memory addresses.
    add r0, r0, #4
    add r1, r1, #4
    cmp r1, r2
    beq exit
    b loop
exit:
    @ Print out dot product.
    mov r0, #1
    ldr r1, r7
    ldr r2, #4
    mov r7, #4
    swi #0

