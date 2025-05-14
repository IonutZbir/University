#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// create a new object that contains an integer
object new_int(int val){
    object obj = {'u', NULL};
    obj.type = INT;
    obj.val = malloc(sizeof(int));
    *(int *)obj.val = val;
    return obj;
}

// create a new object that contains a float
object new_float(float val){
    object obj;
    obj.type = FLOAT;
    obj.val = malloc(sizeof(float));
    *(float *)obj.val = val;
    return obj;
}

// create a new object that contains a long
object new_long(long val){
    object obj;
    obj.type = LONG;
    obj.val = malloc(sizeof(long));
    *(long *)obj.val = val;
    return obj;
}

// create a new object that contains a double
object new_double(double val){
    object obj;
    obj.type = DOUBLE;
    obj.val = malloc(sizeof(double));
    *(double *)obj.val = val;
    return obj;
}

// create a new object that contains a char
object new_char(char val){
    object obj;
    obj.type = CHAR;
    obj.val = malloc(sizeof(char));
    *((char *)obj.val) = val;
    return obj;
}

// create a new object that contains a string
object new_string(char *val){
    object obj;
    obj.type = STRING;
    obj.val = malloc(sizeof(char) * (strlen(val) + 1));
    obj.val = strcpy(obj.val, val);
    return obj;
}

// initialize a NULL vector
vector vector_init(void)
{
    vector v = {NULL, 0, 0};
    return v;
}

vector vector_append_int(vector v, int value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_int(value);
    v.data[v.len] = obj;
    v.len++;
    return v;
}

vector vector_append_float(vector v, float value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_float(value);
    v.data[v.len] = obj;
    v.len++;

    return v;
}

vector vector_append_long(vector v, long value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_long(value);
    v.data[v.len] = obj;
    v.len++;

    return v;
}

vector vector_append_double(vector v, double value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_double(value);
    v.data[v.len] = obj;
    v.len++;

    return v;
}

vector vector_append_char(vector v, char value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_char(value);
    v.data[v.len] = obj;
    v.len++;

    return v;
}

vector vector_append_string(vector v, char* value){
    vector old_v = {v.data, v.len, v.capacity};
    if(v.len == v.capacity){
        v.data = realloc(v.data, (2 * (v.capacity + 1)) * sizeof(object));
        if(v.data == NULL)
            return old_v;
            
        v.capacity = 2*(v.capacity + 1);
    }
    object obj = new_string(value);
    v.data[v.len] = obj;
    v.len++;

    return v;
}

vector vector_insert_int(vector v, int pos, int value){
    int old_cap = v.capacity, old_len = v.len;

    if(pos > v.len){
        return v;
    }

    v = vector_append_int(v, 0);
    if (old_cap == old_len && old_cap == v.capacity){ // realloc dentro append ritorna NULL
        return v;
    }

    for(int i = v.len - 1; i >= pos; i--){
        *(int*)v.data[i + 1].val = *(int*)v.data[i].val;
    }
    *(int *)v.data[pos].val = value;
    v.data[pos].type = INT;
    return v;
}

vector vector_insert_float(vector v, int pos, float value){
    int old_cap = v.capacity, old_len = v.len;

    if(pos > v.len){
        return v;
    }

    v = vector_append_float(v, 0);
    if (old_cap == old_len && old_cap == v.capacity){ // realloc dentro append ritorna NULL
        return v;
    }

    for(int i = v.len - 1; i >= pos; i--){
        *(float*)v.data[i + 1].val = *(float*)v.data[i].val;
    }
    *(float *)v.data[pos].val = value;
    v.data[pos].type = FLOAT;
    return v;
}

void vector_print(vector v){
    printf("["); 
    int i;
    char type;
    for(i = 0; i < v.len; i++){
        type = v.data[i].type;
        switch (type)
        {
        case INT:
            printf("%d", (*(int *)v.data[i].val));
            break;
        case FLOAT:
            printf("%f", (*(float *)v.data[i].val));
            break;
        case LONG:
            printf("%ld", (*(long *)v.data[i].val));
            break;
        case DOUBLE:
            printf("%lf", (*(double *)v.data[i].val));
            break;
        case CHAR:
            printf("%c", (*(char *)v.data[i].val));
            break;
        case STRING:
            printf("%s", v.data[i].val);
            break;
        default:
            break;
        }
        if (i < v.len - 1) {
             printf(", ");
        }
    }
    printf("]\n");
}