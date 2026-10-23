#ifndef UTIL_H
#define UTIL_H

#define PECO_LINEA 'L'

// Sets all the str to \0 a.k.a. null characters
void zero(char *str, int size);
void mostrarSocket(char *nom, char *ip, int port);
void mostrarError(char *msg);

void formatToPeco(char *info, int infoSize, char tipus, char *msg,
                  int *msgSize);

void getPecoInfo(char *msg, int *msgSize, char *info, int infoSize);

#endif
