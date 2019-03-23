/* Bernardo Lanza de Assunção
// RA164836
// LAB01 - ASCII
// Impressão de uma tabela ASCII */
#include<stdio.h>

int main(){
    int i, j; /* i contador de colunas, j contador de linhas */

    /* imprime o header */
    printf("      +0 +1 +2 +3 +4 +5 +6 +7 \n");
    printf("    +------------------------ \n");

    /* imprime a tabela */
    for(i=32;i<=120; i+=8){
        /* imprime index i */
        if(i<100)
            printf(" ");
        printf("%d | ", i);

        /* imprime caracteres da fileira + quebra de linha */
        for(j=0; j<=7; j++){
            if(i==120 && j==7)
              printf("   ");
            else
              printf(" %c ", i+j);
            /*  teste de formatacao
                if(j<7)
                printf(" "); */
        }
        printf("\n");
    }
}
