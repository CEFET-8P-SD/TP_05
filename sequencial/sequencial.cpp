#include <cstdlib>
#include <iostream>

void isPrimo(int num) {
    printf("num primo: %d\n", num);
    int isPrimo = 1;

    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            isPrimo = 0;
            break;
        }
    }
    printf(isPrimo ? "primo" : "não primo");
    printf("\n");
}

int main(int argc, char** argv) {
    for (int i = i; i < 6; i++) {
        isPrimo(i + 1);
    }
}

