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

#define IP_serv "0.0.0.0"
#define IP_LENGTH 16

/* Variables globals                                                      */
int running = true;
int socket_server = 0;
int socket_client = 0;

/* Declaració de funcions INTERNES que es fan servir en aquest fitxer     */
/* (les  definicions d'aquestes funcions es troben més avall) per així    */
/* fer-les conegudes des d'aquí fins al final d'aquest fitxer, p.e.,      */

/* int FuncioInterna(arg1, arg2...);                                      */

void tancarServidor(int dummy);
void ms1();

int main(int argc, char *argv[]) {
  /* Declaració de variables, p.e., int n;                                 */

  char *linea = NULL;
  int port_server;
  char IP_client[IP_LENGTH];
  int port_client;
  int bytes_llegits;
  int mida_linea;
  int bytes_enviats;

  /* Expressions, estructures de control, crides a funcions, etc.          */

  signal(SIGINT, tancarServidor);

  printf("Entra el port del servidor: ");
  port_server = 8000;
  scanf("%d", &port_server);
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
    socket_client = TCP_AcceptaConnexio(socket_server, IP_client, &port_client);
    if (!running)
      continue;

    if (socket_client == -1) {
      mostrarError("Error acceptant connexio");
      TCP_TancaSock(socket_client);
      continue;
    }

    printf("Connexio acceptada:\n");
    mostrarSocket("Server (socket local)", IP_serv, port_server);
    mostrarSocket("Client (socket remot)", IP_client, port_client);

    // Funcio per fer la millor senzilla 1 descomentar en cas que es vulgui
    // mirar el contingut dels 2 sockets del servidor.

    ms1();

    do {
      printf("\nEsperant missatge del client...\n");

      bytes_llegits = rebreLinea(socket_client, &linea, &mida_linea);
      if (!running)
        continue;

      if (bytes_llegits == -1) {
        mostrarError("Error llegit missatge del socket client");

      } else if (bytes_llegits > 0) {
        printf("Missatge rebut (%d bytes):\n'%s'\n", bytes_llegits, linea);

        bytes_enviats = enviarLinea(socket_client, linea, mida_linea);
        if (!running)
          continue;

        if (bytes_enviats == -1) {
          mostrarError("Error enviant missatge al socket client");
        }
      } else {
        printf("El client ha tencat la connexio...\n");
      }
    } while (running && bytes_llegits > 0);
  }

  if (linea != NULL) {
    free(linea);
  }
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */

// Funcio que tenca els sockets del servidor, aquesta funcio nomes s'hauria de
// cridar mitjançant el signal interrupt
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

// Funcio per mostrar per pantalla els sockets per realitzar la millora senzilla
// 1
//
// Mostra els sockets locals que té el servidor
void ms1() {
  char ip_serv[IP_LENGTH], ip_client[IP_LENGTH];
  int port_serv, port_client;

  TCP_TrobaAdrSockLoc(socket_server, ip_serv, &port_serv);
  TCP_TrobaAdrSockLoc(socket_client, ip_client, &port_client);

  printf("\n========= Millor Senzilla 1 ==========\n");
  mostrarSocket("Socket server", ip_serv, port_serv);
  mostrarSocket("Socket client", ip_client, port_client);
  printf("\n======================================\n");
}
