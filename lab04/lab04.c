// Bernardo Lanza de Assunção
// RA164836
// LAB04 - Triangular
// Lê uma matriz triangular inferior e calcula novos valores z = (x-med)/dp considerando os valores de média e desvio padrão
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int n,i,j;
  double **matrix;
  double med=0, dp=0; // med = média, dp = desvio padrão

  // lê o valor de n e aloca uma matriz triangular inferior de ordem n
  scanf("%d", &n);
  matrix = malloc(sizeof(double*)*n);
  for(i=0;i<n;i++)
    matrix[i] = malloc(sizeof(double)*n);

  // lê os valores da matriz e vai agregando o valor de matrix[i][j] para calcular a média posteriormente
  for(i=0;i<n;i++){
    for(j=0;j<=i;j++){
      scanf("%lf", &matrix[i][j]);
      med += matrix[i][j];
    }
  }
  med /= (n*n+n)/2;

  // calcula o valor do desvio padrão da matriz
  for(i=0;i<n;i++)
    for(j=0;j<=i;j++)
      dp += (matrix[i][j]-med)*(matrix[i][j]-med);
  dp /= ((n*n+n)/2);
  dp = sqrt(dp);

  // imprime os valores de (x-m)/d e depois os valores de m e d
  for(i=0;i<n;i++){
    for(j=0;j<=i;j++){
      printf("%.12lf ", (matrix[i][j] - med)/dp);
    }
    printf("\n");
  }
  printf("\n%.12lf %.12lf \n", med, dp);

  // libera memória dinâmica
  for(i=0;i<n;i++)
    free(matrix[i]);
  free(matrix);

  return 0;
}
