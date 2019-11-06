#ifndef INVENTORY_H
#define INVENTORY_H

enum traversal {
  PREFIX,
  POSTFIX,
  FORWARD,
  REVERSE,
};
 
typedef struct car {
  char *make;
  char *model;
  unsigned int year;
} car;

typedef struct tree_node {
  struct tree_node *left_ptr;
  struct tree_node *right_ptr;
  car * info;
} tree_node;
 
typedef struct list_node {
  struct list_node *next_ptr;
  car * info;
} list_node;
 
tree_node * create_node(char * make, char * model, unsigned int year);
void insert_node(tree_node ** tree, tree_node * node);
tree_node * search_tree(tree_node * root, char * model);
list_node * tree_to_list(tree_node * root, enum traversal type);
void delete_tree(tree_node ** root);

#endif
