"improved_loop:\n\t"
    "vsetvli t0, %[arr_size], e16\n\t"
    "addi %[others_cnt], %[others_cnt], 1\n\t"

    "vle16.v v0, (%[h])\n\t"
    "addi %[lw_cnt], %[lw_cnt], 1\n\t"

    
    "vle16.v v1, (%[x])\n\t"
    "addi %[lw_cnt], %[lw_cnt], 1\n\t"

    "vmul.vv v2, v1, v0\n\t"
    "addi %[mul_cnt], %[mul_cnt], 1\n\t"

    "vadd.vx v2, v2, %[id]\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"

    "vse16.v v2, (%[y])\n\t"
    "addi %[sw_cnt], %[sw_cnt], 1\n\t"


    "addi %[y], %[y], 16\n\t"
    "addi %[h], %[h], 16\n\t"
    "addi %[x], %[x], 16\n\t"
    "addi %[add_cnt], %[add_cnt], 3\n\t"

    "sub %[arr_size], %[arr_size], t0\n\t"
    "addi %[sub_cnt], %[sub_cnt], 1\n\t"

"addi %[others_cnt], %[others_cnt], 1\n\t"
"bnez %[arr_size], improved_loop\n\t"
