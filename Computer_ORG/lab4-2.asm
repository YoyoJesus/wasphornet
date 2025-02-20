# Austin Sternberg
# November 11, 2024
#
#
#
# Code for Lab4-2
# 
# This code reads three integers from the user.
# It then calculates and prints the sum of the largest two distinct integers.
#
# The program compares the three integers, selects the two largest distinct integers, 
# and calculates their sum.
#

.data
    prompt: .asciiz "Enter an integer: "
    result_msg: .asciiz "The sum of the largest two integers is: "

.text
    .globl main

main:
    # Prompt and read the first integer (a)
    li    $v0, 4             # syscall for print string
    la    $a0, prompt        # load address of prompt
    syscall

    li    $v0, 5             # syscall for read integer
    syscall
    move  $t0, $v0           # store first integer in $t0 (a)

    # Prompt and read the second integer (b)
    li    $v0, 4             # syscall for print string
    la    $a0, prompt        # load address of prompt
    syscall

    li    $v0, 5             # syscall for read integer
    syscall
    move  $t1, $v0           # store second integer in $t1 (b)

    # Prompt and read the third integer (c)
    li    $v0, 4             # syscall for print string
    la    $a0, prompt        # load address of prompt
    syscall

    li    $v0, 5             # syscall for read integer
    syscall
    move  $t2, $v0           # store third integer in $t2 (c)

    # Compare and find the two largest distinct integers
    # First, sort the values
    # Find largest and second largest

    # Initialize $t4 as the first integer (a) and $t5 as second
    move  $t4, $t0           # largest (a)
    move  $t5, $t1           # second largest (b)

        # Compare a and b
    bge   $t0, $t1, check_ab # If a ($t0) >= b ($t1), keep $t4 and $t5 as they are, jump to check_ab
    move  $t4, $t1           # If b > a, set largest ($t4) to b ($t1)
    move  $t5, $t0           # Set second largest ($t5) to a ($t0)
check_ab:
    # Compare c with the two largest numbers so far ($t4 and $t5)
    bge   $t2, $t4, check_ac # If c ($t2) >= the largest value ($t4), jump to check_ac
    bge   $t2, $t5, check_bc # If c ($t2) >= second largest ($t5) but < largest ($t4), jump to check_bc
    j     end_check          # Jump to end_check if neither of the previous conditions are true
check_ac:
    move  $t5, $t4           # Move current largest ($t4) to second largest ($t5)
    move  $t4, $t2           # Update largest ($t4) to c ($t2)
    j     end_check          # Jump to the end of the checks
check_bc:
    move  $t5, $t2           # Update the second largest ($t5) to c ($t2)
end_check:

    # Add the two largest distinct numbers
    add   $t6, $t4, $t5      # sum the two largest integers and store in $t6

    # Print the result message
    li    $v0, 4             # syscall for print string
    la    $a0, result_msg    # load address of result message
    syscall

    # Print the sum
    li    $v0, 1             # syscall for print integer
    move  $a0, $t6           # move sum into $a0 for printing
    syscall

    # End the program
    li    $v0, 10            # syscall for exit
    syscall
