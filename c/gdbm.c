#include <stdio.h>
#include <gdbm.h>

int foo(unsigned int i) 
{
    if (i < 0) 
	return -1;
    else 
	return +1;
}

int main(void)
{
    GDBM_FILE dbf;
    datum key = { "testkey", 7 };
    datum value = { "testvalue", 9 };

    printf("Storing key-value pair ...");
    dbf = gdbm_open( "test", 0, GDBM_NEWDB, 0644, 0 );
    gdbm_store( dbf, key, value, GDBM_INSERT );
    gdbm_close( dbf );
    printf(" done.\n");
 
    return foo(-3);
}
