    .data
array_a:  .word   1, 2, 3
array_b:  .word   7, 8, 9
    .text
main:
    la $s0, array_a # Load address of array_a into s0
    la $s1, array_b # Load address of array_b into s1
    la $s2, array_a # Load address of array_a into s2
    addi $s2, $s2, 12 # Final array offset relative to array_a
    addi $t0, $zero, 4 # Incrementor (words are 4 bytes long)
loop:
    lw $t1, ($s0) # Get value from arrays
    lw $t2, ($s1)
    mul $t3, $t1, $t2 # Multiply values
    add $t4, $t4, $t3 # Store multiplied values
    addu $s0, $s0, $t0 # Increment memory addresses.
    addu $s1, $s1, $t0
    beq $s0, $s2, exit # Check if all values have been added. If so, exit.
    j loop # If not, loop again.
exit:
    li $v0, 1 # Print value
    move $a0, $t4
    syscall

