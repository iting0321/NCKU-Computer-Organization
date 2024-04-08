#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    //y[2i+j]+= h[3i+f] * x[2f+j];

    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                asm volatile(
			//y[2i+j] + = h[3i+f] * x[2f+j];
			//"la t4,0(%[py])\n\t"
			//"la t6,0(%[px])\n\t"
			//"la t5,0(%[ph])\n\t"
			
		//	"lw t4,0(%[i])\n\t"
		//	"lw t5,0(%[j])\n\t"
			//"lw t6,0(%[f])\n\t"

			"add t0,%[i],%[i]\n\t"
			"add t0,t0,%[i]\n\t"    // t0 = 3i
			"add t0,t0,%[f]\n\t"    // t0 = 3i+f
			"slli t0,t0,2\n\t"
			"add t0,t0,%[ph]\n\t" // t1 = h[3i+f]
			"lw t1,0(t0)\n\t"

			"add t0,%[f],%[f]\n\t"
			"add t0,%[j],t0\n\t"	// 
			"slli t0,t0,2\n\t"
			"add t0,t0,%[px]\n\t" // t2 = x[2f+j]
			"lw t2,0(t0)\n\t"

			"lw t3,0(%[py])\n\t"   


			"mul t2,t2,t1\n\t"
			"add t2,t3,t2\n\t"
			"sw t2,0(%[py])\n\t"

			:
                        :[py] "r" (p_y+2*i+j) ,[ph] "r" (p_h),[px] "r" (p_x),[i] "r" (i),[j] "r" (j),[f] "r" (f)
		    	:"t0","t1","t2","t3","t4","t5","t6"  // clubber memory
		   
                               

				);
	}
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
