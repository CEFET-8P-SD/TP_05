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

#include <time.h>
#include <iostream>

// tempo de execução em segundos
float tempo_de_execucao = 5.0;

void _run()
{

    clock_t tempo_de_inicio = clock();

    while ((clock() - tempo_de_inicio)/CLOCKS_PER_SEC <= tempo_de_execucao)
    {
        printf("r");
    }
        
    

}

int main(int argc, char const *argv[])
{
    
    _run();
    
    return 0;
}
