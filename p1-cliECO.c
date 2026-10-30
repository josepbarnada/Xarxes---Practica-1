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
#include "p1-util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Definició de constants, p.e.,                                          */
char IPloc[] = "0.0.0.0"; // nose si esta be.. pero es la idea maomeno
int portTCPloc = 0;
/* #define XYZ       1500                                                 */
#define IP_LONG 16
/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

int main(int argc, char *argv[]) {
  /* Declaració de variables, p.e., int n;                                 */
  int continuar = 1;
  char *linea;
  int codi_error;
  char *missatge_error;
  int socket_client;
  char IP_server[IP_LONG] = "192.168.1.36";
  int port_server = 8000;
  int bufferSize = 200;
  char buffer[bufferSize];
  int llegit;
  int enviat;
  int mida_linea;
  int llegits;

  /* Expressions, estructures de control, crides a funcions, etc.          */
  while (continuar) {

    printf("Entra la IP del servidor: ");
    scanf("%s", IP_server);

    printf("Entra el port del servidor: ");
    scanf("%d", &port_server);

    printf("Iniciant connexio al servidor %s amb port: %d\n", IP_server,
           port_server);

    socket_client = TCP_CreaSockClient(IPloc, portTCPloc);
    if (socket_client == -1) {
      mostrarError("Error creant socket client");
      TCP_TancaSock(socket_client);
      exit(-1);
    }

    if ((TCP_DemanaConnexio(socket_client, IP_server, port_server)) == -1) {
      TCP_TancaSock(socket_client);
      mostrarError("Error demanant connexió server");
      exit(-1);
    };

    printf("\nClient (socket local):\n\tIP:\t%s\n\tPort:\t%d\n", IPloc,
           portTCPloc);
    printf("\nServer (socket remot):\n\tIP:\t%s\n\tPort:\t%d\n", IP_server,
           port_server);

    llegit = read(STDIN_FILENO, buffer, bufferSize);

    buffer[llegit - 1] = '\0';

    while (llegit > 0 && strcmp(buffer, "EOF") != 0) {

      printf("Per Enviar: '%s' %d bytes\n", buffer, llegit);
      if ((enviat = enviarLinea(socket_client, buffer, llegit)) == -1) {
        mostrarError("Error enviant missatges");
        TCP_TancaSock(socket_client);
        exit(-1);
      }
      printf("Enviat: '%s' %d bytes\n", buffer, enviat);

      printf("ESPERANT... rebre\n");

      if ((llegits = rebreLinea(socket_client, &linea, &mida_linea)) == -1) {
        mostrarError("Error rebent missatges");
        TCP_TancaSock(socket_client);
        exit(-1);
      } else if (llegits == 0) {
        printf("El servidor ha tancat la connexió");
        TCP_TancaSock(socket_client);
        break; // pq l'usuari es pugui connectar a un altre server si vol
      }
      strncpy(buffer, linea, bufferSize);
      printf("Rebut: '%s' %d bytes\n", buffer, llegits);

      llegit = read(STDIN_FILENO, buffer, bufferSize);

      buffer[llegit - 1] = '\0';
    }

    printf("Tancants sockets...\n");

    TCP_TancaSock(socket_client);
    // TCP_TancaSock(socket_server);

    printf("Vols enviar missatges a un altre servidor? [0: no |||| 1: si]: ");
    scanf("%d", &continuar);
  }

  free(linea);
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
