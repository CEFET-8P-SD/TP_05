/*


    O problema a seguir deve ser abordade or meio de 3 métodos:
        1 - Monitore o tempo e contole a execução.
        2 - Teste se um dado número é primo ou não.
        3 - Imprima o teste.

    A estratégia a ser usada é a de região crítica. Basicamente, por meio dessa estratégia, 
    uma dada estrutura de dados só pode ser acessada por uma thread a cada vez. Para isso,
    é necessário que o programador defina quando e como cada thread poderá acessar.

    Para que o código funcione corretamente, é necessário que algumas variáveis sejam definidas 
    globalmente:

        * vetor que conterá os números primos (principal estrutura de dados compartilhada)
        * variável que define qual número será calculado (incrementada com passo = 2 para evitar testes com pares)
        * índice que irá ser incrementado a cada novo número primo calculado
        * número de threads a serem disparadas
        * tempo de execução total que define quanto tempo o código poderá permanecer em execução
        * variável que define o tamanho do vetor
        * uma variável pthread_mutex_t que define qual thread terá accesso à região crítica
    
    O método número um tem o seguintes objetivos:
        - implementa o loop que deve ser executado até que o tempo máximo seja atingido
        - permite a uma thread por vez incrementar a variável que define o número a ser testado
        - para cada número chame o teste
    
    O método número dois tem os seguintes objetivos:
        - testa se um dado número é ou não primo
        - caso ele seja primo, permita que apenas uma thread acesse o vetor e adiciona ao 
        vetor o número testado como positivo, incrementa o indice do vetor
        - destrava o vetor para que outra thread possa alterar seu conteúdo

    O terceiro método é executado no final e seu objetivo é o seguinte:
        - imprime cada casa desse vetor

    Lidando com a biblioteca time.h:
        * Crie um variável "tempo" do tipo clock_t
        * utilize o método clock() para capturar o tempo corrente
        * Utilize a constante CLOCKS_PER_SEC para ter acesso ao número de clocks por segundo



*/

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
