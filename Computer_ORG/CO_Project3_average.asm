.data
promptNum:  .asciiz "Enter the number of values:"
promptVal:  .asciiz "Enter a float value:"
resultMsg:  .asciiz "The Mean of A = "
zeroFloat:  .float 0.0         # Define a constant for 0.0

.text
.globl main
main:
# Prompt the user for the number of values
    li $v0, 4                  # Load syscall for print string
    la $a0, promptNum          # Load prompt
    syscall

# Read integer input for the number of values
    li $v0, 5                  # Load syscall for reading an integer
    syscall
    move $t0, $v0              # Store number in $t0

# Convert integer count to float (to use later in mean calculation)
    mtc1 $t0, $f6              # Move integer in $t0 to $f6
    cvt.s.w $f6, $f6           # Convert integer to float

# Initialize sum value to 0.0
    lwc1 $f4, zeroFloat        # Load 0.0 into $f4 (for summ of floats)

# Loop to collect float numbers and calculate sum
loop:
# Check if we've reached the count
    beqz $t0, end_loop         # Exit loop when $t0 (count) reaches zero

# Prompt the user for each floating-point value
    li $v0, 4                  # Load syscall for print string
    la $a0, promptVal          # Load address of "Enter a float value"
    syscall

# Read floating-point input from the user
    li $v0, 6                  # Load syscall for reading a float
    syscall
    add.s $f4, $f4, $f0        # Add input (in $f0) to sum ($f4)

# Decrement loop counter and repeat
    sub $t0, $t0, 1            # Decrement counter
    j loop                     # Jump back to start of loop


# Calculate mean by dividing sum by count and display result
end_loop:
    div.s $f8, $f4, $f6        # Divide sum ($f4) by count ($f6) to get mean in $f8

# Print the result message "The Mean of A = "
    li $v0, 4                  # Load syscall for print string
    la $a0, resultMsg          # Load address of result message
    syscall

# Print the mean
    mov.s $f12, $f8            # Move mean result to $f12 for printing
    li $v0, 2                  # Load syscall for printing a float
    syscall

# Exit the program
    li $v0, 10                 # Load syscall for exit
    syscall