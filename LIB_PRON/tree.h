#ifndef TREE_PRON
#define TREE_PRON

#define STRING_SIZE 100
#define MAX(a, b) (a > b) ? a : b

struct node {
  int data;
  struct node *l;
  struct node *r;
};

void postfix_print(struct node *p);
void prefix_print(struct node *p);
void symmetry_print(struct node *p);
int len(char *c);
int tree_depth(struct node *p, int len);
int tree_count(struct node *p);
int max_node(struct node *p);
void fill_grid(struct node *parent, int level, int shift, int start_pos, int ue, char **grid);
void tree_print(struct node *p);
struct node *str_to_tree(char *str);
#endif
