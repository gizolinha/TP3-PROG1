#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*Funcao vai ordenar o vetor de structs racionais usando 
  a logica do Insertion Sort*/
void ordenar_vet(struct racional *v[], int tamanho){
    
    int i;

    for (int j = 1; j < tamanho; j++) 
        // Verifica se o denominador é zero
        if (v[j]->den == 0) 
            return; 
        

    for (int j = 1; j < tamanho; j++) {

        struct racional *chave;

        if(!(chave = malloc(sizeof(struct racional))))
            return;

        chave->num = v[j]->num;
        chave->den = v[j]->den;

        i = j-1;

        while (i >= 0 && compara_r(v[i],chave) > 0 ){

            v[i + 1]->num = v[i]->num;
            v[i + 1]->den = v[i]->den;

            i--;
        }

        v[i+1]->num = chave->num;
        v[i+1]->den = chave->den;

        destroi_r(chave);
    }
    
}

/* Função para eliminar racionais inválidos de um vetor */
void eliminar_elemento(struct racional *v[], int *tamanho) {
    int j = 0;  // Índice para a nova posição do vetor

    // Percorre o vetor original
    for (int i = 0; i < *tamanho; i++) {
        if (valido_r(v[i])) {
            // se valido, reorganiza o vetor)
            v[j++] = v[i];
        } else {
            // se invalido, libera a memória
            destroi_r(v[i]);
        }
    }

    // atualiza o tamanho do vetor depois de tirar os invalidos
    *tamanho = j;
}



struct racional *soma_total (struct racional *v[], int tamanho) {
    struct racional *result_soma_total;

    // aloca memoria pro resultado
    if (!(result_soma_total = malloc(sizeof(struct racional)))) {
        return NULL;
    }
    
    result_soma_total->num = 0;  // inicializa o numerador
    result_soma_total->den = 1;  // inicializa o denominador

    for(int i = 0; i < tamanho; i++) {
        if (valido_r(v[i])) {  // ve se eh valido antes de somar
            result_soma_total->num = result_soma_total->num * v[i]->den + v[i]->num * result_soma_total->den;
            result_soma_total->den *= v[i]->den;
        }
    }
   
    return result_soma_total;
}


//preenche o vetor com n numeros racionais lidos na entrada
void le_vet(struct racional *v[], int tam) {
    int numerador, denominador; 

    for (int i = 0; i < tam; i++) {
        scanf("%d %d", &numerador, &denominador);
        v[i] = cria_r(numerador, denominador);
    }
}




int main () {
      
    /* equivalente a struct racional *v[] */
    struct racional **v;  
    struct racional *soma_total_vet; 
    int n,fim, i;
    n = 0;

    //le um valor n (tamanho do vetor) tal que 0 < n < 100, garante o numero dentro do intervalo
    fim = 1;
    do
    {
        scanf("%d", &n);
        if (n > 0 && n < 100)
            fim = 0;
    } while (fim);
    
    if(!(v = malloc(n * sizeof(struct racional *))))
        return -1;
    
    //le vetor
    le_vet(v,n);

    //imprime o vetor de racionais
    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v[i]);
        printf(" "); 
    }
    printf("\n");

     //elimina os NaNs e imprime
    eliminar_elemento(v,&n);

    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v[i]);
        printf(" "); 
    }
     printf(" \n"); 


      //ordena o vetor e imprime
    ordenar_vet(v,n);

    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v[i]);
        printf(" "); 
    }
     printf(" \n"); 


    //soma os elementos do vetor e imprime
    soma_total_vet = soma_total(v,n);

    printf("SOMA = ");
    imprime_r(soma_total_vet);
    printf("\n");


    //destroi e imprime
    for (int i = 0; i < n; i++) {
        destroi_r(v[i]);
        v[i] = NULL;
    }
    
    printf("VETOR = ");
    for (i = 0; i < n; i++) {
        imprime_r(v[i]); 
        printf(" ");        
    } 
     printf(" \n"); 
    
    destroi_r(soma_total_vet);
    free(v);

  return (0) ;
}

