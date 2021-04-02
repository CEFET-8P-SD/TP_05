#include <iostream>


int teste_primo(int numero){
    int counter = 0;

    for (int i = 1; i < numero/2; i++)
    {
        
        if (numero % i > 0)
        {
            counter++;
        }

    }
    
    if (counter>0)
    {
        return 0;
    }
    

    return 1;
}

int main(int argc, char const *argv[])
{

    for (int i = 0; i < 60; i++)
    {
        
        printf("Número: %d ---", i);
        printf("Resultado do teste: %d.", teste_primo(i));

    }
    

    return 0;
}
