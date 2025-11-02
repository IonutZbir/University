#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct array_int
{
  int *array;
  int len;
};
typedef struct array_int array_int;
char *concatena(char *str1, char *str2);
int len_str(char *str);
array_int append(array_int arr, int elem);
array_int array_int_init(void);

void main(){
  // char a[] = "ciao"; // 14 + 1 (\0)
  // char b[] = " mondo";
  // char *c;
  // c = concatena(a, b);
  // printf("%s, %d\n", c, len_str(c));
  array_int arr = array_int_init();
  arr = append(arr, 100);
  arr = append(arr, 200);
  arr = append(arr, 300);
  for(int i = 0; i<arr.len; i++){
    printf("%d\n", arr.array[i]);
  }
}

array_int array_int_init(void){
  array_int v = {NULL, 0};
  return v;
}

array_int append(array_int old_arr, int elem){
    int *new_arr = malloc((old_arr.len + 1) * sizeof(int));
    if (new_arr != NULL)
    {
        for (int i = 0; i < old_arr.len; i++)
        {
            new_arr[i] = old_arr.array[i];
        }
        new_arr[old_arr.len] = elem;
        free(old_arr.array); // libero lo spazio di memoria in cui era allocato il vecchio array
        old_arr.array = new_arr; // assegno al puntatore il nuovo array
        old_arr.len++; // aumento di la lunghezza dell array
    }
    return old_arr;
}



int len_str(char *str){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return i;
}

char *concatena(char *str1, char *str2){    // costo lineare
  int len1 = len_str(str1), len2 = len_str(str2);
  char *new_str = malloc((len1 + len2 + 1) * sizeof(char));
  if(new_str != NULL){
    for(int i = 0; i < len1; i++){  // costo O(len_a)
      new_str[i] = str1[i];
    }
    for(int i = 0; i < len2; i++){  // costo O(len_b)
      new_str[i + len1] = str2[i];
    }
    new_str[len1 + len2 + 1] = '\0';
  }
  return new_str;
}

