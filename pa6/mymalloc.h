#ifndef _mymalloc_h_
#define _mymalloc_h_

#include <stdlib.h>
#include <stdio.h>

#define malloc( x ) mymalloc( x , __FILE__ , __LINE__ )
#define free( x ) myfree( x , __FILE__ , __LINE__ )

void *mymalloc(unsigned int range, char *file, int line);
void myfree(void *b, char *file, int line);

#endif
