#ifndef UNITTEST
#define UNITTEST
#include <stdio.h>
#define ut_equals(A,B) if ((A) != (B)) { ut_errorcount++; printf("X"); } else printf(".");
#define ut_testfunction(A) ut_errorcount = 0; printf(#A " "); (A)(); printf(" %d\n", ut_errorcount);
static int ut_errorcount;
#endif

