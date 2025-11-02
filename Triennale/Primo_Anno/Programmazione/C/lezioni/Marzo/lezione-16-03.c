#include <stdio.h>
#include <math.h>

float radice_quadrata(float x, float eps)
{
    int c = 0, max_iter = 1000;
    float g = x / 2;
    while (fabs(g * g - x) > eps && c < max_iter)
    {
        g = 0.5 * (g + x / g);
        c++; // c += 1, c--
    }
    return g;
}

void test_char(){
    char min;
    char masc;
    char a = 'a', A = 'A';
    int diff = a - A;
    printf("Minuscolo | Maiuscolo\n");
    for(min = 'a'; min <= 'z'; min++){
        masc = min - diff;
        printf("%c, %d | %c, %d\n", min, min, masc, masc);
    }
}


void main()
{
    float g;
    float eps = 0.0001;
    for (int x = 2; x < 12; x++)
    {
        float radice = radice_quadrata(x, eps);

        printf("La radice quadrata di %d e': %.5f \n", x, radice); // %f stringhe float
        // if (c == max_iter)
        //      printf("eps troppo piccolo %d\n", c);
        // else
        //      printf("Ottenuto dopo %d iterazioni\n", c);
    }


    test_char();
}

/*
    Operatori logici:
    && and
    || or
    ! not
*/

/*
    Operatori relazionali
    ==, !=, >, <, <=, >=

*/

/*
    for e while
    for(istr0; cond; istr1){
        blocco
    }
        <==>
    istr0;
    while(cond){
        blocco;
        istr1;
    }
*/