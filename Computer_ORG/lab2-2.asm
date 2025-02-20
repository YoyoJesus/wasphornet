# Austin Sternberg
# September 25th, 2024
#
#
#
# Code for Project2-2
# 
#
# This code prompts the user for an input type.
# Then asks for two values of that type.
#
# It then uses a temporary memory space to swap the contents of the two values.
#
# The first and second values are then printed to the console.
#

                .data          		# Data segment begins
                .align 2       		# Align the following data on a word boundary

prompt_choice: .asciiz "Enter 1 for string, 2 for integer, 3 for float: "
prompt1:       .asciiz "Enter the first value: "
prompt2:       .asciiz "Enter the second value: "
result1:       .asciiz "After swapping, the first value is: "
result2:       .asciiz "After swapping, the second value is: "
newline:       .asciiz "\n"

string1:       .space 100    		# Allocate space for the first string (up to 100 bytes)
string2:       .space 100   		# Allocate space for the second string (up to 100 bytes)
temp:          .space 100   		# Allocate space for the temporary storage (up to 100 bytes)

              .align 2 
x:            .float 0.0  	        # Allocate space for float x
y:            .float 0.0    		# Allocate space for float y 
tempf:	      .float 0.0    		# Allocate space for float temp

              .text          		# Code segment begins
              .globl main    		# Declare main as global
main:
###############################################################
# Prompt for type: string, integer, or float
            li $v0, 4                   # System call 4 for print string
            la $a0, prompt_choice       # Load address of prompt_choice into $a0
            syscall                     # Make the system call

            li $v0, 5                   # System call 5 for reading an integer
            syscall                  
            move $t0, $v0               # Read the integer into $t0

            li $t1, 1                   # Load immediate 1 into $t1 (for comparison)
            li $t2, 2                   # Load immediate 2 into $t2 (for comparison)
            li $t3, 3                   # Load immediate 3 into $t3 (for comparison)

            beq $t0, $t1, string_input  # If input is 1, go to string_input
            beq $t0, $t2, int_input     # If input is 2, go to int_input
            beq $t0, $t3, float_input   # If input is 3, go to float_input

            j invalid_input             # Jump to invalid_input if not 1, 2, or 3

###############################################################
invalid_input:
# Print error message and reprompt
            li $v0, 4                  # System call 4 for print string
            la $a0, prompt_choice      # Load address of prompt_choice into $a0
            syscall                    # Print the invalid choice message
            j main                     # Jump back to main prompt to retry

###############################################################
# String Input Section
string_input:
# Prompt for the first string
            li $v0, 4                 # System call 4 for print string
            la $a0, prompt1           # Load address of prompt1 into $a0
            syscall                   # Make the system call

            li $v0, 8                 # System call 8 for reading a string
            la $a0, string1           # Load address of string1 into $a0
            li $a1, 100               # Set the maximum number of characters to read
            syscall                   # Make the system call

# Prompt for the second string
            li $v0, 4                # System call 4 for print string
            la $a0, prompt2          # Load address of prompt2 into $a0
            syscall                  # Make the system call

            li $v0, 8                # System call 8 for reading a string
            la $a0, string2          # Load address of string2 into $a0
            li $a1, 100              # Set the maximum number of characters to read
            syscall                  # Make the system call

# Swap the contents of string1 and string2 using temp as a temporary storage
            la $a0, string1          # Load the address of string1 into $a0
            la $a1, temp             # Load the address of temp into $a1
            li $t0, 100              # Set a loop counter for the length of the strings

swap_loop_copy1_to_temp:
            lb $t1, 0($a0)           # Load byte from string1 into $t1
            sb $t1, 0($a1)           # Store byte into temp
            addi $a0, $a0, 1         # Increment the address in $a0
            addi $a1, $a1, 1         # Increment the address in $a1
            addi $t0, $t0, -1        # Decrement the loop counter
            bgtz $t0, swap_loop_copy1_to_temp # Loop until $t0 reaches 0

# Copy string2 into string1
            la $a0, string2          # Load the address of string2 into $a0
            la $a1, string1          # Load the address of string1 into $a1
            li $t0, 100              # Reset the loop counter

swap_loop_copy2_to_1:
            lb $t1, 0($a0)           # Load byte from string2 into $t1
            sb $t1, 0($a1)           # Store byte into string1
            addi $a0, $a0, 1         # Increment the address in $a0
            addi $a1, $a1, 1         # Increment the address in $a1
            addi $t0, $t0, -1        # Decrement the loop counter
            bgtz $t0, swap_loop_copy2_to_1 # Loop until $t0 reaches 0

# Copy temp into string2
            la $a0, temp             # Load the address of temp into $a0
            la $a1, string2          # Load the address of string2 into $a1
            li $t0, 100              # Reset the loop counter

