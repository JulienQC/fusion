#include <stdlib.h>
#include <stdio.h>


void fusion(int * t, int n){

  int i = 0;
  int j = n;  
  while((i < n) && (j < 2 * n)){
    if(t[i] > t[j]){
      printf("%d ", t[j++]);
    }else{
      printf("%d ", t[i++]);
    }
  }
  while(i < n){
    printf("%d ", t[i++]);
  }
  while(j < 2 * n){
    printf("%d ", t[j++]);
  }    
  putchar('\n');
  
}


int main(int argc, char* argv[]){

  int n;
  scanf("%d", &n);
  int * t = malloc(2 * n * sizeof(int));

  int i = 0;
  for(i = 0; i < 2 * n; i++){
      scanf("%d", &t[i]);
  }
  
  fusion(t, n);  
  
  free(t);

  return EXIT_SUCCESS;
}


