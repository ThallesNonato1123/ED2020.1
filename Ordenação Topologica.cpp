#include <string>
#include <iostream>
#include <cstring>

typedef  struct grafo Grafo;
using namespace std;
struct grafo{
    int nv;
    int grau_max;
    int **link_arestas;
    int *grau;
    int *Ograu;
};

Grafo *cria_grafo(int nv, int grau_max){
    Grafo *g= (Grafo*) malloc(sizeof(struct grafo));
    if(g != NULL){
        int i;
        g -> nv = nv;
        g -> grau_max = grau_max + 1;
        g -> grau = (int*)calloc(nv,sizeof(int));
        g -> Ograu = (int*)calloc(nv,sizeof(int));
        g -> link_arestas = (int**)malloc(nv*sizeof(int*));
        for(i=0; i<nv;i++)
        g -> link_arestas[i] = (int*)malloc((grau_max + 1)*sizeof(int));
    }
    return g;
}

void libera_grafo(Grafo *g){
    if(g != NULL){
        int i;
        for(i=0;i<g ->nv; i++)
            free(g->link_arestas[i]);
        free(g->link_arestas);
    }
    free(g->Ograu);
    free(g->grau);
    free(g);
}



int insereAresta(Grafo *g, int orig, int dest){
    if(g == NULL)
        return 0;
    if(orig < 0 || orig>= g->nv)
        return 0;
    if(dest < 0 || dest>=g->nv)
        return 0;
    
    g ->link_arestas[orig][g->grau[orig]] = dest;
    g-> grau[orig]++;
    g-> Ograu[dest - 1]++;
    return 1;
}

int is_num(char c) {
  if(c>47&&c<58) {
    return 1;
  }
  return 0;
}

int validos(char* texto) {
  int contador=0;
  for(int i=0;i<(int)strlen(texto);i++)
    if(is_num(texto[i])&&!is_num(texto[i+1]))
      contador+=1;
  return contador;
}

void separarString(char* buf,int* listaarestas,int validos) {
  int i=0;
  char *p = strtok (buf, " ");
  char *array[100];
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok (NULL, " ");
  }
  for (int i = 0; i < validos; i++) {
    listaarestas[i] = atoi(array[i]);
  }
}

bool isvisited(int *lista, int n, int x){
  for(int i = 0; i < n; i++ ){
    if(lista[i] == x)
    return true;
  }
  return false;
}

bool tudoNulo(int *lista, int n) {
  for(int i=0;i<n;i++)
    if(lista[i])
      return false;
  return true;
}

int main(){
    Grafo *g;
    int nv, na,val;
    char entrada[100];

    cin >> nv >> na;
    g = cria_grafo(nv + 1,na + 1);
    cin.getline(entrada,100);

  for(int i = 0; i<nv; i++){
    cin.getline(entrada,100);
    val = validos(entrada);
    int ar[val];
    separarString(entrada, ar, val);
    
    for(int j=0; j<val;j++){
      insereAresta(g,i,ar[j]);
    }
  }

  
  int posicaotopologica = 0;
  int ordemtopologica[nv];
  for(int i=0; i<nv;i++){
    ordemtopologica[i]=0;
  }
  
  while(!tudoNulo(g->Ograu,nv)) {
    for(int i = 0; i< (g->nv) - 1;i++){

      if(g->Ograu[i] == 0 && isvisited(ordemtopologica,nv,i+1) == false){
        ordemtopologica[posicaotopologica] = i + 1;
        for(int j = 0; j< g->grau_max; j++){
          if(g->link_arestas[i][j] !=0){
            g->Ograu[g->link_arestas[i][j]-1]--;
            g->link_arestas[i][j] = 0;
            
          }     
        }
          break;
      }
    }
    posicaotopologica++;
  }

    for(int i = 0; i< (g->nv) - 1;i++){

      if(g->Ograu[i] == 0 && isvisited(ordemtopologica,nv,i+1) == false){
        ordemtopologica[posicaotopologica] = i + 1;
        for(int j = 0; j< g->grau_max; j++){
          if(g->link_arestas[i][j] !=0){
            g->Ograu[g->link_arestas[i][j]-1]--;
            g->link_arestas[i][j] = 0;
            
          }     
        }
      }
    }
    posicaotopologica++;

  for(int i=0 ; i< nv;i++){
    printf("%d ",ordemtopologica[i]);
  } 


}

