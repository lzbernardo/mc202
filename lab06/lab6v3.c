#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
  int key;
  struct Node *prev;
  struct Node *next;
} node;

typedef struct List{
  int size;
  int cost;
  struct Node *head;
} list;

node *new_node(int key, node *prev){
  node *n = malloc(sizeof(node));
  if(n == NULL){
    printf("Not able to allocate memory for a new node\n");
    exit(1);
  }
  n->key = key;
  n->prev = prev;
  n->next = NULL;
  return n;
}

void print_list(list l){
  node *nav = l.head->next;
  printf("(");
  while(nav){
    printf("%d,", nav->key);
    nav = nav->next;
  }
  printf(")\n");
}

void push(int key, list *l){
  node *n;
  node *nav = l->head;
  while(nav->next)
    nav = nav->next;
  n = new_node(key, nav);
  nav->next = n;
}

list *new_list(int size){
  int i;
  list *l = malloc(sizeof(list));

  if(l == NULL){
    printf("Not able to allocate memory for a new list\n");
    exit(1);
  }

  l->size = size;
  l->cost = 0;
  l->head = new_node(-1, NULL);

  for(i=1;i<=size;i++){
    push(i, l);
  }

  return l;
}

void proc_mtf(int keyReq, list *l){
  int cost = 1;
  node *temp;
  node *nav = l->head->next;

  while(nav && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  // printf("key %d found\n", nav->key);

  if(cost > 1){
    // REMOVING THE KEY FROM ITS PLACE
    temp = nav;
    nav = nav->prev;
    nav->next = temp->next;
    if(nav->next != NULL)
      nav->next->prev = nav;

    // PUTTING THE KEY AT THE BEGINNING
    temp->next = l->head->next;
    temp->prev = l->head;
    l->head->next = temp;
    if(temp->next)
      temp->next->prev = temp;
  }

  l->cost += cost;

  // printf("MTF // Key replaced. New list (c = %d): ", l->cost);
  // print_list(*l);
}

void proc_transpose(int keyReq, list *l){
  int cost = 0;
  node *temp;
  node *nav = l->head;

  while(nav->next && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  // printf("key %d found\n", nav->key);

  if(cost>1){
    // REMOVING THE KEY FROM ITS PLACE
    temp = nav;
    nav = nav->prev;
    nav->next = temp->next;
    if(nav->next != NULL)
      nav->next->prev = nav;

    // MOVING THE KEY 1 SPACE BEHIND
    temp->next = nav;
    temp->prev = nav->prev;
    nav->prev->next = temp;
    nav->prev = temp;
  }

  l->cost += cost;

  // printf("TRANSPOSE // Key replaced. New list (c = %d): ", l->cost);
  // print_list(*l);
}

void proc_count(int keyReq, list *l, int *counter){
  int i, j, counterTemp, cost = 0;
  node *temp;
  node *nav = l->head;

  while(nav->next && nav->key != keyReq){
    nav = nav->next;
    cost++;
  }

  for(i=0; i<l->size; i++)
    if(counter[i] <= counter[cost-1] + 1)
      break;

  // NESSE PONTO TENHO i = novo previous E nav = key

  if(cost > 1){
    // REMOVING THE KEY FROM ITS PLACE
    temp = nav;
    nav = nav->prev;
    nav->next = temp->next;
    if(nav->next != NULL)
      nav->next->prev = nav;

    // GETTING THE POS. FROM THE NEW INSERTION PLACE
    nav = l->head;
    for(j=0;j<i;j++)
      nav = nav->next;

    // INSERTING THE KEY IN THE NEW POSITION
    temp->next = nav->next;
    if(nav->next)
      nav->next->prev = temp;
    temp->prev = nav;
    nav->next = temp;


    // printf("COUNT // // // Counter B4 CHANGES: (");
    // for(k=0; k<l->size; k++)
    //   printf("%d,", counter[k]);
    // printf(")\n");
    counterTemp = counter[cost-1];
    for(j=cost - 1; j>i; j--)
      counter[j] = counter[j-1];
    counter[j] = counterTemp + 1;
  } else {
    counter[0]++;
  }


  l->cost += cost;

  // printf("COUNT // Key %d replaced. New list (c = %d): ", keyReq, l->cost);
  // print_list(*l);
  // printf("COUNT // // // Counter: (");
  // for(i=0; i<l->size; i++)
  //   printf("%d,", counter[i]);
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

  counter = malloc(n*sizeof(int));
  for(i=0; i<n; i++)
    counter[i] = 0;

  for(i=0; i<r; i++){
    scanf("%d", &req);

    proc_mtf(req, mtf);
    proc_transpose(req, transpose);
    proc_count(req, count, counter);
  }

  printf("%d %d %d\n", mtf->cost, transpose->cost, count->cost);
  return 0;
}
