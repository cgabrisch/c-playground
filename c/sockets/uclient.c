/* uclient.c - Einfacher Client für Unix-Domain-Sockets */

/* Verbindet sich mit dem ./sample-socket Unix Domain Socket,
   kopiert stdin in den Socket und beendet sich dann. */

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "sockutil.h"

int main(void) {
    struct sockaddr_un address;
    int sock;
    size_t addrLength;

    if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
	die("socket");
    }

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "./sample-socket");

    addrLength = sizeof(address.sun_family) + strlen(address.sun_path);

    if (connect(sock, (struct sockaddr *) &address, addrLength)) {
	die("connect");
    }

    copyData(0, sock);

    close(sock);

    return 0;
}
