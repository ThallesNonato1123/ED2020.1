#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 64

void print(int **M, int tam){
    for(int i = 0; i< tam; i++){
        for(int j = 0 ; j<tam ; j++){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int gera_aleatorio(int menor,int maior) { 
    return menor + rand() % (maior+1-menor);
}

int **matrizalocada(int tam){
    int i;
    int **M;
    M = (int**)malloc(sizeof(int*)* tam );
    if(M == NULL){
        printf("erro\n");
        exit(1);
    }

    for( i = 0 ; i<tam ; i++){
        M[i]= (int*)malloc(sizeof(int)*tam);
        if(M[i]== NULL){
            printf("erro\n");
            exit(1);
        }
    }
    return M;
}

int **preenchermatriz(int **M, int tam){
    for(int i= 0 ; i<tam ; i++){
        for(int j = 0;j<tam; j++)
        M[i][j]= gera_aleatorio(-1000,1000);
    }
    return M;
}

void DesalocaMatrix(int **M, int tam){
    int i;
    for(i=0;i<tam;i++)
        free(M[i]);
    free(M);
}

int **multimatrix(int **A, int **B, int tam){
    int **M;
    M = matrizalocada(tam);
    for(int i = 0 ; i < tam ; i++){
        for(int j = 0 ; j<tam ; j++){
            M[i][j]=0;
            for( int k=0; k<tam; k++)
                M[i][j]+= A[i][k] * B[k][j];
        }
    }
    return M;
}

int **soma_matrizes(int **A, int  **B, int tam){
    int **M;
    M = matrizalocada(tam);
    for(int i = 0 ; i < tam ; i++){
        for(int j = 0 ; j<tam ; j++){
                M[i][j]= A[i][j] + B[i][j];
        }
    }
    return M;
}

int **subtrai_matrizes(int **A, int  **B, int tam){
    int **M;
    M = matrizalocada(tam);
    for(int i = 0 ; i < tam ; i++){
        for(int j = 0 ; j<tam ; j++){
                M[i][j]= A[i][j] - B[i][j];
        }
    }
    return M;
}

int **buscarquadrante(int **M , int inilinha, int inicoluna, int tam){
    int **R;
    R = matrizalocada(tam);
    for(int i = 0 ; i < tam ; i++ ){
        for(int j = 0 ; j < tam ; j++){
            R[i][j] = M[i + inilinha][j + inicoluna];
        }
    }
    return R;
}

int **Strassen(int **A , int **B,  int tam){
    int **C;
    
    C = matrizalocada(tam);

    if (tam <= 128) {
    C= multimatrix(A,B,tam);
    return C;
    }
    
    
    int **aux1, **aux2, **aux3, **aux4;
    int **m1, **m2,**m3,**m4,**m5,**m6,**m7;
    
    aux1 = buscarquadrante(A,0,0,tam/2);
    
    aux2 = buscarquadrante(A,tam/2,tam/2,tam/2);
    
    aux3= soma_matrizes(aux1,aux2,tam/2);

    
    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);

    aux1 = buscarquadrante(B,0,0,tam/2);
    aux2 = buscarquadrante(B,tam/2,tam/2,tam/2);

    aux4=soma_matrizes(aux1,aux2,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    
    m1 = Strassen(aux3,aux4,tam/2);
    
    DesalocaMatrix(aux3,tam/2);
    DesalocaMatrix(aux4,tam/2);

    aux1= buscarquadrante(A,tam/2,0,tam/2);
    aux2 = buscarquadrante(A,tam/2,tam/2,tam/2);

    aux3= soma_matrizes(aux1,aux2,tam/2);
    
    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    
    aux1= buscarquadrante(B,0,0,tam/2);
    
    m2 = Strassen(aux3,aux1,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux3,tam/2);

    aux1= buscarquadrante(A,0,0,tam/2);
    aux2 = buscarquadrante(B,0,tam/2,tam/2);
     
    aux3= buscarquadrante(B,tam/2,tam/2,tam/2);
     
    aux4 = subtrai_matrizes(aux2,aux3,tam/2);
    
    
    m3 = Strassen(aux1,aux4,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    DesalocaMatrix(aux3,tam/2);
    DesalocaMatrix(aux4,tam/2);

    aux1= buscarquadrante(A,tam/2,tam/2,tam/2);
    aux2= buscarquadrante(B,tam/2,0,tam/2);
    aux3= buscarquadrante(B,0,0,tam/2);
    aux4= subtrai_matrizes(aux2,aux3,tam/2);
    
    m4= Strassen(aux1,aux4,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    DesalocaMatrix(aux3,tam/2);
    DesalocaMatrix(aux4,tam/2);

    aux1=buscarquadrante(A,0,0,tam/2);
    aux2= buscarquadrante(A,0,tam/2,tam/2);
    aux3=buscarquadrante(B,tam/2,tam/2,tam/2);
    aux4=soma_matrizes(aux1,aux2,tam/2);
    
    m5=Strassen(aux4,aux3,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    DesalocaMatrix(aux3,tam/2);
    DesalocaMatrix(aux4,tam/2);

    aux1=buscarquadrante(A,tam/2,0,tam/2);
    aux2= buscarquadrante(A,0,0,tam/2);
    
    aux3=subtrai_matrizes(aux1,aux2,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);

    aux1=buscarquadrante(B,0,0,tam/2);
    aux2= buscarquadrante(B,0,tam/2,tam/2);

    aux4=soma_matrizes(aux1,aux2,tam/2);

    m6 = Strassen(aux3,aux4,tam/2);

    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);
    DesalocaMatrix(aux3,tam/2);
    DesalocaMatrix(aux4,tam/2);

    aux1=buscarquadrante(A,0,tam/2,tam/2);
    aux2=buscarquadrante(A,tam/2,tam/2,tam/2);

    aux3=subtrai_matrizes(aux1,aux2,tam/2);
    
    DesalocaMatrix(aux1,tam/2);
    DesalocaMatrix(aux2,tam/2);

    aux1=buscarquadrante(B,tam/2,0,tam/2);
    aux2=buscarquadrante(B,tam/2,tam/2,tam/2);

    aux4=soma_matrizes(aux1,aux2,tam/2);

    m7 = Strassen(aux3,aux4,tam/2);

    for(int i = 0; i<tam/2; i++){
        for(int j=0;j<tam/2;j++){
            C[i][j]= m1[i][j]+ m4[i][j]-m5[i][j]+m7[i][j];
            C[i][j+tam/2]=m3[i][j]+m5[i][j];
            C[i+tam/2][j]=m2[i][j]+m4[i][j];
            C[i+tam/2][j+tam/2]=m1[i][j]-m2[i][j]+m3[i][j]+m6[i][j];
        }
    }
    return C;

}



int main(){
    int **A , **B, **R,**K;
    int tam, igual = 0;
    clock_t t,f;
    scanf("%d",&tam);
    
    A = matrizalocada(tam);
    B = matrizalocada(tam);
    R = matrizalocada(tam);
    K = matrizalocada(tam);
    preenchermatriz(A,tam);
    preenchermatriz(B,tam);
    
    t= clock();
    R = Strassen(A,B,tam);
    t = clock() - t;
   

    f= clock();
    K = multimatrix(A,B,tam);
    f = clock() - f; 
    for(int i = 0; i< tam; i++){
        for(int j = 0; j<tam; j++){
            if( R[i][j] != K[i][j])
                igual++;
        }
    }
   
    if(igual == 0){
        printf("Resultado Correto, Tempo Strassen: %lf segundos\n", ((double)t)/((CLOCKS_PER_SEC)));
        printf("Resultado Correto, Tempo Multi Tradicional: %lf segundos\n", ((double)f)/((CLOCKS_PER_SEC)));
    }
    
    return 0;
}