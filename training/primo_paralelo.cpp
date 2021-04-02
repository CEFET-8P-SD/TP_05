#include <iostream>

void imprime_primos(int* vetor_primos, int numero_maximo)
{
    
    for (int i = 0; i < numero_maximo; i++)
    {
        printf("%d     ", vetor_primos[i]);
    }
}

int main(int argc, char const *argv[])
{

    //Vetor de Primos
    int numero_maximo = 500;
    int* vetor_primos = (int*) malloc(sizeof(int*) * numero_maximo);

    for (int i = 0; i < numero_maximo; i++)
    {
        vetor_primos[i] = i+1;
    }

    imprime_primos(vetor_primos, numero_maximo);


    return 0;
}
