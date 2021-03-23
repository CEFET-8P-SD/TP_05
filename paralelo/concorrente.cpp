#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

// Define o tamanho da matriz quadrada a ser preenchida
#define TAM 1000
#define NTHREADS 6

pthread_mutex_t mutex;

// Cria a referência global para a vetor com os numeros primos
int *vetor;
int indice = 0;

void *isPrimo(void *aux) {
    pthread_mutex_lock(&mutex);
    int *num = (int *) aux;
    printf("num primo: %d\n", *num);
    int isPrimo = 1;

    for (int i = 2; i <= *num / 2; i++) {
        if (*num % i == 0) {
            isPrimo = 0;
            break;
        }
    }
    printf(isPrimo ? "primo" : "não primo");
    printf("\n");
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main(int argc, char** argv) {
    vetor = (int*) malloc(sizeof (int*) * TAM);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NTHREADS];
    int *num;

    for (int i = 0; i < NTHREADS; i++) {
        num = (int *) malloc(sizeof (int));
        *num = i + 1;

        if (pthread_create(&threads[i], NULL, isPrimo, (void *) num)) {
            printf("--ERRO at create thread id %d--\n", i);
            return -1;
        }
    }

    for (int i = 0; i < NTHREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("--ERRO: pthread_join() \n");
            return -1;
        }
    }

    return 0;
}
