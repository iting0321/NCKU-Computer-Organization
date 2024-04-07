#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    asm volatile(
	//y[2i+j]+= h[3i+f] * x[2f+j];
	
	"li t3,3\n\t"
	"li t4,0\n\t"//t4 = i 
	"loop1:\n\t"

		"li t5,0\n\t"//t5 = j
		"loop2:\n\t"
	
			"li t6,0\n\t" // t6 = f
			"loop3:\n\t"

			"add t0,t4,t4\n\t"
			"add t0,t0,t4\n\t"    // t0 = 3i
			"add t0,t0,t6\n\t"    // t0 = 3i+f
			"slli t0,t0,2\n\t"
			"add t0,t0,%[ph]\n\t" // t0 = h[3i+f]
			"lw t1,0(t0)\n\t"

			"add t0,t6,t6\n\t"
			"add t0,t5,t0\n\t"	// t2 = 2f+j
			"slli t0,t0,2\n\t"
			"add t0,t0,%[px]\n\t" // t2 = x[2f+i]
			"lw t2,0(t0)\n\t"

			"add t0,t4,t4\n\t"      // t0 = 2i
                        "add t0,t0,t5\n\t"      // t0 = 2i +j
                        "slli t0,t0,2\n\t"
                        "add t0,t0,%[py]\n\t" // t0 = y[2i+j]
                        "lw t3,0(t0)\n\t"


			"mul t2,t2,t1\n\t"
			"add t2,t3,t2\n\t"
			"sw t2,0(t0)\n\t"

			"addi t6,t6,1\n\t"
			"li t3,3\n\t"
			"blt t6,t3,loop3\n\t"

		"addi t5,t5,1\n\t"
		"li t3,2\n\t"
		"blt t5,t3,loop2\n\t"

	"addi t4,t4,1\n\t"
	"li t3,3\n\t"
	"blt t4,t3,loop1\n\t"


	:
	:[py] "r" (p_y),[ph] "r" (p_h),[px] "r" (p_x)
	:"t0","t1","t2","t3","t4","t5","t6"	    
		    
		    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
