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

typedef struct keys{
    char **array;
    int len;    
}keys;

typedef struct values{
    float *array;
    int len;    
}values;

typedef struct d_node{
    char *key;
    object data;
    struct d_node *next;
}d_node;

typedef struct dict{
    d_node **head;
    int len;
    int cap;
}dict;

dict dict_init(int);
dict dict_resize(dict, int);
dict dict_set_int(dict, char*, int);
dict dict_set_float(dict, char*, float);
dict dict_set_long(dict, char*, long);
dict dict_set_double(dict, char*, double);
dict dict_set_char(dict, char*, char);
dict dict_set_string(dict, char*, char*);
d_node* dict_search(dict, char*);
d_node* dict_in0(d_node*, d_node);
char** get_keys(dict);
float* get_values(dict);
int dict_del(dict, char*);
int hash(dict, char*);
void llist_print(d_node*);
void dict_print(dict);
void llist_print_debug(d_node*);
void dict_print_debug(dict);