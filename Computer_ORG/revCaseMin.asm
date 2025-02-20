# Starter code for reversing the case of a 30 character input.
# Put in comments your name and date please.  You will be
# revising this code.
#
# Students should modify this code
# 
# This code displays the authors name (you must change
# outpAuth to display Austin Sternberg".
#
# The code then prompts the user for input
# stores the user input into memory "varStr"
# then displays the users input that is stored in"varStr" 
#
# You will need to write code per the specs for 
# procedures main, revCase and function findMin.
#
# revCase will to reverse the case of the characters
# in varStr.  You must use a loop to do this.  Another buffer
# varStrRev is created to hold the reversed case string.
# 
# Please refer to the specs for this project, this is just starter code.
#
# In MARS, make certain in "Settings" to check
# "popup dialog for input syscalls 5,6,7,8,12"
#

################################################################
# Reverse Case and Find Min/Max ASCII Character Program
# Austin Sternberg
# 11/25/2024
################################################################
            .data      # data segment
	    .align 2   # align the next string on a word boundary
outpAuth:   .asciiz  "This is Austin Sternberg presenting revCaseMin.\n"
outpPrompt: .asciiz  "Please enter 30 characters (upper/lower case mixed):\n"
	    .align 2   #align next prompt on a word boundary 
outpStr:    .asciiz  "\nYou entered the string: "
            .align 2   # align users input on a word boundary
varStr:     .space 32  # will hold the user's input string thestring of 20 bytes 
                       # last two chars are \n\0  (a new line and null char)
                       # If user enters 31 characters then clicks "enter" or hits the
                       # enter key, the \n will not be inserted into the 21st element
                       # (the actual users character is placed in 31st element).  the 
                       # 32nd element will hold the \0 character.
                       # .byte 32 will also work instead of .space 32
            .align 2   # align next prompt on word boundary
outpStrRev: .asciiz   "\nYour string in reverse case is: "
            .align 2   # align the output on word boundary
varStrRev:  .space 32  # reserve 32 characters for the reverse case string
	    .align 2   # align  on a word boundary
outMin: .asciiz    "\nThe min ASCII character after reversal is: "

### Extra Credit Stuff:
outMax:  .asciiz    "\nThe max ASCII character after reversal is: "
outDiff: .asciiz    "\nThe difference between max and min ASCII values is: "
asciiParenOpen: .asciiz " ("
asciiParenClose: .asciiz ")"

#
            .text      # code section begins
            .globl	main 
main:  
#
# system call to display the author of this code
#
	 la $a0,outpAuth	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	

#
# system call to prompt user for input
#
	 la $a0,outpPrompt	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
#
# system call to store user input into string thestring
#
	li $v0,8		# system call 8 for read string needs its call number 8 in $v0
        			# get return values
	la $a0,varStr    	# put the address of thestring buffer in $t0
	li $a1,32 	        # maximum length of string to load, null char always at end
				# but note, the \n is also included providing total len < 22
        syscall
#
# system call to display "You entered the string: "
#
	 la $a0,outpStr 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  	
#
# system call to display user input that is saved in "varStr" buffer
#
	 la $a0,varStr  	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall	
#
# Your code to invoke revCase goes next	 
#
	jal revCase
# Code to calculate and print max, min, and difference starts here

	# Find min character
	addiu $sp, $sp, -8        # Allocate 2 words to stack
	sw   $ra, 4($sp)
	jal findMin
	lw   $v0, ($sp)           # Retrieve min value
	move $t9, $v0             # Store min value in $t9

	# Display min ASCII character
	la $a0, outMin
	li $v0, 4
	syscall
	
	move $a0, $t9             # Print the min character
	li $v0, 11
	syscall
	
	# Display min ASCII value
	la $a0, asciiParenOpen
	li $v0, 4
	syscall
	
	move $a0, $t9             # ASCII value of min (in $t9)
	li $v0, 1                 # Print integer syscall
	syscall
	
	la $a0, asciiParenClose
	li $v0, 4
	syscall

	# Find max character
	jal findMax
	lw   $v0, 4($sp)          # Retrieve max value
	move $t8, $v0             # Store max value in $t8

	# Display max ASCII character
	la $a0, outMax
	li $v0, 4
	syscall
	
	move $a0, $t8             # Print the max character
	li $v0, 11
	syscall
	
	# Display max ASCII value
	la $a0, asciiParenOpen
	li $v0, 4
	syscall
	
	move $a0, $t8             # ASCII value of max (in $t8)
	li $v0, 1                 # Print integer syscall
	syscall
	
	la $a0, asciiParenClose
	li $v0, 4
	syscall

	# Calculate and display difference
	sub $t1, $t8, $t9         # Difference = max - min
	la $a0, outDiff
	li $v0, 4
	syscall
	
	move $a0, $t1             # Print the difference value
	li $v0, 1                 # Print integer syscall
	syscall

