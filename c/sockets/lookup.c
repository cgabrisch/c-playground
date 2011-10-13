/* lookup.c - Ausgabe grundlegender Informationen eines Internetrechners */

/* Bei gegebenem Rechnernamen oder gegebener IP-Adresse auf der Kommandozeile
   den kanonischen Rechnernamen dieses Rechners und alle seine IP-Nummern
   ausgeben */

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    struct hostent * answer;
    struct in_addr address, ** addrptr;
    char ** next;

    if (argc != 2) {
	fprintf(stderr, "Nur ein Argument erlaubt.\n");
	return 1;
    }

    /* Als IP-Nummer annehmen, wenn Argument so aussieht. */
    if (inet_aton(argv[1], &address)) {
	answer = gethostbyaddr((char *) &address, sizeof(address), AF_INET);
    } else {
	answer = gethostbyname(argv[1]);
    }

    if (!answer) {
	herror("Fehler beim Suchen des Rechners");
	return 1;
    }

    printf("Kanonischer Rechnername: %s.\n", answer->h_name);

    if (answer->h_aliases[0]) {
	printf("Aliase:");
	for (next = answer->h_aliases; *next; next++) {
	    printf(" %s", *next);
	}
	printf("\n");
    }

    printf("Adressen:");
    for (addrptr = (struct in_addr **) answer->h_addr_list;
	 *addrptr; addrptr++) {
	printf(" %s", inet_ntoa(**addrptr));
    }
    printf("\n");

    return 0;
}
