#include "p1-util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mostra un missatge d'error incluint el errno i l'error que s'ha donat.
// El missatge té el següent estil:
//
// <msg>.
// Codi errno: <errno>
// <missatge error intern>
//
// Paràmetres:
// - char *msg: El missatge que es mostrara per pantalla
void mostrarError(char *msg) {
  int codi_error;
  char *missatge_error;

  missatge_error = T_ObteTextRes(&codi_error);
  printf("\n%s\nCodi errno: %d\n%s\n", msg, codi_error, missatge_error);
}

// Mostra per pantalla la informació de la connexió d'un socket
//
// Estil missatge:
// <nom>.
//    IP: <IP>.
//    Port: <Port>.
//
// Paràmetres:
// - char *nom: Nom informatiu sobre a que fa referència el socket.
// - char *ip: La ip del socket.
// - int port: El port del socket.
void mostrarSocket(char *nom, char *ip, int port) {
  printf("\n%s:\n\tIP:\t%s\n\tPort:\t%d\n", nom, ip, port);
}

// Envia una linea en el format PECO LIN al socket especificat.
//
// Paràmetres:
// - int socket: El socket al que s'ha d'enviar el missatge.
// - char *msg: El missatge a enviar.
// - int msgSize: La mida del missatge.
//
// Retorna el nombre de bytes enviats pel socket (que son els del missatge + 1).
// Retorna -1 s'hi hi ha error
int enviarLinea(int socket, char *msg, int msgSize) {
  int paquetSize;
  char *paquet;
  int bytes_enviats;

  formatToPeco(msg, msgSize, PECO_LINEA, &paquet, &paquetSize);

  bytes_enviats = TCP_Envia(socket, paquet, paquetSize);

  free(paquet);

  return bytes_enviats;
}

// Rep una linea en format PECO LIN del socket especificat.
//
// Paràmetres:
// - int socket: El socket que rep la linea.
//
// Paràmetres de retorn:
// - char **msg: On es guarda el missatge:
// - - Es reserva la memoria per guardar el
// missatge, s'hauria d'allibera un cop no es necessiti.
// - - El missatge esta en el format C string.
// - int *msgSize: La mida del missatge.
//
// Retorna el nombre de bytes rebuts al socket, que són diferents a la mida del
// missatge, ja que el missatge retornat no està en el format PECO LIN.
int rebreLinea(int socket, char **msg, int *msgSize) {

  char buffer[200] = {0};
  int bytes_rebuts;

  bytes_rebuts = TCP_Rep(socket, buffer, 200);

  if (bytes_rebuts > 0) {

    getPecoInfo(buffer, bytes_rebuts, msg, msgSize);
  }

  return bytes_rebuts;
}

// Converteix un missatge en un paquet PECO LIN.
//
// Paràmetres:
// - char *info: El missatge original.
// - int infoSize: La mida del missatge original.
// - char tipus: El tipus del paquet (de moment nomes L).
//
// Paràmetres de retorn:
// - char *paquet[]: String del paquet en format PECO LIN.
// - int *paquetSize: La mida del paquet
void formatToPeco(char *info, int infoSize, char tipus, char *paquet[],
                  int *paquetSize) {

  char *msg;

  // 1 bytes el de el tipus
  *paquetSize = infoSize + 1;

  msg = (char *)malloc(*paquetSize);

  msg[0] = tipus;

  strncpy(msg + 1, info, infoSize);

  *paquet = msg;
}

// Converteix un paquet PECO LIN en un missatge tipus C string.
//
// Paràmetres:
// - char *paquet: El paquet.
// - int paquetSize: La mida del paquet.
//
// Paràmetres de retorn:
// - char *info[]: El missatge en C string.
// - int *infoSize: La mida del missatge.
void getPecoInfo(char *paquet, int paquetSize, char *info[], int *infoSize) {
  char *msg;

  // treiem el byte del tipus de paquet
  *infoSize = paquetSize - 1;

  msg = (char *)malloc(*infoSize);

  strncpy(msg, paquet + 1, *infoSize);

  *info = msg;
}
