// Bernardo Lanza de Assunção
// RA164836
// LAB02 - Frequência
// Impressão de uma tabela de frequências que exiba as triplas inputadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[ ]){
    int i; // contador simples
    int new_number; // abriga o número inputado em caracteres (já traduzido pra int)
    char c; // abriga o caractere especial da tabela
    char input[100]; // abriga a tripla
    char *pointer; // apontador simples
    char *limit; // limite de corte para números inputados

    // escaneia entradas até encontrar EOF
    while(scanf("%s", input) != EOF){

        // lê o primeiro número da tripla
        new_number = 0;
        pointer = strchr(input,'(');
        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += (*pointer - 48);
          }
          pointer++;
        }

        // imprime primeiro número da tripla
        if(new_number<100) printf(" ");
        if(new_number<10) printf(" ");
        printf("%d |", new_number);

        // lê o segundo número da tripla
        new_number = 0;
        pointer++;
        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += (*pointer - 48);
          }
          pointer++;
        }
        pointer++;
        c = *pointer;  // lê o caractere da tripla

        // imprime a barra e o número correspondente
        for(i=0;i<new_number;i++)
            printf("%c", c);
        printf(" %d\n", new_number);
    }


    /* Versão do programa feita pra quando eu tinha entendido que o input seria por argumentos em cli =(
    for(i=1;i<argc;i++){

        new_number = 0;
        pointer = argv[i];
        pointer++;
        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += (*pointer - 48);
          }
          pointer++;
        }
        if(new_number<100) printf(" ");
        if(new_number<10) printf(" ");
        printf("%d |", new_number);


        new_number = 0;
        pointer++;
        limit = strchr(pointer, ',');
        while(pointer != limit){
          if(*pointer>='0' && *pointer<='9'){
            new_number *= 10;
            new_number += (*pointer - 48);
          }
          pointer++;
        }
        pointer++;
        c = *pointer;
        for(j=0;j<new_number;j++)
            printf("%c", c);
        printf(" %d\n", new_number);
    } */
}
