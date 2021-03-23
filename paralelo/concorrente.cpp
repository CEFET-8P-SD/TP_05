#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

// Define o tamanho da vetor de primos
#define TAM 15
// Define a quantidade de threads a serem usadas
#define NTHREADS 6
// Define a variável para o controle da região crítica
pthread_mutex_t mutex;
// Cria vetor para alocar os números primos
int *vetor_primos;
// Define variável de índice para inserir no vetor
int indice = 0;

// função que determina se o número é primo e adiciona no
// vetor de primos
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

// função que imprimi o vetor de primos
void print_vetor() {
    printf("print vetor de primos primos\n");
    for (int i = 0; i < indice; i++) {
        printf("%d ", vetor_primos[i]);
    }
    printf("\n");
}

// método main
int main(int argc, char** argv) {
    // aloca espaço do vetor de primos na memória
    vetor_primos = (int*) malloc(sizeof (int*) * TAM);

    // inicia a variável de controle de região crítica
    pthread_mutex_init(&mutex, NULL);

    // cria um vetor de threads de tamanho NTHREADS
    pthread_t threads[NTHREADS];
    int *num;

    // laço para disparar todas as threads
    for (int i = 0; i < NTHREADS; i++) {
        num = (int *) malloc(sizeof (int));
        *num = i + 1;

        if (pthread_create(&threads[i], NULL, calcula_primo, (void *) num)) {
            printf("--ERRO at create thread id %d--\n", i);
            return -1;
        }
    }

    // laço para esperar o término de todas as threads
    for (int i = 0; i < NTHREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("--ERRO: pthread_join() \n");
            return -1;
        }
    }
    print_vetor();
    return 0;
}
