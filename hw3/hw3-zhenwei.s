.globl main
.data	
		.align 5
  	array: .asciiz "Joe"
		.align 5
		.asciiz "Jenny"
		.align 5
		.asciiz "Jill"
		.align 5
		.asciiz "John"
		.align 5
		.asciiz "Jeff"
		.align 5
		.asciiz "Joyce"
		.align 5
		.asciiz "Jerry"
		.align 5
		.asciiz "Janice"
		.align 5
		.asciiz "Jake"
		.align 5
		.asciiz "Jonna"
		.align 5
		.asciiz "Jack"
		.align 5
		.asciiz "Jocelyn"
		.align 5
		.asciiz "Jessie"
		.align 5
		.asciiz "Jess"
		.align 5
		.asciiz "Janet"
		.align 5
		.asciiz "Jane"
		.align 5
				
	nextline: .asciiz "\n"
  	space: .asciiz " "
	data: .space 64
.text

main:
	la $t0, array  #load array to t0
	la $t1, data   #load space to t1
	li $t2, 0      #set intialize start index
        li $t3, 16     #set intialize end index
        jal intialize  #jump to intialize
	li $a0, 0      #set print start index
        li $a1, 64     #set print end index
        jal print      #print start list
	jal insertsort #jump to insertsort
	li $a0, 0      #set print start index
        li $a1, 64     #set print end index
        jal print      #print sorted list
	li $v0,10      # exit
	syscall

intialize:
	sw $t0, data($t2)   #save t0 on $t2 address of data to  
	addi $t2,$t2,4      #t2 add 4 prepare for next loop 
	addi $t0,$t0,32     #t0 add 32 prepare for next loop
	addi $t3,$t3,-1     #t3 -1 prepare for next loop
	bgtz $t3,intialize  #if t3>=0 continue loop
	jr $ra              #go back

	
insertsort:
	addi $sp, $sp, -4  # open stack
      	sw $ra, 0($sp)     # save return address at 0(sp)
	la $t0, data       # load data to t0
     	li $t2, 1          # set loop index i = 1
     	
     	
    loop0:
    	bge $t2, 16, stackclose  # if (i >= 16) close ctack and finish loop
    	addi $t3, $t2, -1        # j = i - 1
    	mul $s0, $t2, 4          # set s0 as 4byte
    	add $s0, $s0, $t0        # *value = a[i]
    	lw $t4, ($s0)            # load word of s0 to t4 
    	jal loop1                #jump to loop1
    	
    loop1:
    	bltz  $t3, endloop1      #if j < 0, end loop1 
    	mul $s0, $t3, 4          #set s0 as 4byte
    	add $s0, $s0, $t0        # get a[j] 
    	lw $t5, ($s0)   	 #load word of s0 to t5 
    	move $s0, $t0            # save t0
    	move $s1, $t1            # save t1
    	move $s2, $t2            # save t2
    	move $s3, $t3            # save t3
    	move $t0, $t4            # move t4 to t0
    	move $t1, $t5            # move t5 to t1
    	jal str_lt               # jump to str_lt
    	move $t0, $s0            # move back t0
    	move $t1, $s1            # move back t1
    	move $t2, $s2            # move back t2
    	move $t3, $s3            # move back t3
    	beqz $v0, endloop1       # if (!str_lt()) end
    	
    	add $s0, $t3, 1          # j + 1
    	mul $s0, $s0, 4          #set s0 as 4byte
    	add $s0, $s0, $t0        # get a[j + 1]
    	sw $t5, ($s0)            # a[j+1] = a[j]
    	addi $t3, $t3, -1        # t3 -1
    	j loop1                  #continue loop
    	
    endloop1:
     	addi $s0, $t3, 1         # j + 1
     	mul $s0, $s0, 4          #set s0 as 4byte
     	add $s0, $s0, $t0        # get a[j + 1]
     	sw $t4, ($s0)            # a[j+1] = value
     	addi $t2, $t2, 1         # i++
   	j loop0
   	
    stackclose:
     	lw $ra, 0($sp)          # restore return address
    	addi $sp, $sp, 4        # close stack
    	jr $ra                  # return
    	
 str_lt:                       
      addi $sp, $sp, -4         # open stack
      sw $ra, 0($sp)            # save ra to 0(sp)
      
  loop2:
        lb $t2, 0($t0)         # load *x to t2
        lb $t3, 0($t1)         # load *y to t3
        beqz $t2, return1      # if *x == '\0', return 1
        beqz $t3, return0      # if *y == '\0', return 0
        blt $t2, $t3, return1  # if ( *x < *y ) return 1
        blt $t3, $t2, return0  # if ( *x < *y ) return 0
        addi $t0, $t0, 1       # x++ 
        addi $t1, $t1, 1       # y++ 
        j loop2                # continue loop

  return0:
    	 li $v0, 0             # return 0
    	 j stackclose2
  return1:
    	 li $v0, 1             # return 1
    	 
  stackclose2:
    	 lw $ra, 0($sp)    # restore ra
    	 addi $sp, $sp, 4  # close stack
    	 jr $ra            # return

print:
beq $a0, $a1, next    # if a0 == a1, print next line
move $t0, $a0             # save the value of a0
lw $a0, data($a0)         # load word at $a0 address of data
li $v0, 4
syscall                   # print the word
la $a0, space
li $v0, 4
syscall                   #print space
addi $a0, $t0, 4 
j print                   #continue loop

next:	
la $a0, nextline
li $v0, 4                 # print the '\n'
syscall
jr $ra                    #return
