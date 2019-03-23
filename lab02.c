// Bernardo Lanza de Assunção
// RA164836
// LAB02 - Frequência
// Impressão de uma tabela de frequências que exiba as triplas inputadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[ ]){
    int i,j; //i contador de colunas, j contador de linhas
    int new_number;
    char c;
    char input[1000];

    char *pointer;
    char *limit;

    for(i=0;i<argc;i++){
        new_number = 0;
        pointer = &argv[1]
        pointer++;
        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += atoi(*pointer);
          }
          pointer++;
        }
        printf(" %d |", a[i]);

        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += atoi(*pointer);
          }
          pointer++;
        }
        pointer++;
        c = *pointer;
        for(i=0;i<new_number;i++)
            printf("%c", c);
        printf(" %d\n", new_number);
    }
}
