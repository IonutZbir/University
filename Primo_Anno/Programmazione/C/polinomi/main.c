#include "polinomi.h"

void main(){
    int i_data[] = {-3, 4, 6}; 
    float f_data[] = {7.5, -9.75, 1.23};
    vector val = vector_init();
    for (int i = 0; i < 3; i++)
    {
        val = vector_append_int(val, i_data[i]);
        val = vector_append_float(val, f_data[i]);
    }
    
    Polynomial p = polynomial_values_init(6, val);
    //vector_print(val);
    polynomial_print(p, 'P', 'x');

    val = vector_append_int(val, 4);
    val = vector_append_float(val, 676.2);

    Polynomial g = polynomial_values_init(8, val);

    polynomial_print(g, 'G', 'y');

    Polynomial sum;
    sum = polynomial_sum(p, g);

    polynomial_print(sum, 'S', 's');

}