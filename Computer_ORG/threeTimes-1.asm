# Austin Sternberg
# September 18th, 2024
#
#
#
# Starter code for threeTimes.asm
# Put in comments your name and date please.  You will be
# revising this code.
#
# Dianne Foreback 
# 
# 
# This code displays the authors name (you must change
# outpAuth to display YourFirstName and YourLastName".
#
# The code then prompts the user for 3 integer values.
# The code outputs the summation of these 3 values multiplied by 3.
#
# In MARS, make certain in "Settings" to check
# "popup dialog for input syscalls 5,6,7,8,12"
#
            .data      # data segment
	    .align 2   # align the next string on a word boundary
outpAuth:   .asciiz  "This is Austin Sternberg presenting threeTimes.\n"
outpPrompt: .asciiz  "Please enter an integer: "
	    .align 2   #align next prompt on a word boundary
outpStr:    .asciiz  "The sum of your numbers multiplied by 3 is: "
            .align 2   # align users input on a word boundary
#
# main begins
            .text      # code section begins
            .globl	main 
main:  
###############################################################
# system call to display the author of this code
	 la $a0,outpAuth	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
	 
#
# system call to prompt user for input
	 la $a0,outpPrompt	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
###############################################################
# write a system call to read the user's integer value
	 li $v0, 5		# system call 5 code for reading first integer
	 syscall
	 move $t1, $v0		# store the first integer in $t1
	 
# Same for integer 2
	 li $v0, 4		# system call 4 for print string needs 4 in $v0 
	 syscall
	 
	 li $v0, 5		# system call 5 code for reading second integer
	 syscall
	 move $t2, $v0		# store the second integer in $t2
	 
# Same for integer 3
	 li $v0, 4		# system call 4 for print string needs 4 in $v0 
	 syscall
	 
	 li $v0, 5		# system call 5 code for reading third integer
	 syscall
	 move $t3, $v0		# store the third integer in $t3
	 
# We have not studied looping, so you will need to repeat the prompt for input
# and do the calculation as you see fit
# do the summation
	add $t4, $t1, $t2	# add $t1 and $t2 - store value in $t4
	add $t4, $t4, $t3	# add $t4 and $t3 - store value in $t4
	
# do the multiplication
	li $t5, 3		# load 3 into $t5
	mul $t6, $t4, $t5	# multiply $4 by $5 - store in $t6

#
# system call to display "The sum of your numbers multiplied by 3 is: "
	 la $a0,outpStr 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  	
################################################################
# write a system call to display the calculation
	move $a0, $t6		# move the final result in $t6 to $a0 for printing
	li $v0, 1		# system call 1 for print integer
	syscall

#
# Exit gracefully
         li   $v0, 10       # system call for exit
         syscall            # close file
###############################################################
