#include <stdio.h>

float add(float a, float b)
{
    return a + b;
}

float sub(float a, float b)
{
    // return  (a >= b) ? a - b : -1 * (b - a);
    return a - b;
}

float mult(float a, float b)
{
    return a * b;
}

float div(float a, float b)
{
    return a / b;
}

int main()
{
    int op;
    float a, b, result;
    printf("Seleziona l\'operazione: \n1. Addizione\n2. Sottrazione \n3. Moltiplicazione \n4. Divisione \n");
    scanf("%d", &op);
    printf("Digita due numeri: \n");
    scanf("%f", &a);
    scanf("%f", &b);
    
    if(op == 1){
        result = add(a, b);
    }
    if(op == 2){
        result = sub(a, b);
    }
    if(op == 3){
        result = mult(a, b);
    }   
    if(op == 4){
        result = div(a, b);
    }


    printf("%0.1f", result);        
}
