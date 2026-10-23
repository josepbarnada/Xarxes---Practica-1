#include "p1-util.h"
#include <stdio.h>

void mostrarError(char *msg) {
  int codi_error;
  char *missatge_error = T_ObteTextRes(&codi_error);
  printf("\n%s\nCodi errno: %d\n%s\n", msg, codi_error, missatge_error);
}

void zero(char *str, int size) {
  for (int i = 0; i < size; i++) {
    str[i] = '\0';
  }
}

void mostrarSocket(char *nom, char *ip, int port) {
  printf("\n%s:\n\tIP:\t%s\n\tPort:\t%d\n", nom, ip, port);
}
