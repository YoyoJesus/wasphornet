# Austin Sternberg
# September 25th, 2024
#
#
#
# Code for Project2-1
# 
# This code prompts for type of input (float or integer)
# It then prompts the user for values of w, x, y, and z.
#
# It calculates (x - y) and compares it with w.
#
# If (x - y) >= w, x is set to y; otherwise, x is set to z.
#
# The value of x is then printed to the console.
#
            	.data          # Data segment begins
            	.align 2       # Align the following data on a word boundary

prompt_choice:  .asciiz "Enter 1 for float, 2 for integer: "
prompt_w:       .asciiz "Enter value for w: "
prompt_x:       .asciiz "Enter value for x: "
prompt_y:       .asciiz "Enter value for y: "
prompt_z:       .asciiz "Enter value for z: "
output:         .asciiz "The value of x is: "

invalid_prompt: .asciiz "Invalid choice. Please enter 1 for float or 2 for integer.\n"

float:		.asciiz "FLOAT"
integer:	.asciiz "INTEGER"

w:          	.float 0.0     # Allocate space for float w
x:          	.float 0.0     # Allocate space for float x
y:          	.float 0.0     # Allocate space for float y
z:          	.float 0.0     # Allocate space for float z

            	.text          # Code segment begins
            	.globl main    # Declare main as global
main:
###############################################################
# Prompt for number type: 1 for float, 2 for integer
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_choice  # Load address of prompt_choice into $a0
            syscall                # Make the system call

            li $v0, 5              # System call 5 for reading an integer
            syscall                
            move $t0, $v0          # Read the integer into $t0

            li $t1, 1              # Load immediate 1 into $t1 (for comparison)
            li $t2, 2              # Load immediate 2 into $t2 (for comparison)

            beq $t0, $t1, float_input  # If input is 1, go to float_input
            beq $t0, $t2, int_input    # If input is 2, go to int_input

###############################################################
invalid_input:
# Print error message and reprompt
            li $v0, 4              # System call 4 for print string
            la $a0, invalid_prompt # Load address of invalid_prompt into $a0
            syscall                # Print the invalid choice message

            j main                 # Jump back to main prompt to retry

###############################################################
# Float Input Section
float_input:
# Prompt for the value of w (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_w       # Load address of prompt_w into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (w)
            s.s $f0, w             # Store the value of w

# Prompt for the value of x (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_x       # Load address of prompt_x into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (x)
            s.s $f0, x             # Store the value of x

# Prompt for the value of y (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_y       # Load address of prompt_y into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (y)
            s.s $f0, y             # Store the value of y

# Prompt for the value of z (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_z       # Load address of prompt_z into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (z)
            s.s $f0, z             # Store the value of z

# Calculate (x - y)
            l.s $f1, x             # Load x from memory
            l.s $f2, y             # Load y from memory
            sub.s $f4, $f1, $f2    # $f4 = x - y

# Compare (x - y) with w
            l.s $f0, w             # Load w from memory
            c.le.s $f4, $f0        # Compare (x - y) <= w
            bc1t else_label        # Branch to else if true

# Then: Set x to y
            mov.s $f1, $f2         # x = y
            s.s $f1, x             # Store the new value of x
            j end_label            # Jump to end

else_label:
# Else: Set x to z
            l.s $f3, z             # Load z from memory
            mov.s $f1, $f3         # x = z
            s.s $f1, x             # Store the new value of x...
            j end_label            # Jump to end after float section

###############################################################
# Integer Input Section
int_input:
# Prompt for the value of w (integer)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_w       # Load address of prompt_w into $a0
            syscall                # Make the system call

            li $v0, 5              # System call 5 for reading an integer
            syscall
            move $t1, $v0          # Read input into $t1 (w)

# Prompt for the value of x (integer)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_x       # Load address of prompt_x into $a0
            syscall                # Make the system call

            li $v0, 5              # System call 5 for reading an integer
            syscall
            move $t2, $v0          # Read input into $t2 (x)

# Prompt for the value of y (integer)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_y       # Load address of prompt_y into $a0
            syscall                # Make the system call

            li $v0, 5              # System call 5 for reading an integer
            syscall
            move $t3, $v0          # Read input into $t3 (y)

# Prompt for the value of z (integer)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt_z       # Load address of prompt_z into $a0
            syscall                # Make the system call

            li $v0, 5              # System call 5 for reading an integer
            syscall
            move $t4, $v0          # Read input into $t4 (z)

###############################################################
# Integer Calculation and Comparison Section
# Calculate (x - y)
            sub $t5, $t2, $t3      # $t5 = x - y

# Compare (x - y) with w
            ble $t5, $t1, else_label_int # Branch if (x - y) <= w

# Then: Set x to y
            move $t2, $t3          # x = y
            j end_label_int        # Jump to end

else_label_int:
# Else: Set x to z
            move $t2, $t4          # x = z

end_label_int:
###############################################################
# Print the value of x (integer)
            li $v0, 4              # System call 4 for print string
            la $a0, output         # Load address of output into $a0
            syscall                # Make the system call

            move $a0, $t2          # Move the final value of x to $a0
            li $v0, 1              # System call 1 for print integer
            syscall                # Make the system call

	    j end_exit		   # Jump to end
###############################################################
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
end_exit:
# Exit the program
            li $v0, 10             # System call 10 for exit
            syscall                # Make the system call
###############################################################
