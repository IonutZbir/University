#include "polinomi.h"

vector vector_append_pol_term(vector v, Pol_term term){
    vector old_v = {v.data, v.len, v.capacity};
    object obj;
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    obj.type = term.type;
    obj.val = malloc(sizeof(Pol_term));
    *(Pol_term*)obj.val = term; // da migliorare
    v.data[v.len] = obj;
    v.len++;
    return v;
}

Pol_term pol_term_int(int val, int deg){
    Pol_term term;
    term.val = malloc(sizeof(int));
    if (term.val != NULL)
    {
        *(int *)term.val = val;
        term.deg = deg;
        term.type = INT;
    }
    return term;
}

Pol_term pol_term_float(float val, int deg){
    Pol_term term;
    term.val = malloc(sizeof(float));
    if (term.val != NULL)
    {
        *(float *)term.val = val;
        term.deg = deg;
        term.type = FLOAT;
    }
    return term;
}

Polynomial polynomial_empty_init(int degree){
    Polynomial p;
    p.pol = vector_init();
    p.degree = degree;
    return p;
}

Polynomial polynomial_values_init(int degree, vector values){
    Polynomial p;
    p.pol = vector_init();
    p.degree = degree;
    for (int i = 0; i < values.len; i++)
    {
        Pol_term term;
        if (values.data[i].type == INT)
        {
            term = pol_term_int(*(int*)values.data[i].val, i);
        }else{
            term = pol_term_float(*(float*)values.data[i].val, i);
        }
        p.pol = vector_append_pol_term(p.pol, term);
    }
    return p;
}

Polynomial polynomial_sum(Polynomial p1, Polynomial p2) {
    int max_degree = p1.degree > p2.degree ? p1.degree : p2.degree;
    Polynomial result = polynomial_empty_init(max_degree);
    Pol_term term;

    // Traverse through the terms of both polynomials and add their coefficients for each degree
    for (int i = 0; i <= max_degree; i++) {
        int coeff_sum = 0;
        Pol_term sum_term;

        // Add the coefficient of term with degree i from the first polynomial
        if (i <= p1.degree) {
            term = *(Pol_term*)p1.pol.data[i].val;
            coeff_sum += p1.pol.data[i].type == INT ? *(int *)term.val : *(float *)term.val;
        }

        // Add the coefficient of term with degree i from the second polynomial
        if (i <= p2.degree) {
            term = *(Pol_term*)p2.pol.data[i].val;
            coeff_sum += p2.pol.data[i].type == INT ? *(int *)term.val : *(float *)term.val;
        }
        sum_term = pol_term_int(coeff_sum, i);

        printf("%d\n", coeff_sum);

        // Append the new term to the result polynomial
        result.pol = vector_append_pol_term(result.pol, sum_term);
    }

    return result;
}

void polynomial_print(Polynomial p, char f, char var){
    printf("%c[%c] = ", f, var);
    Pol_term term;
    int i;
    for (i = 0; i < p.degree - 1; i++)
    {
        term = *(Pol_term*)p.pol.data[i].val;
        if (p.pol.data[i].type == INT)
        {
            printf("(%d*x^%d) + ", *(int *)term.val, term.deg);
        }
        if (p.pol.data[i].type == FLOAT)
        {
            printf("(%f*x^%d) + ", *(float *)term.val, term.deg);
        }
    }
    term = *(Pol_term*)p.pol.data[i].val;
    if (p.pol.data[i].type == INT)
    {
        printf("(%d*x^%d)", *(int *)term.val, term.deg);
    }
    if (p.pol.data[i].type == FLOAT)
    {
        printf("(%f*x^%d)", *(float *)term.val, term.deg);
    }
    printf("\n");
}

