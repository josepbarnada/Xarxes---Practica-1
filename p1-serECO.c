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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "p1-util.h"

/* Definició de constants, p.e.,                                          */

/* #define XYZ       1500                                                 */

#define true 1
#define false 0

#define IP_serv "192.168.1.36"

#define IP_LENGTH 16

int running = true;
int socket_server = 0;
int socket_client = 0;

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

// TODO: Check running before each call to show error

void tancarServidor(int dummy) {
  printf("Tancant sockets...\n");

  running = false;
  if (socket_server > 0) {
    TCP_TancaSock(socket_server);
  }
  if (socket_client > 0) {
    TCP_TancaSock(socket_client);
  }

  printf("Sockets tancats\n");
}

void ms2() {
  char ip_serv[IP_LENGTH], ip_client[IP_LENGTH];
  int port_serv, port_client;

  TCP_TrobaAdrSockLoc(socket_server, ip_serv, &port_serv);
  TCP_TrobaAdrSockLoc(socket_client, ip_client, &port_client);

  printf("\n========= Millor Senzilla 2 ==========\n");
  mostrarSocket("Socket server", ip_serv, port_serv);
  mostrarSocket("Socket client", ip_client, port_client);
  printf("\n======================================\n");
}

int main(int argc, char *argv[]) {
  char *linea;

  signal(SIGINT, tancarServidor);

  printf("Entra el port del servidor: ");
  int port_server = 8000;
  // scanf("%d", &port_server);
  printf("\nIniciant el servidor amb port: %d\n", port_server);

  socket_server = TCP_CreaSockServidor(IP_serv, port_server);
  if (running && socket_server == -1) {
    mostrarError("Error creant socket");
    TCP_TancaSock(socket_server);
    exit(-1);
  }
  printf("Servidor iniciat correctament\n");

  while (running) {
    printf("\nEsperant connexio...\n");
    char IP_client[IP_LENGTH];
    int port_client;
    socket_client = TCP_AcceptaConnexio(socket_server, IP_client, &port_client);

    if (running && socket_client == -1) {
      mostrarError("Error acceptant connexio");
      TCP_TancaSock(socket_client);
      continue;
    }

    printf("Connexio acceptada:\n");
    mostrarSocket("Server (socket local)", IP_serv, port_server);
    mostrarSocket("Client (socket remot)", IP_client, port_client);

    // Funcio per fer la millor senzilla 2 decomentar en cas que es vulgui mirar
    // el contingut dels 2 sockets del servidor.
    //
    // ms2();

    int bytes_llegits;
    do {
      printf("\nEsperant missatge del client...\n");

      int mida_linea;
      bytes_llegits = rebreLinea(socket_client, &linea, &mida_linea);

      if (running && bytes_llegits == -1) {
        mostrarError("Error llegit missatge del socket client");

      } else if (bytes_llegits > 0) {
        printf("Missatge rebut (%d bytes):\n'%s'\n", bytes_llegits, linea);

        int bytes_enviats = enviarLinea(socket_client, linea, mida_linea);

        if (running && bytes_enviats == -1) {
          mostrarError("Error enviant missatge al socket client");
        }
      } else {
        printf("El client ha tencat la connexio...\n");
      }
    } while (bytes_llegits > 0);
  }

  free(linea);

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
