#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

typedef enum {
    LEITURA = 1,
    ESCRITA = 2
} mapear_memoria_modo_t;

void *f_Mapear_Memoria(unsigned long int, mapear_memoria_modo_t);
