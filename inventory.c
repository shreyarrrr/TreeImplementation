/* Shreya Roy, inventory.c
 * Last updated March 29, 2019
 */

#include "inventory.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

/*
 *  create_node
 *  This function creates a new tree node and sets its data equal to the
 *  parameters, which are the car's make, model, and year. It returns the new
 *  node.
 */

tree_node *create_node(char *make, char *model, unsigned int year) {
  assert(make != NULL);
  assert(model != NULL);
  car *chosen = malloc(sizeof(car));
  assert(chosen != NULL);
  chosen->make = malloc((strlen(make) + 1) * sizeof(char));
  assert(chosen->make != NULL);
  strcpy(chosen->make, make);
  chosen->model = malloc((strlen(model) + 1) * sizeof(char));
  assert(chosen->model);
  strcpy(chosen->model, model);
  chosen->year = year;
  tree_node *list = malloc(sizeof(tree_node));
  assert(list != NULL);
  list->info = chosen;
  list->left_ptr = NULL;
  list->right_ptr = NULL;
  return list;
} /* create_node() */

/*
 *  insert_node
 *  This function inserts a node, given by the second parameter, in the tree,
 *  whose address is pointed to by the first parameter.
 */

void insert_node(tree_node **elem_ptr, tree_node *elem) {
  assert(elem_ptr != NULL);
  assert(elem != NULL);
  assert(elem->left_ptr == NULL);
  assert(elem->right_ptr == NULL);
  char *elem_model = elem->info->model;
  if (*elem_ptr == NULL) {
    *elem_ptr = elem;
    return;
  }
  if (strncmp((*elem_ptr)->info->model, elem_model, strlen(elem_model)) < 0) {
    insert_node(&((*elem_ptr)->right_ptr), elem);
  }
  else {
    insert_node(&((*elem_ptr)->left_ptr), elem);
  }
} /* insert_node() */

/*
 *  search_tree
 *  This function searches a tree, pointed to by the first parameter, for an
 *  element whose model matches the string given by the second parameter. It
 *  returns the node it finds, and null if it doesn't find anything.
 */

tree_node *search_tree(tree_node *list, char *model) {
  assert(model != NULL);
  if (list == NULL) {
    return NULL;
  }
  char *elem_model = list->info->model;
  if (strcmp(elem_model, model) < 0) {
    return search_tree(list->right_ptr, model);
  }
  else if (strcmp(elem_model, model) > 0) {
    return search_tree(list->left_ptr, model);
  }
  return list;
} /* search_tree() */

/*
 *  tree_to_list
 *  This function makes four different lists by traversing through a tree,
 *  given by the first parameter, in four different ways: prefix, postfix,
 *  forward, and reverse. The way the tree is traversed is given by the second
 *  parameter. The function returns the new list that is created.
 */

list_node *tree_to_list(tree_node *root, enum traversal manner) {
  assert((manner == PREFIX) || (manner == POSTFIX) || (manner == FORWARD) ||
      (manner == REVERSE));
  if (root == NULL) {
    return NULL;
  }
  list_node *list = NULL;
  if (manner == PREFIX) {
    list = malloc(sizeof(list_node));
    assert(list != NULL);
    list->info = root->info;
    list->next_ptr = tree_to_list(root->left_ptr, PREFIX);
    if (list->next_ptr == NULL) {
      list->next_ptr = tree_to_list(root->right_ptr, PREFIX);
    }
    else {
      list_node *iterator = list;
      while (iterator->next_ptr != NULL) {
        iterator = iterator->next_ptr;
      }
      iterator->next_ptr = tree_to_list(root->right_ptr, PREFIX);
    }
    return list;
  }
  else if (manner == POSTFIX) {
    list = tree_to_list(root->left_ptr, POSTFIX);
      if (list == NULL) {
        list = tree_to_list(root->right_ptr, POSTFIX);
      }
      else {
        list_node *iterator = list;
        while (iterator->next_ptr != NULL) {
          iterator = iterator->next_ptr;
        }
        iterator->next_ptr = tree_to_list(root->right_ptr, POSTFIX);
      }

      list_node *last = malloc(sizeof(list_node));
      assert(last != NULL);
      last->info = root->info;
      last->next_ptr = NULL;
      if (list == NULL) {
        list = last;
      }
      else {
        list_node *iterator = list;
        while (iterator->next_ptr != NULL) {
          iterator = iterator->next_ptr;
        }
      iterator->next_ptr = last;
    }
    return list;
  }
  else if (manner == FORWARD) {
    list = tree_to_list(root->left_ptr, FORWARD);
    list_node *last = malloc(sizeof(list_node));
    assert(last != NULL);
    last->info = root->info;
    last->next_ptr = NULL;
    if (list == NULL) {
      list = last;
    }
    else {
      list_node *iterator = list;
      while (iterator->next_ptr != NULL) {
        iterator = iterator->next_ptr;
      }
      iterator->next_ptr = last;
    }

    if (list == NULL) {
      list = tree_to_list(root->right_ptr, FORWARD);
    }
    else {
      list_node *iterator = list;
      while (iterator->next_ptr != NULL) {
        iterator = iterator->next_ptr;
      }
      iterator->next_ptr = tree_to_list(root->right_ptr, FORWARD);
    }
    return list;
  }
  else {
    list = tree_to_list(root->right_ptr, REVERSE);
    list_node *last = malloc(sizeof(list_node));
    assert(last != NULL);
    last->info = root->info;
    last->next_ptr = NULL;
    if (list == NULL) {
      list = last;
    }
    else {
      list_node *iterator = list;
      while (iterator->next_ptr != NULL) {
        iterator = iterator->next_ptr;
      }
      iterator->next_ptr = last;
    }
    if (list == NULL) {
      list = tree_to_list(root->left_ptr, REVERSE);
    }      
    else {
      list_node *iterator = list;
      while (iterator->next_ptr != NULL) {
        iterator = iterator->next_ptr;
      }
      iterator->next_ptr = tree_to_list(root->left_ptr, REVERSE);
    }
    return list;
  }
  return list;
} /* tree_to_list() */

/*
 *  delete_tree
 *  This function deletes the tree, whose address is pointed to by the
 *  parameter, and all of its data recursively.
 */

void delete_tree(tree_node **list) {
  assert(list != NULL);
  if (*list != NULL) {
    if ((*list)->left_ptr != NULL) {
      delete_tree(&(*list)->left_ptr);
    }
    if ((*list)->right_ptr != NULL) {
      delete_tree(&(*list)->right_ptr);
    }
    free((*list)->info->make);
    (*list)->info->make = NULL;
    free((*list)->info->model);
    (*list)->info->make = NULL;
    free((*list)->info);
    (*list)->info = NULL;
    free(*list);
    (*list)->left_ptr = NULL;
    (*list)->right_ptr = NULL;
    *list = NULL;
  }
} /* delete_tree() */
