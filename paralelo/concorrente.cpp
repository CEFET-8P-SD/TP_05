#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

// Define o tamanho da matriz quadrada a ser preenchida
#define TAM 15
#define NTHREADS 6

pthread_mutex_t mutex;

// Cria a referência global para a vetor com os numeros primos
int *vetor_primos;
int indice = 0;

void *calcula_primo(void *aux) {
    int *num = (int *) aux;
    int is_primo = 1;

    for (int i = 2; i <= *num / 2; i++) {
        if (*num % i == 0) {
            is_primo = 0;
            break;
        }
    }
    pthread_mutex_lock(&mutex);
    if (is_primo) {
        vetor_primos[indice] = *num;
        indice += 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void print_vetor() {
    printf("print vetor de primos primos\n");
    for (int i = 0; i < indice; i++) {
        printf("%d ", vetor_primos[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    vetor_primos = (int*) malloc(sizeof (int*) * TAM);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NTHREADS];
    int *num;

    for (int i = 0; i < NTHREADS; i++) {
        num = (int *) malloc(sizeof (int));
        *num = i + 1;

        if (pthread_create(&threads[i], NULL, calcula_primo, (void *) num)) {
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
    print_vetor();
    return 0;
}
