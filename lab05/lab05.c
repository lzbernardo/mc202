// Bernardo Lanza de Assunção
// RA164836
// LAB05 - Dinâmico
// Realiza operações de inserção, remoção e print em uma fila circular armazenada num vetor de tamanho dinâmico
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND 13

typedef struct seq{
  int start;
  int seq_size;
  int *vector;
  int vector_size;
} Seq;

// Verifica se a sequência está vazia ou não
int is_empty(Seq myseq){
  if(myseq.seq_size == 0)
    return 1;
  else
    return 0;
}

// Verifica & imprime na tela se a sequência está vazia ou não
void print_is_empty(Seq myseq){
  int is = is_empty(myseq);
  if(is)
    printf("yes\n");
  else
    printf("no\n");
}

// Duplica o tamanho do vetor alocado dinamicamente
void duplicate_vector(Seq *myseq){
  int *aux = malloc(2*myseq->vector_size*sizeof(int));
  int i;

  // copia vetor antigo pra vetor novo
  for(i=0; i<(myseq->seq_size); i++){
    aux[i] = myseq->vector[(myseq->start+i)%myseq->vector_size]; // os elementos do vetor antigo entram no novo vetor de maneira organizada a partir da posição 0. (start+i)%seq_size é a fórmula para circular dentro dos endereços do vetor de maneira eficiente
  }

  // atualiza informações sobre a sequência e libera a memória do vetor antigo
  myseq->vector_size *= 2;
  free(myseq->vector);
  myseq->vector = aux;
  myseq->start = 0;
}

// Reduz o tamanho do vetor dinâmico em um quarto
void reduce_vector(Seq *myseq){
  int *aux;
  int i;

  if(myseq->vector_size < 4){
    printf("BUG: Not able to reduce vectors w/ less than 4 memory slots\n");
    return;
  }

  aux = malloc(0.25*myseq->vector_size*sizeof(int));

  // copia vetor antigo pra vetor novo
  for(i=0; i<(myseq->seq_size); i++){
    aux[i] = myseq->vector[(myseq->start+i)%myseq->vector_size]; // os elementos do vetor antigo entram no novo vetor de maneira organizada a partir da posição 0. (start+i)%seq_size é a fórmula para circular dentro dos endereços do vetor de maneira eficiente
  }

  // atualiza informações sobre a sequência e libera a memória do vetor antigo
  myseq->vector_size *= 0.25;
  free(myseq->vector);
  myseq->vector = aux;
  myseq->start = 0;
}

// Insere um novo elemento no início da sequência
void push_start(Seq *myseq, int n){
  // caso necessário, duplica o espaço do vetor dinâmico
  if(myseq->vector_size == myseq->seq_size)
    duplicate_vector(myseq);

  // atualiza infos
  myseq->seq_size++;
  myseq->vector[(myseq->start + myseq->vector_size -1)%myseq->vector_size] = n;
  myseq->start = (myseq->start + myseq->vector_size -1)%myseq->vector_size;
}

// Insere um novo elemento no final da sequência
void push_end(Seq *myseq, int n){
  if(myseq->vector_size == myseq->seq_size)
    duplicate_vector(myseq);

  // atualiza infos
  myseq->seq_size++;
  myseq->vector[(myseq->start + myseq->seq_size + myseq->vector_size - 1)%myseq->vector_size] = n;
}

// Retira um elemento do início da sequência
void pop_start(Seq *myseq){
  if(is_empty(*myseq))
    return;

  myseq->vector[myseq->start] = -1;
  myseq->start = (myseq->start + 1)%myseq->vector_size;
  myseq->seq_size--;
  if(myseq->seq_size > 0 && myseq->seq_size <= 0.25*myseq->vector_size)
    reduce_vector(myseq);
}

// Retira um elemento do fim da sequência
void pop_end(Seq *myseq){
  if(is_empty(*myseq))
    return;
  myseq->vector[(myseq->start + myseq->seq_size - 1)%myseq->vector_size] = -1;
  myseq->seq_size--;
  if(myseq->seq_size > 0 && myseq->seq_size <= 0.25*myseq->vector_size)
    reduce_vector(myseq);
}

// Imprime primeiro elemento da sequência
void print_start(Seq myseq){
  if(!is_empty(myseq))
    printf("%d\n", myseq.vector[myseq.start]);
}

// Imprime último elemento da sequência
void print_end(Seq myseq){
  if(!is_empty(myseq))
    printf("%d\n", myseq.vector[(myseq.start + myseq.seq_size - 1)%myseq.vector_size]);
}

// DEBUGGING-ONLY FUNCTION
// void print_all(Seq myseq){
//   int i;
//   printf("- - - - - - - - - - - -\n");
//   printf("Seq: ");
//   for(i=0;i<myseq.seq_size;i++){
//     printf("%d ", myseq.vector[(myseq.start+i)%myseq.vector_size]);
//   }
//   printf("\n");
//   printf("Vector Size: %d\n", myseq.vector_size);
//   printf("Sequence Size: %d\n", myseq.seq_size);
//   printf("Sequence Start: %d (%d)\n", myseq.start, myseq.vector[myseq.start]);
//   printf("RAW Vector: ");
//   for(i=0;i<myseq.vector_size;i++){
//     printf("%d ", myseq.vector[i]);
//   }
//   printf("\n- - - - - - - - - - - -\n");
// }

int main(){
  int input;
  char command[MAX_COMMAND];
  Seq myseq;

  // inicialização da sequência vazia
  myseq.start = 0;
  myseq.seq_size = 0;
  myseq.vector_size = 1;
  myseq.vector = malloc(sizeof(int));

  // lê e processa entradas até encontrar o comando 'exit'
  while(1){
    scanf("%s", command);
    if(strcmp(command, "exit")==0)
      break;
    if(strcmp(command, "insert-first")==0){
      scanf("%d", &input);
      push_start(&myseq, input);
      // print_all(myseq);
    }
    if(strcmp(command, "insert-last")==0){
      scanf("%d", &input);
      push_end(&myseq, input);
      // print_all(myseq);
    }
    if(strcmp(command, "remove-first")==0){
      pop_start(&myseq);
      // print_all(myseq);
    }
    if(strcmp(command, "remove-last")==0){
      pop_end(&myseq);
      // print_all(myseq);
    }
    if(strcmp(command, "print-first")==0){
      print_start(myseq);
    }
    if(strcmp(command, "print-last")==0){
      print_end(myseq);
    }
    if(strcmp(command, "is-empty")==0){
      print_is_empty(myseq);
    }
  }
  return 0;
}
