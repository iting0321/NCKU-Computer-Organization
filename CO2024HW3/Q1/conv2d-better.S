.global conv2d
conv2d:
# a0: address of input
# a1: address of kernel
# a2: w
# a3: h
# a4: ksize
# a5: s

# prologue
        # addi sp, sp, -4
        # sw a0, 0(sp)

# start of your implementation
	li t0,0 # t0=jj
loop_jj:
	bge t0,a2,end

	#loop_ii
	li t1, 0 # t1=ii
loop_ii:
	bge t1, a3,next_jj
	#loop_j
	mv t2, t0 # t2=j
loop_j:
	bge t2, a2, next_ii

	#loop_i
	mv t3, t1 #t3=i
loop_i:
	bge t3, a3, next_j
	
	li t4, 0 # sum=t4
	#loop_n
	li t5, 0 #n=t5
loop_n:
	bge t5, a4, end_loop_n

	#loop_m
	li t6, 0 #m=t6
loop_m:
	bge t6, a4, next_n
	# a6, a7
	add a6, t3, t6 # (i+m)
	mul a6, a6, a2 # (i+m)*w
	add a6, a6, t2 # (i+m)*w + j
	add a6, a6, t5 # (i+m)*w + j+n
	slli a6, a6, 2
	add a6, a6, a0 # address of input[]
	lw  a6, 0(a6) # input[]

	mul a7, a4, t6 # m*ksize
	add a7, a7, t5 # m*ksize + n
	slli a7, a7, 2
	add a7, a7, a1 # address of kernel[]
	lw  a7, 0(a7) # kernel[]

	mul a6,a7, a6 # input[] * kernel[]
	add t4, t4, a6 # sum += input * kernel
	
    	add t6, t6, a5         # m += s
    j loop_m

next_n:

    add t5, t5, a5         # n += s
    j loop_n

end_loop_n:
	mul a6, t3, a2 # i*w
	add a6, a6, t2 # i*w + j
	slli a6, a6, 2
	add a6, a0, a6 
	sw  t4, 0(a6) # input[i*w + j] = sum
	addi t3, t3, 1          # i++
    	j loop_i
next_j:
    addi t2, t2, 1          # j++
    j loop_j

next_ii:
    addi t1, t1, 8         # ii += blockSize
    j loop_ii

next_jj:
    addi t0, t0, 8         # jj += blockSize
    j loop_jj

end:
	
        
# end of your implementation

# epilogue
        # lw a0, 0(sp)
        # addi sp, sp, 4
        ret

