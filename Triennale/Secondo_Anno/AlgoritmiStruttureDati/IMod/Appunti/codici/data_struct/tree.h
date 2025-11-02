typedef struct node {
    int data;
    struct node *father;
    struct node *right;
    struct node *left;
} node;

typedef struct binary_tree {
    node *root;
    int len;
} binary_tree;

typedef struct array {
    int *data;
    int len;
} array;

array *array_init();
void print_array(array *);
node *node_init(int);
binary_tree *binary_tree_init();
void binary_tree_create(binary_tree *, int *);
