#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    Lista Prototipi
---------------------------------------
*/

bool isAlpha(char *, int);
bool isAlNum(char *, int);
bool isDigit(char *, int);
bool endsWith(char *, int, char *, int);
char *capitalize(char *, int);
char *lower_case(char *, int);
char *upper_case(char *, int);
char *slice(char *, int, int, int, int);
int get_index(char *, int, char);
int find(char *, int, char *, int);
int str_len(char *);
int str_cmp(char *, char *);

/*
    Lista Prototipi
---------------------------------------
*/

int main()
{
    char a[] = "  ";
    char b[] = "  ";
    int rC = strcmp(a, b);
    int rM = str_cmp(a, b);
    if (rC > 0)
        rC = 1;
    if (rC < 0)
        rC = -1;
    printf("C: %d\n", rC);
    printf("M: %d\n", rM);
}

int str_len(char *str)
{
    int c = 0;
    while (str[c] != '\0')
    {
        c++;
    }
    return c;
}

char *capitalize(char *str, int len)
{
    char *upper_str = malloc(len * sizeof(char));
    // int diff = 'a' - 'A';
    if (str[0] >= 'a' && str[0] <= 'z')
    {
        upper_str[0] = 'A' + str[0] - 'a';
        if (upper_str != NULL)
        {
            for (int i = 1; i < len - 1; i++)
            {
                upper_str[i] = str[i];
            }
        }
        return upper_str;
    }
    else
    {
        return str;
    }
}

char *lower_case(char *str, int len)
{
    char *lower_str = malloc(len * sizeof(char));
    // int diff = 'a' - 'A';
    if (lower_str != NULL)
    {
        for (int i = 0; i < len - 1; i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                lower_str[i] = 'a' + str[i] - 'A';
            else
                lower_str[i] = str[i];
        }
    }
    return lower_str;
}

char *upper_case(char *str, int len)
{
    char *upper_str = malloc(len * sizeof(char));
    // int diff = 'a' - 'A';
    if (upper_str != NULL)
    {
        for (int i = 0; i < len - 1; i++)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
                upper_str[i] = 'A' + str[i] - 'a';
            else
                upper_str[i] = str[i];
        }
    }
    return upper_str;
}

char *slice(char *str, int len, int start, int stop, int step)
{
    if (stop <= start)
        return '\0';
    int len_s = stop - start;
    char *slice_str = malloc((len_s + 1) * sizeof(char));
    if (slice_str != NULL && (step <= len - step))
    {
        for (int i = 0; i < len_s; i++)
        {
            slice_str[i] = str[(i + start) * step];
        }
        slice_str[len_s + 1] = '\0';
    }
    return slice_str;
}

int get_index(char *str, int len, char elem)
{
    for (int i = 0; i < len; i++)
    {
        if (elem == str[i])
            return i;
        return -1;
    }
}

bool isAlpha(char *str, int len)
{
    bool b = true;
    int i = 0;
    while (b == true && i < len - 1)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            b = true;
        else
            b = false;
        i++;
    }
    return b;
}

bool isDigit(char *str, int len)
{
    bool b = true;
    int i = 0;
    while (b == true && i < len - 1)
    {
        if ((str[i] >= '0' && str[i] <= '9'))
            b = true;
        else
            b = false;
        i++;
    }
    return b;
}

bool isAlNum(char *str, int len)
{
    bool b = true;
    int i = 0;
    while (b == true && i < len - 1)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
            b = true;
        else
            b = false;
        i++;
    }
    return b;
}

int str_cmp(char *str_a, char *str_b)
{
    // returns -1 if str_a > str_b
    // returns 1 if str_b > str_a
    // returns 0 if str_a == str_b 

    int len_a = str_len(str_a), len_b = str_len(str_b), i = 0, min;
    if (len_a > len_b)
        min = len_b;
    else
        min = len_a;

    while (i < min)
    {
        if (str_a[i] != str_b[i])
        {
            if (str_a[i] < str_b[i])
                return -1;
            else
                return 1;
        }
        i++;
    }
    if (min == len_a && len_a != len_b)
    {
        return -1;
    }
    if (min == len_b && len_a != len_b)
    {
        return 1;
    }

    return 0;
}
