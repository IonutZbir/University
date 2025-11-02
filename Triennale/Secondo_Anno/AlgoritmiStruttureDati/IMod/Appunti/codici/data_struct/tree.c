#include <stdio.h>
#include <stdlib.h>

node *node_init(int e){
    node *nd = malloc(sizeof(node));
    if (nd != NULL) {
        nd->data = e;
        nd->father = NULL;
        nd->right = NULL;
        nd->left = NULL;
    }
    return nd;
}

binary_tree *binary_tree_init(){
    binary_tree *bt = malloc(sizeof(binary_tree));
    bt->root = NULL;
    bt->len = 0;
}

void binary_tree_create(binary_tree *bt, array *arr_data, node *father){
    if(arr_data->len == 0) return;
    node *nd = node_init(arr_data->data[arr_data->len - 1]);
    if(bt->len == 0){
        bt->root = nd;
        bt->len++;
    }else{
        
    }
}
