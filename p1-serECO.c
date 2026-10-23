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

#define true 1
#define false 0

#define IP_serv "192.168.1.36"

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

void mostrarError(char *msg) {
  int codi_error;
  char *missatge_error = T_ObteTextRes(&codi_error);
  printf("%s\n%s\n", msg, missatge_error);
}

int main(int argc, char *argv[]) {

  printf("Entra el port del servidor: ");
  int port_server;
  scanf("%d", &port_server);
  printf("\nIniciant el servidor amb port: %d\n", port_server);

  int socket_server = TCP_CreaSockServidor(IP_serv, port_server);
  if (socket_server == -1) {
    mostrarError("Error creant socket");
    TCP_TancaSock(socket_server);
    exit(-1);
  }
  printf("Servidor iniciat correctament\n");

  while (true) {
    printf("\nEsperant connexio...\n");
    char IP_client[15];
    int port_client;
    int socket_client =
        TCP_AcceptaConnexio(socket_server, IP_client, &port_client);

    if (socket_client == -1) {
      mostrarError("Error acceptant connexio");
      TCP_TancaSock(socket_client);
      continue;
    }
    printf("Connexio acceptada:\n");
    printf("\nServer (socket local):\n\tIP:\t%s\n\tPort:\t%d\n", IP_serv,
           port_server);
    printf("\nClient (socket remot):\n\tIP:\t%s\n\tPort:\t%d\n", IP_client,
           port_client);

    // Aixo no es true pero no ser com es per comprovar que el socket client
    // tingui connectivitat
    int bytes_llegits;
    do {
      printf("\nEsperant missatge del client...\n");
      char buffer[200] = {0};
      bytes_llegits = TCP_Rep(socket_client, buffer, 200);

      if (bytes_llegits == -1) {
        mostrarError("Error llegit missatge del socket client");

      } else if (bytes_llegits > 0) {
        printf("Missatge rebut (%d bytes):\n%s\n", bytes_llegits, buffer);
        // printf("Missatge rebut:\n%s\nBytes: %d\n", buffer, bytes_llegits);

        int bytes_enviats = TCP_Envia(socket_client, buffer, bytes_llegits);

        if (bytes_enviats == -1) {
          mostrarError("Error enviant missatge al socket client");
        }
      } else {
        printf("El client ha tencat la connexio...\n");
      }
    } while (bytes_llegits > 0);
  }

  /* Declaració de variables, p.e., int n;                                 */
  /* Expressions, estructures de control, crides a funcions, etc.          */
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
