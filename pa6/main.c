#include "mymalloc.h"
#include <stdio.h>

int main()
{
        printf("Malloc test1 with 2000\n");
        void *test1 = malloc(2000);
        printf("test1 2000 '%p'\n", test1);
        printf("Malloc test2 for 10000\n");
        void *test2 = malloc(10000);
        printf("test2 10000 '%p'\n", test2);
        printf("Freeing test2\n");
        free(test2);

        printf("Malloc test3 with 4000\n");
        void *test3 = malloc(4000);
        printf("test3 with 6000 '%p'\n", test3);
        printf("Malloc test4 with 18000\n");
        void *test4 = malloc(18000);
        printf("test4 with 18000 '%p'\n", test4);

        printf("Freeing test1\n");
        free(test1);
        printf("Freeing test2\n");
        free(test2);
        printf("Freeing test3\n");
        free(test3);
        printf("Freeing test2\n");
        free(test2);
        printf("Freeing test4\n");
        free(test4);
        printf("Freeing test1\n");
        free(test1);
        
    return 0;
}
