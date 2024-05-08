"li t0,0\n"
"addi %[lw_cnt], %[lw_cnt], 1\n"

"loop:\n"
	
	"lh t2, 0(%[h])\n"
	"lh t3, 0(%[x])\n"
	"addi %[lw_cnt], %[lw_cnt], 2\n"

	"mul t2, t2,t3\n"
	"addi %[mul_cnt], %[mul_cnt], 1\n"
	
	"add t2, t2, %[id]\n"
	"addi %[add_cnt], %[add_cnt], 1\n"

	"sh t2, 0(%[y])\n"
	"addi %[sw_cnt], %[sw_cnt], 1\n"

	"addi %[h], %[h], 2\n"
	"addi %[x], %[x], 2\n"
	"addi %[y], %[y], 2\n"
	"addi %[add_cnt], %[add_cnt], 3\n"
	
	"addi t0, t0, 1\n"
	"addi %[add_cnt], %[add_cnt], 1\n"

"addi %[others_cnt], %[others_cnt], 1\n"
"bne t0, %[arr_size], loop\n"





