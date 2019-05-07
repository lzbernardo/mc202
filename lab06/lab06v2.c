#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
  int key;
  struct Node *prev, *next;
} node;

typedef struct List{
  int size;
  int cost;
  struct Node *head;
} list;

node *new_node(int key, node *prev){
  node *n = malloc(sizeof(node));
  n->key = key;
  n->prev = prev;
  n->next = NULL;
  return n;
}

list *new_list(int size){
  int i;
  node *aux;
  list *L = malloc(sizeof(list));

  L->size = size;
  L->cost = 0;
  L->head = new_node(-1,NULL);

  aux = L->head;
  for(i=1;i<=size;i++){
    aux->next = new_node(i,aux);
    aux = aux->next;
  }

  return L;
}

// node *new_node(int key, node *prev){
//   node *n = malloc(sizeof(node));
//   n->key = key;
//   n->prev = prev;
//   n->next = NULL;
//   return n;
// }
//
// list *new_list(int size){
//   int i;
//   node *aux;
//   list *l = malloc(sizeof(list));
//
//   l->size = size;
//   l->cost = 0;
//   l->head = new_node(-1, NULL);
//   aux = l->head;
//
//   for(i=1;i<=size;i++){
//     aux->next = new_node(i,aux);
//     if(aux->next == NULL)
//       printf("Memory not allocated\n");
//     else{
//       printf("Memory successfully allocated (%d)\n", aux->next->key);
//     }
//     aux = aux->next;
//   }
//
//   return l;
// }

int *new_counter(int size){
  int i;
  int *counter = malloc(size*sizeof(int));

  for(i=0;i<=size;i++)
    counter[i] = 0;

  return counter;
}

void print_list(list L){
  node *nav = L.head->next;

  printf("(");
  while(nav){
    printf("%d,", nav->key);
    nav = nav->next;
  }
  printf(")\n");
}

void proc_mtf(list *L, int keyReq){
  int cost = 0;
  node *aux;
  node *nav = L->head->next;

  cost++;
  while(nav && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  if(!nav){
    printf("Not found\n");
    return;
  }

  if(cost>1){
    aux = nav->prev;
    aux->next = nav->next;
    if(aux->next)
      aux->next->prev = aux;

    nav->next = L->head->next;
    nav->next->prev = nav;
    L->head->next = nav;
    nav->prev = L->head;
  }

  L->cost += cost;

  // printf("Req: %d. Cost: %d. List: ", keyReq, L->cost);
  // print_list(*L);
}

void proc_transpose(list *L, int keyReq){
  int cost = 0;
  node *aux;
  node *nav = L->head->next;

  cost++;
  while(nav && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  if(!nav){
    printf("Not found\n");
    return;
  }

  if(cost>1){
    aux = nav->prev;
    aux->next = nav->next;
    if(aux->next)
      aux->next->prev = aux;

    nav->next = aux;
    nav->prev = aux->prev;
    nav->prev->next = nav;
    aux->prev = nav;
  }

  L->cost += cost;
}

void proc_count(list *L, int keyReq, int *counter){
  int i, j, ab, cost = 0;
  node *aux;
  node *exg;
  node *nav = L->head->next;

  cost++;
  while(nav && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  if(!nav){
    printf("Not found\n");
    return;
  }

  if(cost>1){
    for(i=0; i<L->size; i++)
      if(counter[i] <= counter[cost-1] + 1)
        break;

    ab = counter[cost-1];
    for(j=cost-1; j>i; j--){
      counter[j] = counter[j-1];
    }
    counter[i] = ab+1;

    aux = nav->prev;
    aux->next = nav->next;
    if(aux->next)
      aux->next->prev = aux;

    exg = L->head->next;
    for(j=0; j<i; j++)
      exg = exg->next;

    aux = exg->prev;
    aux->next = nav;
    nav->next = exg;
    exg->prev = nav;
    nav->prev = aux;
  } else {
    counter[0]++;
  }

  L->cost += cost;

  // printf("Req: %d. Cost: %d. List: ", keyReq, L->cost);
  // print_list(*L);
  // printf("(");
  // for(i=0;i<L->size;i++){
  //   printf("%d, ", counter[i]);
  // }
  // printf(")\n");
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

  for(i=0; i<r; i++){
    scanf("%d", &req);

    proc_mtf(mtf, req);
    proc_transpose(transpose, req);
    proc_count(count, req, counter);
  }

  printf("%d %d %d\n", mtf->cost, transpose->cost, count->cost);

  return 0;
}
