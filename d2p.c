#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

int isSorted(int * t, int n){
  int i;
  for(i = 0; i < n - 1; i++){
    if(t[i] > t[i + 1]){
      return 0;
    }
  }
  return 1;
}


int rechercheDichotomique(int e, const int * t, int p, int r){
  // recherche l'element e entre les indices p (inclus) et r (exclus) du tableau t
  // retourne l'indice de l'element du tableau egal a e s'il existe
  // sinon, retourne l'indice i du premier element tel que t[i] >= e
  // si tous les elements sont plus petits, retourner p

  if(p == r){
    //si l'intervalle est vide, retourner le premier index
    return p;
  }
  
  int i = (p + r) / 2;
  while(t[i] != e){
    if(t[i] > e){ //l'element devrait etre a gauche
      r = i;
    }else{ //l'element devrait etre a droite
      p = i + 1;
    }
    if(p == r){
      return p;
    }
    i = (p + r) / 2;
  }

  //si l'element est trouve, on verifie qu'il n'y a pas d'elements de meme
  //valeur a un indice inferieur
  while(i > 0 && t[i - 1] == t[i]){i--;}
  return i;
}

void interchanger(int * a, int * b){
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void fusionRec(const int * t, int * r, int p1, int r1, int p2, int r2, int p3){
  int n1 = r1 - p1; //nombre d'elements de la partie gauche
  int n2 = r2 - p2; //nombre d'elements de la partie droite

  if(n1 < n2){ //la partie de gauche doit être la plus grande
    interchanger(&n1, &n2);
    interchanger(&p1, &p2);
    interchanger(&r1, &r2);
  }

  if(n1 <= 0){
    return;
  }

  int q1 = (p1 + r1) / 2;
  int q2 = rechercheDichotomique(t[q1], t, p2, r2);
  int q3 = p3 + (q1 - p1) + (q2 - p2);
#pragma omp parallel
  {
#pragma omp single
    {
      r[q3] = t[q1];
#pragma omp task
      fusionRec(t, r, p1, q1, p2, q2, p3);
#pragma omp task
      fusionRec(t, r, q1 + 1, r1, q2, r2, q3 + 1);
    }
  }
}

void fusion(int * t, int n){

  int * r = malloc(2 * n * sizeof(int));
  int i;  
  for(i = 0; i < 2 * n; i++){
    r[i] = -1;
  }

#ifdef NTHREADS
  omp_set_num_threads(NTHREADS);
#endif
  
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  fusionRec(t, r, 0, n, n, 2 * n, 0);
  gettimeofday(&t2, NULL);
  
  if(isSorted(t, n)){
    printf("Fusion OK (%d threads created)\n", NTHREADS);
  }else{
    for(i = 0; i < 2 * n; i++){
      printf("%d ", r[i]);
    }
    putchar('\n');
  }

  printf("Time: %lu us\n",
	 (t2.tv_sec - t1.tv_sec) * 1000000 +
	 (t2.tv_usec - t1.tv_usec));
  
  free(r);
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
