// Bernardo Lanza de Assunção
// RA164836
// LAB03 - Celebridades
// Identificação de celebridades (conhecido por todxs, não conhece ninguém) a partir das relações inputadas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRINGMAX 50
#define DELIM " conhece "


typedef struct {
  char name[STRINGMAX];
  int knows_n, known_by_n;
} person;

// Encontra as pessoas da relação e atualiza os 'placares' de conhecidos
void match_n_count(person *people, int *n, char *name1, char *name2){
  int i, flag1=1, flag2=1, flag_eq=1;

  // Se as duas strings forem iguais, ativa uma flag especifica
  if(!strcmp(name1, name2))
    flag_eq = 0;

  // Procura até encontrar o nome das duas pessoas ou o vetor de pessoas esgotar
  // Quando encontra um match, atualiza a qtdd de conhecidos
  for(i=0;i<*n && (flag1 || flag2);i++){
    if(flag1 && !strcmp(people[i].name, name1)){
      (people[i].knows_n)++;
      flag1 = 0;
    }
    if(flag2 && !strcmp(people[i].name, name2)){
      (people[i].known_by_n)++;
      flag2 = 0;
    }
  }

  // Se as pessoas nao forem encontradas, adicionar elas
  if(flag1){
    strcpy(people[*n].name,name1);
    (people[*n].knows_n)=1;
    (people[*n].known_by_n)=0;
    (*n)++;
  }
  if(flag2 && flag_eq){
    strcpy(people[*n].name,name2);
    (people[*n].knows_n)=0;
    (people[*n].known_by_n)=1;
    (*n)++;
  }
}

// Procura na lista de pessoas se alguém é conhecido por todxs e não conhece ninguém
int find_celebrity(person *people, int n){
  int i;
  for(i=0; i<n; i++){
    if(people[i].known_by_n == n-1 && people[i].knows_n == 0){
      return i;
    }
  }
  return -1;
}

int main(){
  int n = 0, result;
  char input[200],
       *clipper,
       name1[STRINGMAX],
       name2[STRINGMAX];
  person people[1000];

  while(scanf("%[^\n] ", input) != EOF){

    // Separa a string em duas, cortando o delimitador (neste caso, o delimitador é " conhece ")
    clipper = strstr(input, DELIM);
    *name1 = '\0'; // safety handler pra evitar que a string 1 quebre
    strncat(name1, input, strlen(input)-strlen(clipper));
    strcpy(name2, clipper+strlen(DELIM));

    // Chama a função de atualização da lista de pessoas
    match_n_count(people,&n,name1,name2);
  }

  result = find_celebrity(people, n);
  if(result > 0)
    printf("%s e' celebridade.\n", people[result].name);
  else
    printf("Nao ha' celebridade.\n");
}
