/* tserver.c - einfacher Server für TCP/IP-Sockets */

/* Wartet auf eine Verbindung auf konfiguriertem Port. Ist die Verbindung 
   hergestellt, werden alle Daten von dem Socket in die Standardausgabe
   kopiert, bis die Gegenseite die Verbindung schließt.
   Anschließend wird auf eine neue Verbindung gewartet. */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockutil.h"

int main(int argc, char ** argv) {
    struct sockaddr_in address;
    int sock, conn, i, port;
    size_t addrLength;
    char * line = (char *) malloc(1024);

    if (argc != 2) {
	printf("%s <Port-Nummer>\n", argv[0]);
	return 1;
    }

    port = atoi(argv[1]);

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
	die("socket");
    }

    /* Den Kernel die Socket-Adresse wiederbenutzen lassen. Erlaubt
       mehrmalige Durchläufe ohne auf das Timeout von (ip, port) 
       warten zu müssen. */
    i = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    memset(&address.sin_addr, 0, sizeof(address.sin_addr));

    if (bind(sock, (struct sockaddr *) &address, sizeof(address))) {
	die("bind");
    }
    
    if (listen(sock, 5)) {
	die("listen");
    }

    while ((conn = accept(sock, (struct sockaddr *) &address, 
			  &addrLength)) >= 0 ) {
	printf("--- Hole Daten\n");
	do {
	    readln(conn, line);
	    printf("%s", line);
	} while (!contains_space_only(line));
//	copyData(conn, STDOUT_FILENO);
	printf("--- Fertig\n");
	close(conn);
    }

    if (conn < 0) {
	die("accept");
    }

    close(sock);
    return 0;
}

int contains_space_only(char * str) {
    while (*str) {
	if (!isspace(*str)) {
	    return 0;
	}
	
	str++;
    }

    return 1;
}
