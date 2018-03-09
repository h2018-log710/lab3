#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

int main(int argc, char* argv[])
{
    initmem();
    alloumem(sizeof(int));
    return 0;
}
