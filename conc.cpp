// Bibliotecas utilizadas
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <cmath>    

//Variáveis globais
pthread_mutex_t mutex;  // Variável que será usada para controlar a região crítica

int *vetor_de_primos;   

float tempo_de_execucao = 5.0;  // Tempo permitido de execução
int indice_atual_vetor = 0;     // Variável que controla o índice do vetor
int numero = 1;                 // número a ser testado no momento atual

//Método usado para testes: Imprime o vetor de primos
void imprime_primos()
{
    printf("%d", vetor_de_primos[0]);

    for (int i = 1; i < indice_atual_vetor; i++)
    {
        printf("%d     ", vetor_de_primos[i]);
    }

}

//Método que testa se um dado número é ou não primo
void teste_primo(int num){
    int counter = 0;
    int teste = 1;

    // Laço de repetição que testara se um número divide por todos os números até sua raiz quadrada
    for (int i = 2; i < sqrt(num); i++)
    {
        
        if (num % i == 0)
        {
            teste = 0;
            break;
        }

    }

    // Se o teste de primos é positivo
    if (teste==1)
    {
        // Inicia região crítica
        pthread_mutex_lock(&mutex);
        
        //  Acrescenta um dado númeo ao veto de primos
        vetor_de_primos[indice_atual_vetor] = num;
        // Incrementa o índice do vetor
        indice_atual_vetor++;
        
        // Desativa região crítica
        pthread_mutex_unlock(&mutex);
    }
    

}

// Método que monitora e chama os teste de primos
void *run(void *num)
{

    // Captura o tempo de inicio
    clock_t tempo_de_inicio = clock();

    // Enquanto o tempo de inicio estiver no intervalo definido
    while ((clock() - tempo_de_inicio)/CLOCKS_PER_SEC <= tempo_de_execucao)
    {

        // Inicia região crítica
        pthread_mutex_lock(&mutex);

        // Incrementa em dois o número a ser testado para evitar pares
        numero += 2;

        // Desativa região crítica
        pthread_mutex_unlock(&mutex); 

        //Chama o método que testa os número primos
        teste_primo(numero);    
    }

    // Finaliza a chamada das threads
    pthread_exit(NULL);


}

int main(int argc, char const *argv[])
{

    // Aloca memória para o vetor de primos
    vetor_de_primos = (int*) malloc(sizeof(int*) * 100000000);
    //Define o número de threads
    int numero_de_threads = 6;
    
    int *num;

    // Crie o vetor de threads
    pthread_t threads[numero_de_threads];
    
    // Inicie as threads
    for (int i = 0; i < numero_de_threads; i++)
    {
        if(pthread_create(&threads[i], NULL, run, (void *) num)){
            printf("ERROR!!! - Thread: %d.\n", i);
            return -1;
        }

    }

    // Desative as threads
    for (int i = 0; i < numero_de_threads; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("--Erro: pthread_join() \n");
            return -1;
        }
        
    }
    
    // Elimine o mutex
    pthread_mutex_destroy(&mutex);

    // Imprime o tempo e o número total de primos alcançados
    printf("Tempo gasto %f. Número alcancado: %d.", tempo_de_execucao, indice_atual_vetor-1);
    //imprime_primos();

    return 0;
}
