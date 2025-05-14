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


typedef struct node{
    object data; // the data stored in the node
    struct node *next; // pointer to the next node of the list
}node;

typedef struct linked_list{
    node *head; // pointer to the first node of the linked list
    node *tail;
    int len; // lenght of the linked list, (number of nodes)
}linked_list;

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
Functions of linked_list
*/

linked_list ll_init(void);
/*-----*/
linked_list ll_in0_int(linked_list, int);
linked_list ll_in0_float(linked_list, float);
linked_list ll_in0_long(linked_list, long);
linked_list ll_in0_double(linked_list, double);
linked_list ll_in0_char(linked_list, char);
linked_list ll_in0_string(linked_list, char*);
/*-----*/
linked_list ll_insert_int(linked_list, int, int);
linked_list ll_insert_float(linked_list, int, float);
linked_list ll_insert_long(linked_list, int, long);
linked_list ll_insert_double(linked_list, int, double);
linked_list ll_insert_char(linked_list, int, char);
linked_list ll_insert_string(linked_list, int, char*);
/*-----*/
linked_list ll_append_int(linked_list, int);
linked_list ll_append_float(linked_list, float);
linked_list ll_append_long(linked_list, long);
linked_list ll_append_double(linked_list, double);
linked_list ll_append_char(linked_list, char);
linked_list ll_append_string(linked_list, char*);
/*-----*/
linked_list ll_clear_all(linked_list);
linked_list ll_clear_int(linked_list, int);
linked_list ll_clear_float(linked_list, float);
linked_list ll_clear_long(linked_list, long);
linked_list ll_clear_double(linked_list, double);
linked_list ll_clear_char(linked_list, char);
linked_list ll_clear_string(linked_list, char*);
/*-----*/
linked_list ll_del0(linked_list);
linked_list ll_delete(linked_list, int);
linked_list slice(linked_list, int, int);
node *ll_search(linked_list, int);
void ll_print(linked_list);