swap_loop_copy_temp_to_2:
            lb $t1, 0($a0)           # Load byte from temp into $t1
            sb $t1, 0($a1)           # Store byte into string2
            addi $a0, $a0, 1         # Increment the address in $a0
            addi $a1, $a1, 1         # Increment the address in $a1
            addi $t0, $t0, -1        # Decrement the loop counter
            bgtz $t0, swap_loop_copy_temp_to_2 # Loop until $t0 reaches 0

# Print the first string after swap
            li $v0, 4                # System call 4 for print string
            la $a0, result1          # Load address of result1 into $a0
            syscall                  # Make the system call

            li $v0, 4                # System call 4 for print string
            la $a0, string1          # Load the swapped string1 into $a0
            syscall                  # Make the system call

# Print a newline after the first string
            li $v0, 4                # System call 4 for print string
            la $a0, newline          # Load address of newline into $a0
            syscall                  # Make the system call

# Print the second string after swap
            li $v0, 4                # System call 4 for print string
            la $a0, result2          # Load address of result2 into $a0
            syscall                  # Make the system call

            li $v0, 4                # System call 4 for print string
            la $a0, string2          # Load the swapped string2 into $a0
            syscall                  # Make the system call
            j end_program            # Jump to the end of the program

###############################################################
# Integer Input Section
int_input:
# Prompt for the first integer
            li $v0, 4               # System call 4 for print string
            la $a0, prompt1         # Load address of prompt1 into $a0
            syscall                 # Make the system call

            li $v0, 5               # System call 5 for reading an integer
            syscall
            move $t1, $v0           # Read input into $t1 (first integer)

# Prompt for the second integer
            li $v0, 4               # System call 4 for print string
            la $a0, prompt2         # Load address of prompt2 into $a0
            syscall                 # Make the system call

            li $v0, 5               # System call 5 for reading an integer
            syscall
            move $t2, $v0           # Read input into $t2 (second integer)

# Swap integers
            move $t0, $t1           # Move first integer to temp
            move $t1, $t2           # Move second integer to first
            move $t2, $t0           # Move temp to second

# Print the first integer after swap
            li $v0, 4               # System call 4 for print string
            la $a0, result1         # Load address of result1 into $a0
            syscall                 # Make the system call

            li $v0, 1               # System call 1 for print integer
            move $a0, $t1           # Move the first swapped integer to $a0
            syscall                 # Print first integer

# Print a newline after the first integer
            li $v0, 4               # System call 4 for print string
            la $a0, newline         # Load address of newline into $a0
            syscall                 # Make the system call

# Print the second integer after swap
            li $v0, 4               # System call 4 for print string
            la $a0, result2         # Load address of result2 into $a0
            syscall                 # Make the system call

            li $v0, 1               # System call 1 for print integer
            move $a0, $t2           # Move the second swapped integer to $a0
            syscall                 # Print second integer

            j end_program           # Jump to the end of the program

###############################################################
# Float Input Section
float_input:
# Prompt for the value of x (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt1        # Load address of prompt_x into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (x)
            s.s $f0, x             # Store the value of x

# Prompt for the value of y (float)
            li $v0, 4              # System call 4 for print string
            la $a0, prompt2        # Load address of prompt_y into $a0
            syscall                # Make the system call

            li $v0, 6              # System call 6 for reading a float
            syscall                # Read input into $f0 (y)
            s.s $f0, y             # Store the value of y

# Swap floats
            l.s $f1, x		   # Load value of x into $f1
            s.s $f1, tempf	   # Save value of $f1 into tempf
            
            l.s $f1, y		   # Load value of y into $f1
            s.s $f1, x		   # Save value of $f1 into x
            
            l.s $f1, tempf         # Load value of tempf into $f1
            s.s $f1, y		   # LSave value of $f1 into y

# Print the first float after swap
           li $v0, 4               # System call 4 for print string
           la $a0, result1         # Load address of output into $a0
           syscall                 # Make the system call

           l.s $f1, x              # Load the final value of x from memory
           li $v0, 2               # System call 2 for print float
           mov.s $f12, $f1         # Move x to $f12 for printing
           syscall                 # Make the system call

# Print a newline after the first float
            li $v0, 4              # System call 4 for print string
            la $a0, newline        # Load address of newline into $a0
            syscall                # Make the system call

# Print the second float after swap
           li $v0, 4              # System call 4 for print string
           la $a0, result2        # Load address of output into $a0
           syscall                # Make the system call

           l.s $f1, y             # Load the final value of x from memory
           li $v0, 2              # System call 2 for print float
           mov.s $f12, $f1        # Move x to $f12 for printing
           syscall                # Make the system call

###############################################################
# End of Program
end_program:
            li $v0, 10            # System call 10 for exit
            syscall               # Make the system call
