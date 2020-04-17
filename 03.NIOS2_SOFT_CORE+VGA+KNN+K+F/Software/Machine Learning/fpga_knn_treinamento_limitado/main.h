#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


#include "include/mapmem.h"

#define PO_KNN_DADOS                    (0x080034d0)
#define PO_KNN_ATRIBUTO_N               (0x08003490)
#define PO_KNN_DADOS_PRONTO             (0x080034c0)
#define PO_KNN_CLASSE_PREVISTA          (0x080034b0)
#define PO_KNN_CLASSE_PREVISTA_PRONTO   (0x080034a0)
#define PO_KNN_TREINAMENTO              (0x08003480)
#define PO_KNN_RESET                    (0x08003470)
#define PO_KNN_K                        (0x080034e0)

#define ARQUIVO "iris_teste.txt"


#define TOTAL_HARDWARE_TREINAMENTO      6   // TAMANHO DO REGISTRO DE TREINAMENTO DO HARDWARE.
#define TOTAL_HARDWARE_ATRIBUTOS        6   // TOTAL DE ATRIBUTOS MAXIMOS PERMITIDOS NO HARDWARE.

int     *p_int_atributo = 0;
int     **pp_int_dados_teste = 0;
int     **pp_int_dados_treinamento = 0;

int f_total_linhas_arquivo (char *);
void f_carregar_arquivo_memoria (char *, int *);
void f_selecionar_dados_treinamento(int );
