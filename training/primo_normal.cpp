#include <iostream>


int teste_primo(int numero){
    int counter = 0;

    for (int i = 2; i < numero/2+1; i++)
    {
        
        if (numero % i == 0)
        {
            return 0;
        }

    }

    return 1;
}

int main(int argc, char const *argv[])
{

    for (int i = 3; i <= 60; i++)
    {

        int test = teste_primo(i);

        printf("Número: %d ---", i);

        if (test == 0)
        {
            printf("Resultado do teste: Não Primo.\n");
        }else{
            printf("Resultado do teste: Primo.\n");
        }
        
        

    }
    

    return 0;
}
