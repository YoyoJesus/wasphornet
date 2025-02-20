# Austin Sternberg
# November 11, 2024
#
#
#
# Code for Lab4-1
# 
# This code implements an adding machine program that repeatedly reads integers
# and adds them into a running sum. The program stops when the input is zero
# and then prints the final sum.
#

.data
    prompt: .asciiz "Enter a number: "
    result_msg: .asciiz "The sum is: "

.text
    .globl main

main:
    # Initialize sum to 0
    li $t0, 0            # $t0 = sum register

read_input:
    # Print prompt
    li $v0, 4            # syscall for print string
    la $a0, prompt       # load address of prompt
    syscall

    # Read an integer
    li $v0, 5            # syscall for read integer
    syscall
    move $t1, $v0        # move input value to $t1

    # Check if the input is zero
    beq $t1, $zero, print_sum  # if input is zero, go to print_sum

    # Add the input to the sum
    add $t0, $t0, $t1    # sum += input

    # Go back to read another input
    j read_input         # jump back to the top of the loop

print_sum:
    # Print the result message
    li $v0, 4            # syscall for print string
    la $a0, result_msg   # load address of result message
    syscall

    # Print the sum
    li $v0, 1            # syscall for print integer
    move $a0, $t0        # move sum to $a0 for printing
    syscall

    # Exit program
    li $v0, 10           # syscall for exit
    syscall
