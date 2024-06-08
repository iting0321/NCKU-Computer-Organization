void matrix_multiplication(int *a, int *b, int *output, int i,                       int k, int j) {
    const int blocksize = 8;
    int sum=0;
    for(int x=0;x<i;x+=blocksize){
	    for(int y=0;y<j;y+=blocksize){
		    for(int z=0;z<k;z+=blocksize){
		            for(int Block_x=x;Block_x<x+blocksize&&Block_x<i;++Block_x){
			    		for(int Block_y=y;Block_y<y+blocksize&&Block_y<j;++Block_y){
						sum=0;
						for(int Block_z=z;Block_z<z+blocksize&&Block_z<k;++Block_z){
							sum += a[Block_x * k + Block_z] * b[Block_z * j + Block_y];	
						}
						 output[Block_x * j + Block_y] += sum;
					}
			    }
				    }
	    } 
    }
	return;
}
