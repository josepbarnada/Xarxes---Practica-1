/**************************************************************************/
/*                                                                        */
/* L'aplicació ECO amb sockets TCP/IP                                     */
/* Fitxer cliECO.c que implementa el client ECO sobre la capa de          */
/* transport TCP (fent crides a la "nova" interfície de la capa de        */
/* transport o "nova" interfície de sockets).                             */
/*                                                                        */
/* Autors:                                                                */
/* Data:                                                                  */
/*                                                                        */
/**************************************************************************/

/* Inclusió de llibreries, p.e. #include <stdio.h> o #include "meu.h"     */

#include "p1-tTCP.h"

/* Definició de constants, p.e.,                                          */
char IPloc[] = "192.168.1.32"; // nose si esta be.. pero es la idea maomeno
int portTCPloc = 8000;
/* #define XYZ       1500                                                 */

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int main(int argc, char *argv[]) {
  /* Declaració de variables, p.e., int n;                                 */

  int codi_error;
  char *missatge_error;
  int socket_client;

  char *IP_server;
  int port_server;

  /* Expressions, estructures de control, crides a funcions, etc.          */

  socket_client = TCP_CreaSockClient(IPloc, portTCPloc);
  if (socket_client == -1) {
    TCP_TancaSock(socket_client);
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error creant socket client:\n%s", missatge_error);
    exit(-1);
  }

  if ((TCP_DemanaConnexio(socket_client, IP_server, &port_server)) == -1) {
    TCP_TancaSock(socket_client);
    missatge_error = T_ObteTextRes(&codi_error);
    printf("Error demanant connexió server:\n%s", missatge_error);
    exit(-1);
  };

  printf("tot funciona be");
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
