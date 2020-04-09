#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


#include "include/mapmem.h"

#define PO_KNN_DADOS            (0x080034d0)
#define PO_KNN_DADOS_PRONTO     (0x080034c0)
#define PO_KNN_CLASSE_PREVISTA  (0x080034b0)


int main(int argc, char *argv[])
{
    struct timeval start, stop;


    int a;
    void *po_knn_classe_prevista_p;
    u_int16_t po_knn_classe_prevista_valor;
    double delta_ms;

    //volatile int16_t *addr = (int16_t *) 0x080034d0;
    //volatile bool *y = (bool*) 0x080034c0;

    po_knn_classe_prevista_p = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA, LEITURA);
    printf ("Endereco mapeado %p\n", po_knn_classe_prevista_p);

    printf ("Teste de velocidade de acesso a porta paralela NIOS2 \n");
    printf ("1.000.000 iteracoes \n");

    gettimeofday(&start, NULL);
    for (a=1; a < 1000000; a++) {

        po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;

    }
    gettimeofday(&stop, NULL);
    delta_ms = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("%5.5f Segundos\n", (float) delta_ms);

    printf ("10.000.000 iteracoes \n");

    gettimeofday(&start, NULL);
    for (a=1; a < 10000000; a++) {

        po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;

    }
    gettimeofday(&stop, NULL);
    delta_ms = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("%5.5f Segundos\n", (float) delta_ms);

    printf ("100.000.000 iteracoes \n");

    gettimeofday(&start, NULL);
    for (a=1; a < 100000000; a++) {

        po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;

    }
    gettimeofday(&stop, NULL);
    delta_ms = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("%5.5f Segundos\n", (float) delta_ms);

    printf ("valor %d\n", po_knn_classe_prevista_valor);

//#ifdef NIOS2
//        *y = 0x0;
        //*x = 0x00AA;
        //*y = 0x1;

    //PO_KNN_DADOS_PRONTO = 0;
   // PO_KNN_DADOS = 255;
   // PO_KNN_DADOS_PRONTO = 1;
//#endif // NIO2



    printf("FIM");

    return 0;
}
