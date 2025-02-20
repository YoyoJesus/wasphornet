# Dianne Foreback
# Revised and added code taken from Hennesey and Patterson 5th edition
# to work with this simulator.
#
# Prompts a user to enter a Fahrenheit temperature as a floating point.
# Displays the converted temperature in Celcius.
# 10/28/2015

.data
const5:	 	.float 5.0    # store a floating point constant 5.0 
const9: 	.float 9.0
const32:	.float 32.0
     	    .align 2   # align the next string on a word boundary
	        .space 100
prompt:     .asciiz  "Please enter Farh as a float:\n"
	        .align 2   #align next prompt on a word boundary

constfahr:  .float 1   # will hold the user's input 

	        .text
	        .globl	main
main:  
###############################################################
# system call to prompt user
		la $a0,prompt		# system call 4 for print string needs address of string in $a0
		li $v0,4			# system call 4 for print string needs 4 in $v0
		syscall	
###############################################################
# system call to store user input of a float into register $f0
		li $v0,6		     # system call 6 for reading a float is required in $v0
		syscall	             # the user's input is placed in register $f0
###############################################################
# do the conversion from Fahrenheit to Celcius
		mov.s $f12, $f0              # load the value wanting to convert from Fahr to Celcius
f2c:    lwc1 $f16, const5($zero)     #load 5.0
		lwc1 $f18, const9($zero)     # load 9.0
		div.s $f16, $f16, $f18       # $f16 =  5.0 / 9.0
		lwc1 $f18, const32($zero)    # load 32.0
		sub.s $f18, $f12, $f18       #  $f18 = fahr - 32
		mul.s $f0, $f16, $f18        # $f0 gets the result of ((5.0/9.0)*(fahr - 32.0))
# http://www.h-schmidt.net/FloatConverter/IEEE754.html  can be used to convert the result in $f0
# from single precision float to a decimal number (we should know how to do by hand too!)

###############################################################
# system call to print the float in register $f12
        mov.s $f12, $f0
		li $v0,2		     # system call 2 to print a float is required in $v0
        syscall	             # the user's input is placed in register $f0
###############################################################
# Exit gracefully
         li   $v0, 10       # system call for exit
         syscall            # close file
###############################################################
