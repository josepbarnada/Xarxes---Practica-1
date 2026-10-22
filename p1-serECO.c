/**************************************************************************/
/*                                                                        */
/* L'aplicació ECO amb sockets TCP/IP                                     */
/* Fitxer serECO.c que implementa el servidor ECO sobre la capa de        */
/* transport TCP (fent crides a la "nova" interfície de la capa de        */
/* transport o "nova" interfície de sockets).                             */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "p1-tTCP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

#define IP "192.168.1.42"
#define PORT 8000

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int main(int argc, char *argv[]) {
  /* Declaració de variables, p.e., int n;                                 */
  int codi_error;
  char *missatge_error;

  int server_socket;

  char *IP_client;
  int port_client;

  int llegit;

  /* Expressions, estructures de control, crides a funcions, etc.          */

  server_socket = TCP_CreaSockClient(IP, PORT);
  if (server_socket == -1) {
    TCP_TancaSock(server_socket);
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error creant socket:\n%s", missatge_error);
    exit(-1);
  }

  if ((TCP_AcceptaConnexio(server_socket, IP_client, &port_client)) == -1) {
    TCP_TancaSock(server_socket);
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error acceptant socket client:\n%s", missatge_error);
    exit(-1);
  };

  int size = 0;
  char *message;

  int bufferSize = 200;
  char buffer[bufferSize];

  while ((llegit = TCP_Rep(server_socket, buffer, bufferSize)) > 0) {
    size += llegit;
    strcat(message, buffer);
  }

  if (llegit == -1) {
    TCP_TancaSock(server_socket);
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error llegint missatge: \n%s", missatge_error);
    exit(-1);
  }

  TCP_Envia(server_socket, message, size);
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
