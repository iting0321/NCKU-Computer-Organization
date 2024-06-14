.global conv2d

conv2d:

# a0: address of input

# a1: address of kernel

# a2: w

# a3: h

# a4: ksize

# a5: s



# prologue

        # addi sp, sp , -4

        # sw a0, 0(sp)



# start of your implementation

# Initializations
    sub t0, a2, a4      # t0 = w - ksize
    sub t1, a3, a4      # t1 = h - ksize
    li  t2, 0           # t2 = j = 0

	lw x18, 0(a1)
	lw x19, 4(a1)
	lw x20, 8(a1)
	lw x21, 12(a1)
	lw x22, 16(a1)
	lw x23, 20(a1)
	lw x24, 24(a1)
	lw x25, 28(a1)
	lw x26, 32(a1)

# Outer loop for j
1:  bgt t2, t0, 3f      # if j > (w - ksize) exit outer loop

# Inner loop for i
    li  t3, 0           # t3 = i = 0
2:  bgt t3, t1, 4f      # if i > (h - ksize) exit inner loop

# Initialize sum
    li  t4, 0           # t4 = sum = 0

# Convolution sum calculation
    # Unrolled for ksize = 3 and s = 1
    # First row
    #lw  t6, 0(a1)       # kernel[0 * ksize + 0]
    mul t5, t3, a2      # i*w
    add t5, t5, t2      # i*w+j
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x18
    add t4, t4, t5

    #lw  t6, 4(a1)       # kernel[0 * ksize + 1]
    mul t5, t3, a2      # i*w
    add t5, t5, t2      # i*w+j
    addi t5, t5, 1
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x19
    add t4, t4, t5

    #lw  t6, 8(a1)       # kernel[0 * ksize + 2]
    mul t5, t3, a2      # i*w
    add t5, t5, t2      # i*w+j
    addi t5, t5, 2
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x20
    add t4, t4, t5

    # Second row
    #lw  t6, 12(a1)      # kernel[1 * ksize + 0]
    add t5, t3, zero
    addi t5, t5, 1      # i+1
    mul t5, t5, a2      # (i+1)*w
    add t5, t5, t2      # (i+1)*w+j
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x21
    add t4, t4, t5

    #lw  t6, 16(a1)      # kernel[1 * ksize + 1]
    add t5, t3, zero
    addi t5, t5, 1      # i+1
    mul t5, t5, a2      # (i+1)*w
    add t5, t5, t2      # (i+1)*w+j
    addi t5, t5, 1
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x22
    add t4, t4, t5

    #lw  t6, 20(a1)      # kernel[1 * ksize + 2]
    add t5, t3, zero
    addi t5, t5, 1      # i+1
    mul t5, t5, a2      # (i+1)*w
    add t5, t5, t2      # (i+1)*w+j
    addi t5, t5, 2
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x23
    add t4, t4, t5

    # Third row
    #lw  t6, 24(a1)      # kernel[2 * ksize + 0]
    add t5, t3, zero
    addi t5, t5, 2      # i+2
    mul t5, t5, a2      # (i+2)*w
    add t5, t5, t2      # (i+2)*w+j
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x24
    add t4, t4, t5

    #lw  t6, 28(a1)      # kernel[2 * ksize + 1]
    add t5, t3, zero
    addi t5, t5, 2      # i+2
    mul t5, t5, a2      # (i+2)*w
    add t5, t5, t2      # (i+2)*w+j
    addi t5, t5, 1
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x25
    add t4, t4, t5

    #lw  t6, 32(a1)      # kernel[2 * ksize + 2]
    add t5, t3, zero
    addi t5, t5, 2      # i+2
    mul t5, t5, a2      # (i+2)*w
    add t5, t5, t2      # (i+2)*w+j
    addi t5, t5, 2
    slli t5, t5, 2
    add t5, t5, a0
    lw t5, 0(t5)
    mul t5, t5, x26
    add t4, t4, t5

# Store the result in input[i * w + j]
    mul t5, t3, a2      # t5 = i * w
    add t5, t5, t2      # t5 = i * w + j
    slli t5, t5, 2      # t5 = 4 * (i * w + j)
    add t5, a0, t5      # t5 = address of input[i * w + j]
    sw t4, 0(t5)        # input[i * w + j] = sum

# Increment i and continue inner loop
    addi t3, t3, 1
    ble t3, t1, 2b

# Increment j and continue outer loop
    addi t2, t2, 1
    ble t2, t0, 1b

3:  # End of outer loop
4:  # End of inner loop

        

# end of your implementation



# epilogue

        # lw a0, 0(sp)

        # addi sp, sp, 4

        ret
