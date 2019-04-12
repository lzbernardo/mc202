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

void *duplicate_vector(Seq *my_seq){
  int *aux = malloc(2*my_seq->vector_size*sizeof(int));
  int i;

  // copia vetor antigo pra vetor novo
  for(i=0; i<(my_seq->seq_size); i++){
    aux[i] = my_seq->vector[(my_seq->start+i)%my_seq->seq_size]; // os elementos do vetor antigo entram no novo vetor de maneira organizada a partir da posição 0. (start+i)%seq_size é a fórmula para circular dentro dos endereços do vetor de maneira eficiente
  }

  my_seq->seq_size *= 2; // atualiza tamanho do vetor
  free(myseq->vector); // libera vetor antigo
  my_seq->vector = aux; // atualiza vetor
}

void reduce_vector(Seq *my_seq){
  int *aux;
  if(vector_size < 4){
    printf("não reduzimos vetores menores que 4 aqui não meu consagrado\n");
    return;
  }

  aux = malloc(0.25*my_seq->vector_size*sizeof(int));
  int i;

  // copia vetor antigo pra vetor novo
  for(i=0; i<(my_seq->seq_size); i++){
    aux[i] = my_seq->vector[(my_seq->start+i)%my_seq->seq_size]; // os elementos do vetor antigo entram no novo vetor de maneira organizada a partir da posição 0. (start+i)%seq_size é a fórmula para circular dentro dos endereços do vetor de maneira eficiente
  }

  my_seq->seq_size *= 0.25; // atualiza tamanho do vetor
  free(myseq->vector); // libera vetor antigo
  my_seq->vector = aux; // atualiza vetor
}

void push_start(Seq ){

}

void push_end(){

}

void pop_start(){

}

void pop_end(){

}

void print_start(){

}

void print_end(){

}

int main(){
  char command[MAX_COMMAND];
  Seq my_seq;

  my_seq.start = 0;
  my_seq.end = 0;
  my_seq.vector_size = 1;
  my_seq.vector = malloc(sizeof(int));

  while(true){
    scanf("%s ", command);
    if(strcmp(command, "exit")) break;
  }
  return 0;
}
