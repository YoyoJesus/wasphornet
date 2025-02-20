# Austin Sternberg
# September 25th, 2024
#
#
#
# Code for Project2-2
# 
#
# This code prompts the user for values of w, x, y, and z.
#
# It calculates (x - y)^3 and compares it with w.
#
# If (x - y)^3 >= w, x is set to y; otherwise, x is set to z.
#
# The value of x is then printed to the console.
# 
# Debugging information is included to verify stored values.

            .data          # Data segment begins
            .align 2       # Align the following data on a word boundary

prompt_w:   .asciiz "Enter value for w: "
prompt_x:   .asciiz "Enter value for x: "
prompt_y:   .asciiz "Enter value for y: "
prompt_z:   .asciiz "Enter value for z: "
output:     .asciiz "The value of x is: "

w:          .float 0.0     # Allocate space for w
x:          .float 0.0     # Allocate space for x
y:          .float 0.0     # Allocate space for y
z:          .float 0.0     # Allocate space for z

            .text          # Code segment begins
            .globl main    # Declare main as global
main:
###############################################################
# Prompt for the value of w
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_w       # Load address of prompt_w into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (w)
            s.s $f0, w             # Store the value of w

###############################################################
# Prompt for the value of x
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_x       # Load address of prompt_x into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f1 (x)
            s.s $f0, x             # Store the value of x

###############################################################
# Prompt for the value of y
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_y       # Load address of prompt_y into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f2 (y)
            s.s $f0, y             # Store the value of y

###############################################################
# Prompt for the value of z
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_z       # Load address of prompt_z into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f3 (z)
            s.s $f0, z             # Store the value of z

###############################################################
# Calculate (x - y)
            l.s $f1, x             # Load x from memory
            l.s $f2, y             # Load y from memory
            sub.s $f4, $f1, $f2    # $f4 = x - y

# Calculate (x - y)^3
            mul.s $f5, $f4, $f4    # $f5 = (x - y)^2
            mul.s $f4, $f5, $f4    # $f4 = (x - y)^3

# Compare (x - y)^3 with w
            l.s $f0, w             # Load w from memory
            c.le.s $f4, $f0        # Compare (x - y)^3 <= w
            bc1t else_label        # Branch to else if true

# Then: Set x to y
            mov.s $f1, $f2         # x = y
            s.s $f1, x             # Store the new value of x
            j end_label            # Jump to end

else_label:
# Else: Set x to z
            l.s $f3, z             # Load z from memory
            mov.s $f1, $f3         # x = z
            s.s $f1, x             # Store the new value of x

end_label:
###############################################################
# Print the value of x
            li $v0, 4              # System call 4 for print string
            la $a0, output         # Load address of output into $a0
            syscall                # Make the system call

            l.s $f1, x             # Load the final value of x from memory
            li $v0, 2              # System call 2 for print float
            mov.s $f12, $f1        # Move x to $f12 for printing
            syscall                # Make the system call

###############################################################
# Exit the program
            li $v0, 10             # System call 10 for exit
            syscall                # Make the system call
###############################################################
