#include "p1-util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrarError(char *msg) {
  int codi_error;
  char *missatge_error = T_ObteTextRes(&codi_error);
  printf("\n%s\nCodi errno: %d\n%s\n", msg, codi_error, missatge_error);
}

void zero(char *str, int size) {
  int i;
  for (i = 0; i < size; i++) {
    str[i] = '\0';
  }
}

void mostrarSocket(char *nom, char *ip, int port) {
  printf("\n%s:\n\tIP:\t%s\n\tPort:\t%d\n", nom, ip, port);
}

int enviarLinea(int socket, char *msg, int msgSize) {
  int paquetSize;
  char *paquet;

  formatToPeco(msg, msgSize, PECO_LINEA, &paquet, &paquetSize);

  int bytes_enviats = TCP_Envia(socket, paquet, paquetSize);

  free(paquet);

  return bytes_enviats;
}

int rebreLinea(int socket, char **msg, int *msgSize) {

  char buffer[200] = {0};

  int bytes_rebuts = TCP_Rep(socket, buffer, 200);

  if (bytes_rebuts > 0) {

    getPecoInfo(buffer, bytes_rebuts, msg, msgSize);
  }

  return bytes_rebuts;
}

void formatToPeco(char *info, int infoSize, char tipus, char *paquet[],
                  int *paquetSize) {

  // 1 bytes el de el tipus
  *paquetSize = infoSize + 1;

  char *msg = (char *)malloc(*paquetSize);

  msg[0] = tipus;

  strncpy(msg + 1, info, infoSize);

  *paquet = msg;
}

void getPecoInfo(char *paquet, int paquetSize, char *info[], int *infoSize) {
  // treiem el byte del tipus de paquet
  *infoSize = paquetSize - 1;

  char *msg = (char *)malloc(*infoSize);

  strncpy(msg, paquet + 1, *infoSize);

  *info = msg;
}
