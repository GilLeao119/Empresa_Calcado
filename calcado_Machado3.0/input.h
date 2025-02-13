/**
 * @file machado.h
 * @author Gil Leão, Rui Ferreira, Pedro Nunes
 * @date 27 Dezembro 2021 
 *  
 */
#ifndef INPUT_H
#define INPUT_H

int obterInt(int minValor, int maxValor, char *msg);

float obterFloat(float minValor, float maxValor, char *msg);

double obterDouble(double minValor, double maxValor, char *msg);

char obterChar(char *msg);

void lerString(char *string, unsigned int tamanho, char *msg);

#endif /* INPUT_H */
