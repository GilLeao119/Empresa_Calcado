#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logs.h"

/**
 * Esta função guarda num ficheiro txt o histórico das ações no programa
 * @param msg o primeiro argumento da função
 * @param filename o segundo argumento da função
 */
void logMsg(char *msg, char *filename) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", tm->tm_year + 1900, 
            tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);

    fclose(fp);
}