#include <cstdlib>
#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

// Define o tamanho da vetor de primos
#define TAM 100000000
// Tempo de execucao em segundos
#define TEMPO_EXECUCAO 0.01
// Cria vetor para alocar os números primos
int *vetor_primos;
// Define variável de índice para inserir no vetor
int indice = 1;
// Define gerador de numeros para teste
int num = 3;

// função que imprimi o vetor de primos
void print_vetor() {
    printf("print vetor de primos primos\n");
    for (int i = 0; i < indice; i++) {
        printf("%d ", vetor_primos[i]);
    }
    printf("\n");
}

// função que determina se o número é primo e adiciona no
// vetor de primos caso seja
void verifica_primo() {
    int is_primo = 1;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            is_primo = 0;
            break;
        }
    }
    if (is_primo) {
        vetor_primos[indice] = num;
        indice += 1;
    }
}

// função que determina se o número é primo e adiciona no
// vetor de primos
void calcula_primo() {
    clock_t tempo;

    tempo = clock();
    while((clock() - tempo) * 1.0 / CLOCKS_PER_SEC <= TEMPO_EXECUCAO) {
        // chama método para verificar numero primo
        verifica_primo();
        // o passo de incremento do gerador é 2 para não analisar número pares
        num += 2;
    }
    tempo = clock() - tempo;
    printf("Tempo corrido %.5f s gerando %d numeros primos\n", tempo * 1.0 / CLOCKS_PER_SEC, indice);
}

// método main
int main(int argc, char** argv) {
    // aloca espaço do vetor de primos na memória
    vetor_primos = (int*) malloc(sizeof (int*) * TAM);

    // adicionado manual o único número par primo
    vetor_primos[0] = 2;

    // chamando método para gerar os números primos
    calcula_primo();
    // metodo para print do vetor de primos
    // print_vetor();
}

