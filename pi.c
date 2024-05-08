"li t1,0\n\t" 
"addi %[lw_cnt],%[lw_cnt],3\n\t"
"li t4,-1\n\t"
"li t5,1\n\t"
"fcvt.d.w f1,t5\n\t"
"addi %[others_cnt],%[others_cnt],1\n\t"

"loop:\n\t"

	"add t3,t1,t1\n\t" 
	"addi %[add_cnt],%[add_cnt],1\n\t"

	"addi t3,t3,1\n\t" 
	"addi %[add_cnt],%[add_cnt],1\n\t"

	"fcvt.d.w f2,t3\n\t"
	"addi %[others_cnt],%[others_cnt],1\n\t"

	"fdiv.d f2,f1,f2\n\t" 
	"addi %[div_cnt],%[div_cnt],1\n"

	"fadd.d %[pi],f2,%[pi]\n\t" 
	"addi %[add_cnt],%[add_cnt],1\n\t"

	"fcvt.d.w f2,t4\n\t"
	"addi %[others_cnt],%[others_cnt],1\n\t"
	
	"fmul.d f1,f1,f2\n\t"
	"addi %[mul_cnt],%[mul_cnt],1\n\t"

	"addi t1,t1,1\n\t" 
	"addi %[add_cnt],%[add_cnt],1\n\t"

"addi %[others_cnt],%[others_cnt],1\n\t"
"bne t1,%[N],loop\n\t"

