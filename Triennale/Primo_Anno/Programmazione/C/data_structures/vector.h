typedef enum Types{
    INT = 'i',
    FLOAT = 'f',
    CHAR = 'c',
    STRING = 's',
    LONG = 'l',
    DOUBLE = 'd'
}Types;

typedef struct object{
    Types type; // type of the value
    void *val; // pointer to the value
}object;

typedef struct vector
{
  object *data; //puntatore dell array di object (data)
  int len; // len of vector
  int capacity; // max capacity of vector
}vector;
/*
Functions of struct object
*/
void set(object*, int, object);
object new_int(int);
object new_float(float);
object new_long(long);
object new_double(double);
object new_char(char);
object new_string(char *);
/*
Functions of struct vector
*/

vector vector_init(void);
vector vector_append_int(vector, int);
vector vector_append_float(vector, float);
vector vector_append_long(vector, long);
vector vector_append_double(vector, double);
vector vector_append_char(vector, char);
vector vector_append_string(vector, char*);

vector vector_insert_int(vector, int, int);
vector vector_insert_float(vector, int, float);
vector vector_insert_long(vector, int, long);
vector vector_insert_double(vector, int, double);
vector vector_insert_char(vector, int, char);
vector vector_insert_string(vector, int, char*);

vector vector_pop(vector);
vector vector_delete(vector, int);
void vector_print(vector);