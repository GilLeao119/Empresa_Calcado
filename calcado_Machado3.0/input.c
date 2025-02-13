#include <stdio.h>
#include <string.h>

#define VALOR_INVALIDO "O valor inserido é inválido."

/**
 * Esta função permite detetar um "enter"
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
/**
 * Esta função serve para pedirmos um valor inteiro ao cliente
 * @param minValor o primeiro argumento da função
 * @param maxValor o segundo argumento da função
 * @param msg o terceiro argumento da função
 * @return o valor inteiro
 */
int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}
/**
 * Esta função serve para pedirmos um valor float ao cliente
 * @param minValor o primeiro argumento da função
 * @param maxValor o segundo argumento da função
 * @param msg o terceiro argumento da função
 * @return o valor pedido
 */
float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}
/**
 * Esta função serve para pedirmos um valor double ao cliente
 * @param minValor o primeiro argumento da função
 * @param maxValor o segundo argumento da função
 * @param msg o terceiro argumento da função
 * @return o valor pedido
 */
double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}
/**
 * Esta função permite oter o caracter pedido ao cliente
 * @param msg o primeiro argumento da função
 * @return o caracter pedido
 */
char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}
/**
 * Esta função permite ler a string
 * @param string o primeiro argumento da função
 * @param tamanho o segundo argumento da função
 * @param msg o terceiro argumento da função
 */
void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}