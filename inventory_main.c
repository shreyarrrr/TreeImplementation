#include <stdio.h>
#include <unistd.h>

#include "inventory.h"

/*
 *  In case you're curious, we need to include unistd.h to declare
 *  the sleep() function.
 */

#define QUIT (0)
#define INSERT (1)
#define FIND (2)
#define DELETE (3)
#define TO_LIST (4)
#define PRINT (5)
#define PREFIX_TRAVERSAL (0)
#define POSTFIX_TRAVERSAL (1)
#define FORWARD_TRAVERSAL (2)
#define REVERSE_TRAVERSAL (3)

/*
 *  The function prints the name, title, and id_number of the tree passed
 *  into it.
 */

void print_node(car *car_ptr) {
  printf("make: %s;\tmodel: %s;\tyear: %d\n",
      car_ptr->make, car_ptr->model, car_ptr->year);
} /* tree_print_node() */

/*
 *  This function prints the name, title, and id_number of each node
 *  in the binary tree passed to it.
 */

void print_tree(tree_node *tree_ptr) {
  if (tree_ptr == NULL) {
    return;
  }

  print_tree(tree_ptr->left_ptr);
  print_node(tree_ptr->info);
  print_tree(tree_ptr->right_ptr);
} /* tree_print() */

void print_list(list_node *list_ptr) {
  if (list_ptr == NULL) {
    return;
  }

  print_node(list_ptr->info);
  print_list(list_ptr->next_ptr);
}

/*
 *  This function is used to run the functions in hw11.c. User input is used
 *  to determine which function to run an what is passed to it. main()
 *  prints information related to running the chosen function.
 */

int main() {
  tree_node *root = NULL;
  // Disable stdlib I/O buffering

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  while (1) {
    printf("\n\n");
    printf("0) Quit\n"
          "1) Insert\n"
          "2) Find\n"
          "3) Delete\n"
          "4) To List\n"
          "5) Print\n"
        "\nSelect a function: ");

    int selected_option = 333333;
    scanf("%d", &selected_option);

    tree_node * node = NULL;
    char model[100] = "\0";

    if ((selected_option > PRINT) || (selected_option < QUIT)) {
      printf("Invalid selection.\n");
      continue;
    }

    if (selected_option == QUIT) {
      printf("\n\n\n\n\n\nHave a nice day.\n");
      return 0;
    }
    else if (selected_option == INSERT) {
      char make[100] = "\0";
      unsigned int year = 0;
      printf ("Enter the make:  ");
      scanf("%s", make);
      printf ("Enter the model: ");
      scanf("%s", model);
      printf ("Enter the yaer:    ");
      scanf("%d", &year);
      node = create_node(make, model, year);
      insert_node(&root, node);
    }
    else if (selected_option == FIND) {
      printf ("Enter a name to search for: ");
      scanf("%s", model);
      node = search_tree(root, model);
      if (node == NULL) {
        printf("Not found.\n");
      }
      else {
        printf("The matching tree element looks like: \n");
        print_node(node->info);
      }
    }
    else if (selected_option == DELETE) {
      delete_tree(&root);
    }
    else if (selected_option == TO_LIST) {
      list_node * list = NULL;
      int traversal_type = 0;
      printf("0) Prefix\n"
            "1) Postfix\n"
            "2) Forward\n"
            "3) Reverse\n"
            "\nSelect a traversal order: ");
      scanf("%d", &traversal_type);
      switch(traversal_type) {
        case PREFIX_TRAVERSAL:
          list = tree_to_list(root, PREFIX);
          print_list(list);
          break;
        case POSTFIX_TRAVERSAL:
          list = tree_to_list(root, POSTFIX);
          print_list(list);
          break;
        case FORWARD_TRAVERSAL:
          list = tree_to_list(root, FORWARD);
          print_list(list);
          break;
        case REVERSE_TRAVERSAL:
          list = tree_to_list(root, REVERSE);
          print_list(list);
          break;
        default:
          printf("Invalid traveral type selected.\n");
      }
    }
    else {
      print_tree(root);
    }
  }

    /* not reached. */

  return 0;
} /* main() */
                                                                                                      55,0-1        41%
                                                                                                   18,29         Top
