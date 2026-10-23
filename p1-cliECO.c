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

  while(continuar){
    
    int codi_error;
    char *missatge_error;
    int socket_client;
    
    printf("Entra la IP del servidor: ");
    char IP_server[IP_LONG] = "192.168.1.36";
    // scanf("%s", IP_server);
    
    printf("Entra el port del servidor: ");
    int port_server = 8000;
  // scanf("%d", &port_server);
  
  printf("Iniciant connexio al servidor %s amb port: %d\n", IP_server,
        port_server);
        
         /* Expressions, estructures de control, crides a funcions, etc.          */
        
        socket_client = TCP_CreaSockClient(IPloc, portTCPloc);
        if (socket_client == -1) {
          missatge_error = T_ObteTextRes(&codi_error);
          printf("Error creant socket client:\n%s", missatge_error);
          TCP_TancaSock(socket_client);
          exit(-1);
          }
          
          if ((TCP_DemanaConnexio(socket_client, IP_server, port_server)) == -1) {
            TCP_TancaSock(socket_client);
            missatge_error = T_ObteTextRes(&codi_error);
            printf("Error demanant connexió server:\n%s", missatge_error);
            exit(-1);
          };

          printf("\nClient (socket local):\n\tIP:\t%s\n\tPort:\t%d\n", IPloc, portTCPloc);
          printf("\nServer (socket remot):\n\tIP:\t%s\n\tPort:\t%d\n", IP_server, port_server);
          
          // int socket_server;
          // char *ipServer;
          // int portServ;
          
          // TCP_TrobaAdrSockRem(socket_server, ipServer, &portServ);
          
          int bufferSize = 200;
          char buffer[bufferSize];
          int llegit = read(STDIN_FILENO, buffer, bufferSize);
          
          for (int i = llegit - 1; i < bufferSize; i++) {
            buffer[i] = '\0';
          }
          
          while (llegit > 0 && strcmp(buffer, "EOF") != 0) {
            
            printf("Per Enviar: '%s' %d bytes\n", buffer, llegit);
            int enviat;
            if ((enviat = TCP_Envia(socket_client, buffer, llegit)) == -1) {
              missatge_error = T_ObteTextRes(&codi_error);
              printf("Error enviant missatge: \n%s", missatge_error);
              TCP_TancaSock(socket_client);
              exit(-1);
            }
            printf("Enviat: '%s' %d bytes\n", buffer, enviat);
            
            printf("ESPERANT... rebre\n");

            int llegits;
            if ((llegits = TCP_Rep(socket_client, buffer, bufferSize)) == -1) {
              missatge_error = T_ObteTextRes(&codi_error);
              printf("Error rebent missatge: \n%s", missatge_error);
              TCP_TancaSock(socket_client);
              exit(-1);
            } else if (llegits == 0) {
              printf("El servidor ha tancat la connexió");
              TCP_TancaSock(socket_client);
              break; //pq l'usuari es pugui connectar a un altre server si vol
            }
            printf("Rebut: '%s' %d bytes\n", buffer, llegits);
            
            llegit = read(STDIN_FILENO, buffer, bufferSize);
            
            for (int i = llegit - 1; i < bufferSize; i++) {
              buffer[i] = '\0';
            }
          }
  
  printf("Tancants sockets...\n");
  
  TCP_TancaSock(socket_client);
  // TCP_TancaSock(socket_server);

  printf("Vols enviar missatges a un altre servidor? [0: no |||| 1: si]: ");
  scanf("%d", continuar);

  }
}

/* Definició de funcions INTERNES, és a dir, d'aquelles que es faran      */
/* servir només en aquest mateix fitxer. Les seves declaracions es troben */
/* a l'inici d'aquest fitxer.                                             */

/* Descripció de la funció, dels arguments, valors de retorn, etc.        */
/*int FuncioInterna(arg1, arg2...)
{

} */
