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

#define IP "192.168.1.36"
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

  server_socket = TCP_CreaSockServidor(IP, PORT);
  if (server_socket == -1) {
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error creant socket:\n%s", missatge_error);
    TCP_TancaSock(server_socket);
    exit(-1);
  }

  int socket_client;

  if ((socket_client =
           TCP_AcceptaConnexio(server_socket, IP_client, &port_client)) == -1) {
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error acceptant socket client:\n%s", missatge_error);
    TCP_TancaSock(server_socket);
    exit(-1);
  };

  int msgSize = 200;
  char msg[msgSize];

  printf("Esperant rebre...\n");
  llegit = TCP_Rep(socket_client, msg, msgSize);
  printf("Rebut: '%s' %d bytes\n", msg, llegit);

  if (llegit == -1) {
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error llegint missatge: \n%s", missatge_error);
    TCP_TancaSock(server_socket);
    exit(-1);
  }

  printf("Enviant: '%s' %d bytes\n", msg, llegit);
  if ((TCP_Envia(socket_client, msg, llegit) == -1)) {
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error enviant missatge: \n%s", missatge_error);
    TCP_TancaSock(server_socket);
    exit(-1);
  }

  printf("Tancant sockets...\n");
  TCP_TancaSock(socket_client);
  TCP_TancaSock(server_socket);
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
