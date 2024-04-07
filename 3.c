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
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                asm volatile(
			 
                        //y[2i+j]+= h[3i+f] * x[2f+j];
                        "lw t0,0(%[py])\n\t"
                        "lw t1 ,0(%[ph])\n\t"
                        "lw t2 ,0(%[px])\n\t"

                        "mul t1 ,t1,t2\n\t"
                        "add t0 ,t0 ,t1\n\t"
                        "sw t0 ,0(%[py])\n\t"
			:
                        :[py] "r" (p_y+2*i+j) ,[ph] "r" (p_h+3*i+f),[px] "r" (p_x+2*f+j)
		    	:"t0","t1","t2"
		   
                               

				);
	}
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
