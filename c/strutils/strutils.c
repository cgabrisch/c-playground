#include <string.h>
#include "strutils.h"

int strindex(char s[], char t[]) 
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (t[k] == '\0')
			return i;
	}
	return -1;
}

int strrindex(char s[], char t[]) 
{
	size_t s_len, t_len;
	int i, j, k;

	s_len = strlen(s);	
	t_len = strlen(t);

	for (i = s_len - 1; i > 0; i--) {
		for (j = i, k = t_len - 1; j >= 0 && k >= 0 && s[j] == t[k]; j--, k--)
			;
		if (k == -1)
			return j+1;
	}

	return -1;
}

