#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int key;
  node *next;
} Node;

typedef struct list{
  node *start;
  int size;
  int query_cost;
} List;

node *new_node(int key){
  node *new_node = malloc(sizeof(node));
  new_node->key = key;
  new_node->next = NULL;
  return new_node;
}

list *new_list(int size){
  list *new_list = malloc(sizeof(list));
  node *aux;
  int i;

  if(size == 0) return;
  new_list->start = new_node(1);
  aux = new_list->start;
  for(i=2;i<=size;i++){
    aux->next = new_node(i);
    aux = aux->next;
  }

  return new_list;
}

int main(){
  int i, n, r;
  scanf("%d %d", &n, &r);
  list *my_list = new_list(n);
  for(i=0;i<r;i++){

  }
}
