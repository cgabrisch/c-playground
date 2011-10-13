/* sockutil.c - Einfache Hilfsfunktionen */

#include <stdio.h>
#include <unistd.h>

#include "sockutil.h"

/* Fehlermeldung mit perror() ausgeben und beenden */
void die(char * message) {
    perror(message);
    exit(1);
}

/* Kopiert Daten vom Dateideskriptor 'from' zum Dateideskriptor 'to',
   bis nichts mehr zu kopieren ist. Beendet sich im Fehlerfall. */
void copyData(int from, int to) {
    char buf[1024];
    int amount;

    while ((amount = read(from, buf, sizeof(buf))) > 0) {
	if (write(to, buf, amount) != amount) {
	    die("write");
	    return;
	}
    }

    if (amount < 0) {
	die("read");
    }
}

/* Liest eine Zeile vom Dateideskriptor 'fd' */
int readln(int fd, char * str) {
    char buf[1], buf2[1024];
    int amount = 0;

    while (read(fd, buf, sizeof(buf)) > 0) {
	buf2[amount++] = buf[0];
	if (amount > 1023) {
	    die("read line too long");
	}

	if (buf[0] == '\n') {
	    buf2[amount++] = '\0';
	    break;
	}
    }

    strncpy(str, buf2, amount);

    return amount;
}
