#include <stdio.h>
#include <string.h>


void f(int n){
    int cont = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        j = i;
        while (j < n)
        {
            j++;
            cont++;
        }
        while (j > 0)
        {
            j--;
            cont++;
        }
        cont++;
        
    }
    printf("%d \n", cont);
    
}

void main(){
    char a[] = "ciao";  // ci\0 
    char *b = a + strlen(a)/2;
    *b = '\0';
    printf("%s, %d ", a, strlen(b) );  
}