#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


#include "include/mapmem.h"

#define PO_KNN_DADOS                        (0x080034d0)
#define PO_KNN_ATRIBUTO_N                   (0x08003490)
#define PO_KNN_DADOS_PRONTO                 (0x080034c0)
#define PO_KNN_CLASSE_PREVISTA              (0x080034b0)
#define PO_KNN_CLASSE_PREVISTA_PRONTO       (0x080034a0)
#define PO_KNN_TREINAMENTO                  (0x08003480)
#define PO_KNN_RESET                        (0x08003470)
#define PO_KNN_K                            (0x080034e0)
#define PO_KNN_CLASSE_PREVISTA_DISTANCIA    (0x080034f0)

#define ARQUIVO "iris_teste.txt"


#define TOTAL_HARDWARE_TREINAMENTO      6   // TAMANHO DO REGISTRO DE TREINAMENTO DO HARDWARE.
#define TOTAL_HARDWARE_ATRIBUTOS        6   // TOTAL DE ATRIBUTOS MAXIMOS PERMITIDOS NO HARDWARE.
typedef enum {
    RANDOMICO               = 1,
    SEQUENCIALBALANCEADO    = 2,
    RANDOMICOEXCLUSIVO      = 3
} algoritmoselecao_e ;

typedef struct {
    u_int16_t   po_knn_classe_prevista_classe;
    u_int16_t   po_knn_classe_prevista_distancia;
    int         int_classe_real;
    double      dbl_tempo_ms;
} distancia_t;


typedef struct {
    u_int16_t   classe;
    int         total;
} proximos_t;


typedef struct {
    int         int_classe_predita;
    int         int_classe_real;
    double      dlb_tempo_predicao_hardware;
    double      dbl_tempo_predicao_software;
    int         int_registrotreinamento;        //Na predicao este registro estava nos dados de treinamento.?? Se sim o correto e expurga-lo das estatiticas.
} predicao_t;

int             *p_int_atributo = 0;
int             **pp_int_dados_teste = 0;
int             **pp_int_dados_treinamento = 0;

distancia_t     *p_reg_distancia;
predicao_t      *p_reg_predicao;


//distancia_t *p_reg_distancia_ordenada;

int f_total_linhas_arquivo (char *);
void f_carregar_arquivo_memoria (char *, int *);
void f_selecionar_dados_treinamento(algoritmoselecao_e, int , int );
void f_ordenar_execucao_parcial(distancia_t *, int);
void f_obter_k_proximos(int *, distancia_t *, int, int);