# Exit gracefully from main
	li $v0, 10
	syscall         
         
################################################################
# revCase() procedure can go next
################################################################
#  Write code to reverse the case of the string.  The base address of the
# string should be in $a0 and placed there by main().  main() should also place into
# $a1 the number of characters in the string.
#  You will want to have a label that main() will use in its jal 
# instruction to invoke revCase, perhaps revCase:
#
revCase:

	li $t3, 0		#loop counter initialized
	la $t0, varStr		
	la $t2, varStrRev	#pointing to output string
	j While
	
While:	beq $t3, $a1, ExitRevCase
	lbu $t1, 0($t0)
	blt $t1, 64, LoopCounter     #ignores any lower ascii values
	blt $t1, 95, uppercaseCheck  #capitals will be less than 95 ascii value
	j lowercaseCheck
	
LoopCounter:
	sb $t1, 0($t2)
	addi $t0, $t0, 1
	addi $t2, $t2, 1
	addi $t3, $t3, 1
	j While
	
uppercaseCheck:
	add $t1, $t1, $a1  
	j LoopCounter
	
lowercaseCheck:
	sub $t1, $t1, $a1
	j LoopCounter

#
################################################################
# system call to display "Your string in reverse case is: "
ExitRevCase:

# After reversing the string, you may print it with the following code.
# This is the system call to display "Your string in reverse case is: "
	 la $a0,outpStrRev 	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall  	
	# system call to display the user input that is in reverse case saved in the varRevStr buffer
	 la $a0,varStrRev  	# system call 4 for print string needs address of string in $a0
	 li $v0,4		# system call 4 for print string needs 4 in $v0
	 syscall
	
#
# Your code to invoke findMin() can go next
	addiu $sp, $sp, -8	#allocating 2  words to stack
	sw   $ra, 4($sp)
	jal findMin
	lw   $v0, ($sp)
	lw $ra, 4($sp)
	addiu $sp, $sp, 8	#deallocates stack
	
# Your code to return to the caller main() can go next
 	move $t9, $v0		#storing min value to a register
	
	jr $ra 


################################################################
# findMin() function can go next
################################################################
#  Write code to find the minimum character in the string.  The base address of the
# string should be in $a0 and placed there by revCase.  revCase() should also place into
# $a1 the number of characters in the string.
#  You will want to have a label that revCase() will use in its jal 
# instruction to invoke revCase, perhaps findMin:
#
findMin:
#check if character is less than next character in array. if it is, set it to output value
	
	li $t3, 0		#loop counter initialized for findmin
	la $t2, varStrRev	#initialize pointer to beginning of output string
	lb $t1, 0($t2)
	move $t9, $t1
	j loopCheck
	
	
loopCheck:	
	beq $t3, $a1, exitFindMin
	lb $t1, 0($t2)
	blt $t1, 64, nextChar  #ignores any lower ascii values
	blt  $t1, $t9, foundLess 
	j nextChar
	
nextChar: 
	addi $t2, $t2, 1
	addi $t3, $t3, 1
	j loopCheck
	
foundLess:
	move $t9, $t1
	j nextChar

exitFindMin:

# write use a loop and find the minimum character
# system call to display "The min ASCII character after reversal is:  "
 	move $v0, $t9	#moving min value to $v0
	sw   $v0, ($sp)  #saving minimum value to stack
	
# return to the caller
	jr $ra		#return to revCase

### Extra Credit Function
################################################################
# findMax() function can go next
################################################################
# This function finds the maximum character in the string.
# It is structured similarly to `findMin`.

findMax:
	li $t3, 0          # Loop counter initialized for findMax
	la $t2, varStrRev  # Initialize pointer to the beginning of reversed string
	lb $t1, 0($t2)     # Load the first character
	move $t8, $t1      # Set initial max to the first character
	j maxLoopCheck
	
maxLoopCheck:
	beq $t3, $a1, exitFindMax  # Exit loop if end of string
	lb $t1, 0($t2)            # Load current character
	blt $t1, 64, maxNextChar  # Ignore lower ASCII values
	bgt $t1, $t8, foundMax    # If current character > max, update max
	j maxNextChar
	
maxNextChar:
	addi $t2, $t2, 1          # Move to next character
	addi $t3, $t3, 1
	j maxLoopCheck
	
foundMax:
	move $t8, $t1             # Update max value
	j maxNextChar
	
exitFindMax:
	move $v0, $t8             # Move max value to $v0
	sw   $v0, 4($sp)          # Save max value to stack
	jr $ra                    # Return to caller
