#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

void print_mem()
{
    const char alloc_c = 'X';
    const char free_c = 'O';
    char c[9] = {'\0'};

    for(int i = 0; i < TOTAL_MEMORY; i+=8)
    {
        for(int j = 0; j < 8; j++)
        {
            if(mem_est_alloue(i))
            {
                c[j] = alloc_c;
            }
            else
            {
                c[j] = free_c;
            }
        }
        
        printf("0x%02x  %s\n", i, c);
    }
}

int main(int argc, char* argv[])
{
    initmem();
    first_fit_alloumem(4);
    print_mem();
    return 0;
}
