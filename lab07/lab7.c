// Bernardo Lanza de Assunção
// Lab 7 - RevTransp
// 164836
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define stringMAX 128


typedef struct Node{
  char spec;
  char *s;
  int *d;
  float *f;
  char *c;

  struct Node *next;
} node;

typedef struct List{
  int size;
  node *head;
} list;

// cria um novo nó de type = spec;
node *new_node(char spec){
  node *n = malloc(sizeof(node));

  n->spec = spec;
  n->next = NULL;

  switch(spec){
    case 's':
      n->s = malloc(sizeof(char) * stringMAX);
      scanf(" %[^\n]", n->s);
      break;
    case 'd':
      n->d = malloc(sizeof(int));
      scanf(" %d", n->d);
      break;
    case 'f':
      n->f = malloc(sizeof(float));
      scanf(" %f", n->f);
      break;
    case 'c':
      n->c = malloc(sizeof(char));
      scanf(" %c", n->c);
      break;
  }

  return n;
}

// cria uma nova lista (vazia) de tamanho n
list *new_list(int n){
  list *l = malloc(sizeof(list));
  l->size = n;
  l->head = malloc(sizeof(node));
  l->head->spec = 'h';
  l->head->next = NULL;
  return l;
}

// imprime um único nó
void print_item(node *n){
  switch(n->spec){
    case 's':
      printf("%s ", n->s);
      break;
    case 'd':
      printf("%d ", *(n->d));
      break;
    case 'f':
      printf("%.4f ", *(n->f));
      break;
    case 'c':
      printf("%c ", *(n->c));
      break;
  }
}

// imprime uma lista completa
void print_list(list *l){
  node *nav = l->head;
  while(nav){
    print_item(nav);
    nav = nav->next;
  }
  printf("\n");
}

// reverte uma subsecção de uma lista, definida entre *pre->next e *after
void reverse_within_range(node *pre, node *after){
  node *nav = pre->next;
  node *prev = after;
  node *next = NULL;

  // redireciona os nós até encontrar o último nó da lista (que não precisa ser redirecionado)
  while (nav != after){
      // realoca os ponteiros de um nó para que ele aponte para o outro lado
      next = nav->next;

      nav->next = prev;

      prev = nav;
      nav = next;
  }
  pre->next = prev;
}

// pede os parâmetros de reversão como input do usuário e faz a operação dentro da lista l
void reverse(list *l){
  int i, st, end;
  node *nav, *pre;

  scanf("%d %d", &st, &end);

  // ESSE for DEIXA nav NO node ANTERIOR AO CONJUNTO DE REVERSÃO
  nav = l->head;
  for(i=0; nav->next && i<st; i++)
    nav = nav->next;
  pre = nav;

  // ESSE for DEIXA nav NO ÚLTIMO node DO CONJUNTO A SER REVERTIDO
  for(; nav->next && i<end+1; i++)
    nav = nav->next;

  // DEBUGGING ONLY
  // printf("reversing from ");
  // print_item(pre->next);
  // printf("to ");
  // print_item(nav);

  reverse_within_range(pre, nav->next);
}

// pede os parâmetros de transposição como input do usuário e já realiza a operação sobre a lista l
void transpose(list *l){
  int i, st, end, transp;
  node *nav, *pos, *pre, *temp;

  scanf("%d %d %d", &st, &end, &transp);

  // ESSE for DEIXA pos NO node ANTERIOR AO NOVO POSICIONAMENTO DO CONJUNTO TRANSPOSTO
  if(transp == -1)
    pos = l->head;
  else{
    nav = l->head;
    for(i=0; nav->next && i<transp; i++)
      nav = nav->next;
    pos = nav->next;
  }
  // ESSE for DEIXA pre NO node ANTERIOR AO CONJUNTO A SER TRANSPOSTO
  nav = l->head;
  for(i=0; nav->next && i<st; i++)
    nav = nav->next;
  pre = nav;

  // ESSE for DEIXA nav NO ÚLTIMO node DO CONJUNTO A SER TRANSPOSTO
  for(; nav->next && i<end+1; i++)
    nav = nav->next;


  // DEBUGGING ONLY
  // printf("transposing between ");
  // print_item(pre->next);
  // printf("and ");
  // print_item(nav);
  // printf("to after ");
  // print_item(pos);

  temp = pre->next;
  pre->next = nav->next;
  nav->next = pos->next;
  pos->next = temp;

}

void free_list_nodes(node *n){
  if(n){
    free_list_nodes(n->next);
    free(n);
  }
}

void free_list(list *l){
  free_list_nodes(l->head);
  free(l);
}

int main(){
  int i, n;
  char c;
  list *l;
  node *nav;

  scanf("%d", &n);
  l = new_list(n);
  nav = l->head;

  // recebe os tipos de cada elemento e vai adicionando-os à lista
  for(i=0; i<n; i++){
    scanf(" %c", &c);
    nav->next = new_node(c);
    nav = nav->next;
  }
  print_list(l);

  // recebe as operações de reversão e transposição
  scanf("%d", &n);
  for(i=0; i<n; i++){
    scanf(" %c", &c);
    switch(c){
      case 'r':
        reverse(l);
        break;
      case 't':
        transpose(l);
        break;
    }
    print_list(l);
  }

  free_list(l);

  return 0;
}
