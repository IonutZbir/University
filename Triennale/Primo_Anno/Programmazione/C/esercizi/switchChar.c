#include <stdio.h>

/*
    Lista Prototipi
*/
char switch_case(char c); // prototipo di una funzione, anche char switch_case(char);

void main()
{
    char c;
    printf("Inserisci un carattere alfabetico. [a-z] o [A-Z]\n");
    scanf("%c", &c);
    char charASCII = switch_case(c); // va bene anche se switch_case e' int
    if (charASCII == -1)
        printf("Carattere invalido!!");
    else
        printf("%c (%d) -> %c (%d)\n", c, c, charASCII, charASCII);
}

char switch_case(char c) // va bene anche int
{
    /**
     * @param c 
     * @return char
     * @brief se c è una lettera maiuscola ritorni il corrispondente minuscolo;
        se c è una lettera minuscola ritorni il corrispondente maiuscolo;
        nel caso c non sia una lettera, la funzione ritorni -1
     */
    
    
    int diff = 'a' - 'A';
    if (c >= 'A' && c <= 'Z'){
        c = c + diff;
        //printf("%c | %d", c, c);
        return c;
    }
    if (c >= 'a' && c <= 'z'){
        c = c - diff;
        //printf("%c | %d", c, c);
        return c;
    }
    else
        return -1;
}