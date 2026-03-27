#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LIB_PRON/tree.h"
#include "LIB_PRON/stack.h"



struct arr_node{
  int data;
  int parent;
};


void tree_to_array(struct arr_node arr[], int *i, struct node *root, int parent) {
  arr[*i].data = root->data;
  arr[*i].parent = parent;
  int cur_i = *i;
  if (root->l != NULL) { 
    (*i)++;
    tree_to_array(arr, i, root->l, cur_i);
  }
  if (root->r != NULL) {
    (*i)++;
    tree_to_array(arr, i, root->r, cur_i);
  }
}

struct node* array_to_tree(struct arr_node arr[], int len) {
  if (arr[0].parent != -1) {
    return NULL;
  }
  struct node *node_arr[len];
  node_arr[0] = malloc(sizeof(struct node));
  node_arr[0]->data = arr[0].data;
  node_arr[0]->l = NULL; node_arr[0]->r = NULL;
  for (int i = 1; i < len; i++) {
    node_arr[i] = malloc(sizeof(struct node));
    node_arr[i]->data = arr[i].data;
    node_arr[i]->l = NULL; node_arr[i]->r = NULL;
    int node_parent = arr[i].parent;
    if (node_arr[i]->data < node_arr[node_parent]->data) {
      node_arr[node_parent]->l = node_arr[i];
    }
    else if (node_arr[i]->data > node_arr[node_parent]->data) {
      node_arr[node_parent]->r = node_arr[i];
    }
    else return NULL;
  }

  return node_arr[0];
}

void create_and_save_tree() {
  char buf[STRING_SIZE];
  fgets(buf, STRING_SIZE, stdin);
  struct node *root = str_to_tree(buf);
  if (root == NULL) return;
  int tree_len = tree_count(root);
  struct arr_node arr[tree_len];
  int i = 0;
  tree_to_array(arr, &i, root, -1);
  FILE * fp = fopen("tree.dat", "wb");
  fwrite(&tree_len, sizeof(int), 1, fp);
  fwrite(arr, sizeof(struct arr_node), tree_len, fp);
  if (!ferror(fp)) {
    printf("Дерево записано в файл tree.dat\n");
  }
  fclose(fp);
}

void read_tree() {
  FILE * fp = fopen("tree.dat", "rb");
  int tree_len;
  fread(&tree_len, sizeof(int), 1, fp);
  struct arr_node arr[tree_len];
  fread(arr, sizeof(struct arr_node), tree_len, fp);
  fclose(fp);
  struct node *root = array_to_tree(arr, tree_len);
  printf("Из файла загружено дерево: ");
  symmetry_print(root); printf("\n");
  tree_print(root);
}

int main() {
	int t; 
	printf("Работа с деревьями поиска.\n");
	do {
		printf("1) Создать дерево и записать в файл\n2) Прочитать дерево из файла\n");
		scanf("%d", &t);
    getchar();
		if (t >= 1 && t <= 2) (t - 1) ? read_tree() : create_and_save_tree();
		else printf("Неверный ввод\n");
	} while ( !(t >= 1 && t <= 2) );
  return 0;
}
