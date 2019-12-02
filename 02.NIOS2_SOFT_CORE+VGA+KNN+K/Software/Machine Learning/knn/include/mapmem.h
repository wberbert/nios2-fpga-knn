#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

typedef enum {
    LEITURA = (O_RDONLY | O_SYNC),
    ESCRITA = (O_RDWR | O_SYNC)
} mapear_memoria_modo_t;

void *f_Mapear_Memoria(unsigned long int, mapear_memoria_modo_t);
