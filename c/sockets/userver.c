/* userver.c - Einfacher Server für Unix-Domain-Sockets */

/* Wartet auf eine Verbindung am ./sample-socket Unix Domain Socket.
   Ist die Verbindung hergestellt, werden alle Daten von diesem
   Socket nach stdout kopiert, bis die Verbindung vom anderen Ende
   geschlossen wird. Dann warten auf neue Verbindung. */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "sockutil.h"

#define MY_SOCK_ADDRESS "./sample-socket"

int main(void) {
    struct sockaddr_un address;
    int sock, conn;
    size_t addrLength;

    if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
	die("socket");
    }

    /* Bereits vorhandene(n) Socket/Datei entfernen */
    unlink(MY_SOCK_ADDRESS);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, MY_SOCK_ADDRESS);

    /* Länge der Adresse inklusive der Größe des sun_family-Elements */
    addrLength = sizeof(address.sun_family) + strlen(address.sun_path);

    if (bind(sock, (struct sockaddr *) &address, addrLength)) {
	die("bind");
    }

    if (listen(sock, 5)) {
	die("listen");
    }

    while ((conn = accept(sock, (struct sockaddr *) &address, 
			  &addrLength)) >= 0) {
	printf("---- Hole Daten\n");
	copyData(conn, 1);
	printf("---- Fertig\n");
	close(conn);
    }

    if (conn < 0) {
	die("accept");
    }

    close(sock);
    return 0;
}
