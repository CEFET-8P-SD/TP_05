#include <iostream>
#include <pthread.h>

#define NUMERO_THREADS 6

pthread_mutex_t mutex;

//Variáveis globais para evitar parâmetros
int index = 0;
int* vetor_primos;

void imprime_primos(int* vetor_primos, int numero_maximo)
{
    
    for (int i = 0; i < numero_maximo; i++)
    {
        printf("%d     ", vetor_primos[i]);
    }

}


void *teste_primo(void *num){
    int *numero = (int *) num;
    int counter = 0;
    int teste = 1;

    for (int i = 2; i < *numero/2+1; i++)
    {
        
        if (*numero % i == 0)
        {
            teste = 0;
            break;
        }

    }

    pthread_mutex_lock(&mutex);
    
    if (teste==1)
    {
        vetor_primos[index];
        index+=1;
    }
    
    pthread_mutex_lock(&mutex);

    return 0;
}



int main(int argc, char const *argv[])
{

    //Vetor de Primos
    int numero_maximo = 500;
    vetor_primos = (int*) malloc(sizeof(int*) * numero_maximo);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUMERO_THREADS];

    int *num;

    for (int i = 0; i < NUMERO_THREADS; i++)
    {
        if(pthread_create(&threads[i], NULL, teste_primo, (void *) *num)){
            printf("ERROR!!! - Thread: %d.\n");
            return -1;
        }

    }
    

    for (int i = 0; i < NUMERO_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("--Erro: pthread_join() \n");
            return -1;
        }
        
    }
    
    
    imprime_primos(vetor_primos, numero_maximo);


    return 0;
}
