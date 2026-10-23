#ifndef UTIL_H
#define UTIL_H

#include "p1-tTCP.h"

#define PECO_LINEA 'L'

// Sets all the str to \0 a.k.a. null characters
void zero(char *str, int size);
void mostrarSocket(char *nom, char *ip, int port);
void mostrarError(char *msg);

int rebreLinea(int socket, char **msg);
int enviarLinea(int socket, char *msg, int msgSize);
void formatToPeco(char *info, int infoSize, char tipus, char *paquet[],
                  int *paquetSize);

void getPecoInfo(char *paquet, int paquetSize, char *info[], int *infoSize);

#endif
