#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/vector.h"

typedef struct Polynomial
{
    vector pol;
    int degree;
}Polynomial;

typedef struct Pol_term
{
    Types type;
    void *val; // int, float
    int deg;
}Pol_term;

vector vector_append_pol_term(vector v, Pol_term term);

Pol_term pol_term_int(int val, int deg);
Pol_term pol_term_float(float val, int deg);

Polynomial polynomial_empty_init(int degree);
Polynomial polynomial_values_init(int degree, vector values);
Polynomial polynomial_sum(Polynomial pol1, Polynomial pol2);

void polynomial_print(Polynomial pol, char f, char var);