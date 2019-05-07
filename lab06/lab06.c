#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
  int key;
  struct Node *next, *prev;
} node;

typedef struct List{
  struct Node *start;
  int size;
  int query_cost;
} list;

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

  new_list->size = size;
  new_list->query_cost = 0;

  if(size == 0)
    new_list->start = NULL;
  else{
    new_list->start = new_node(1);
    aux = new_list->start;
    for(i=2;i<=size;i++){
      aux->next = new_node(i);
      aux = aux->next;
    }
  }
  return new_list;
}

int *new_counter(int size){
  int i;
  int *counter = malloc(size*sizeof(int));

  for(i=0;i<size;i++)
    counter[i] = 0;
}

void print_list(list my_list){
  node *aux = my_list.start;
  while(aux){
    printf("%d,", aux->key);
    aux = aux->next;
  }
}

void process_mtf(list *my_list, int req){
  int c = 0;
  node *nav = my_list->start;
  node *aux;
  if(nav){
    c++;
    if(nav->key != req)
      while(nav->next){
        c++;
        if(nav->next->key == req)
          break;
        else
          nav = nav->next;
      }
  } else {
    printf("Lista vazia. Impossível processar requisição.\n");
    return;
  }
  my_list->query_cost += c;
  if(c>1){
    aux = nav->next;
    nav->next = nav->next->next;
    aux->next = my_list->start;
    my_list->start = aux;
  }
  printf("Req: %d. Custo: %d. Lista: (", req, c);
  print_list(*my_list);
  printf(")\n");
}

int main(){
  int i, n, r, req;
  int *counter;
  list *mtf, *transpose, *count;

  scanf("%d %d", &n, &r);

  mtf = new_list(n);
  transpose = new_list(n);
  count = new_list(n);
  counter = new_counter(n);

  for(i=0;i<r;i++){
    scanf("%d", &req);

    process_mtf(mtf, req);
  }

  printf("Custo MTF: %d\n", mtf->query_cost);

  return 0;
}
