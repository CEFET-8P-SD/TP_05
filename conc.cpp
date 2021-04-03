
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <cmath>    

pthread_mutex_t mutex; 


int *vetor_de_primos;

float tempo_de_execucao = 5.0;
int indice_atual_vetor = 0;
int numero = 1;

void imprime_primos()
{
    printf("%d", vetor_de_primos[0]);

    for (int i = 1; i < indice_atual_vetor; i++)
    {
        printf("%d     ", vetor_de_primos[i]);
    }

}

void teste_primo(int num){
    int counter = 0;
    int teste = 1;

    for (int i = 2; i < sqrt(num); i++)
    {
        
        if (num % i == 0)
        {
            teste = 0;
            break;
        }

    }


    if (teste==1)
    {
        pthread_mutex_lock(&mutex);
        vetor_de_primos[indice_atual_vetor] = num;
        indice_atual_vetor++;
        pthread_mutex_unlock(&mutex);
    }
    

}

void *run(void *num)
{

    clock_t tempo_de_inicio = clock();

    while ((clock() - tempo_de_inicio)/CLOCKS_PER_SEC <= tempo_de_execucao)
    {

        pthread_mutex_lock(&mutex);

        numero += 2;

        pthread_mutex_unlock(&mutex);

        
        teste_primo(numero);
    }

    pthread_exit(NULL);


}

int main(int argc, char const *argv[])
{

    vetor_de_primos = (int*) malloc(sizeof(int*) * 100000000);
    int numero_de_threads = 6;
    int *num;

    pthread_t threads[numero_de_threads];
    
        for (int i = 0; i < numero_de_threads; i++)
    {
        if(pthread_create(&threads[i], NULL, run, (void *) num)){
            printf("ERROR!!! - Thread: %d.\n", i);
            return -1;
        }

    }

    for (int i = 0; i < numero_de_threads; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("--Erro: pthread_join() \n");
            return -1;
        }
        
    }
    
    pthread_mutex_destroy(&mutex);

    printf("Tempo gasto %f. Número alcancado: %d.", tempo_de_execucao, indice_atual_vetor);
    //imprime_primos();

    return 0;
}
