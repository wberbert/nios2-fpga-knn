#include "main.h"
#define TOTAL_REGISTROS 150

int main(int argc, char *argv[])
{
    void *po_knn_classe_prevista_p;
    void *po_knn_dados_p;
    void *po_knn_dados_pronto_p;
    void *po_knn_treinamento;
    void *po_knn_atributo_n;
    void *po_knn_classe_prevista_pronto_p;
    void *po_knn_reset;
    void *po_knn_k;

    int  int_total_registros = 0;
    int  int_total_registros_corretos = 0;

    struct  timeval start, stop;
    double  delta_ms, g_delta_ms_total;

    int     int_loop;

    char    *chr_knn_k;


    int     arr_iris_data[150][5] = {
                                     {51, 35, 14, 2, 1},
                                     {49, 30, 14, 2, 1},
                                     {47, 32, 13, 2, 1},
                                     {46, 31, 15, 2, 1},
                                     {50, 36, 14, 2, 1},
                                     {54, 39, 17, 4, 1},
                                     {46, 34, 14, 3, 1},
                                     {50, 34, 15, 2, 1},
                                     {44, 29, 14, 2, 1},
                                     {49, 31, 15, 1, 1},
                                     {54, 37, 15, 2, 1},
                                     {48, 34, 16, 2, 1},
                                     {48, 30, 14, 1, 1},
                                     {43, 30, 11, 1, 1},
                                     {58, 40, 12, 2, 1},
                                     {57, 44, 15, 4, 1},
                                     {54, 39, 13, 4, 1},
                                     {51, 35, 14, 3, 1},
                                     {57, 38, 17, 3, 1},
                                     {51, 38, 15, 3, 1},
                                     {54, 34, 17, 2, 1},
                                     {51, 37, 15, 4, 1},
                                     {46, 36, 10, 2, 1},
                                     {51, 33, 17, 5, 1},
                                     {48, 34, 19, 2, 1},
                                     {50, 30, 16, 2, 1},
                                     {50, 34, 16, 4, 1},
                                     {52, 35, 15, 2, 1},
                                     {52, 34, 14, 2, 1},
                                     {47, 32, 16, 2, 1},
                                     {48, 31, 16, 2, 1},
                                     {54, 34, 15, 4, 1},
                                     {52, 41, 15, 1, 1},
                                     {55, 42, 14, 2, 1},
                                     {49, 31, 15, 1, 1},
                                     {50, 32, 12, 2, 1},
                                     {55, 35, 13, 2, 1},
                                     {49, 31, 15, 1, 1},
                                     {44, 30, 13, 2, 1},
                                     {51, 34, 15, 2, 1},
                                     {50, 35, 13, 3, 1},
                                     {45, 23, 13, 3, 1},
                                     {44, 32, 13, 2, 1},
                                     {50, 35, 16, 6, 1},
                                     {51, 38, 19, 4, 1},
                                     {48, 30, 14, 3, 1},
                                     {51, 38, 16, 2, 1},
                                     {46, 32, 14, 2, 1},
                                     {53, 37, 15, 2, 1},
                                     {50, 33, 14, 2, 1},
                                     {70, 32, 47, 14, 2},
                                     {64, 32, 45, 15, 2},
                                     {69, 31, 49, 15, 2},
                                     {55, 23, 40, 13, 2},
                                     {65, 28, 46, 15, 2},
                                     {57, 28, 45, 13, 2},
                                     {63, 33, 47, 16, 2},
                                     {49, 24, 33, 10, 2},
                                     {66, 29, 46, 13, 2},
                                     {52, 27, 39, 14, 2},
                                     {50, 20, 35, 10, 2},
                                     {59, 30, 42, 15, 2},
                                     {60, 22, 40, 10, 2},
                                     {61, 29, 47, 14, 2},
                                     {56, 29, 36, 13, 2},
                                     {67, 31, 44, 14, 2},
                                     {56, 30, 45, 15, 2},
                                     {58, 27, 41, 10, 2},
                                     {62, 22, 45, 15, 2},
                                     {56, 25, 39, 11, 2},
                                     {59, 32, 48, 18, 2},
                                     {61, 28, 40, 13, 2},
                                     {63, 25, 49, 15, 2},
                                     {61, 28, 47, 12, 2},
                                     {64, 29, 43, 13, 2},
                                     {66, 30, 44, 14, 2},
                                     {68, 28, 48, 14, 2},
                                     {67, 30, 50, 17, 2},
                                     {60, 29, 45, 15, 2},
                                     {57, 26, 35, 10, 2},
                                     {55, 24, 38, 11, 2},
                                     {55, 24, 37, 10, 2},
                                     {58, 27, 39, 12, 2},
                                     {60, 27, 51, 16, 2},
                                     {54, 30, 45, 15, 2},
                                     {60, 34, 45, 16, 2},
                                     {67, 31, 47, 15, 2},
                                     {63, 23, 44, 13, 2},
                                     {56, 30, 41, 13, 2},
                                     {55, 25, 40, 13, 2},
                                     {55, 26, 44, 12, 2},
                                     {61, 30, 46, 14, 2},
                                     {58, 26, 40, 12, 2},
                                     {50, 23, 33, 10, 2},
                                     {56, 27, 42, 13, 2},
                                     {57, 30, 42, 12, 2},
                                     {57, 29, 42, 13, 2},
                                     {62, 29, 43, 13, 2},
                                     {51, 25, 30, 11, 2},
                                     {57, 28, 41, 13, 2},
                                     {63, 33, 60, 25, 3},
                                     {58, 27, 51, 19, 3},
                                     {71, 30, 59, 21, 3},
                                     {63, 29, 56, 18, 3},
                                     {65, 30, 58, 22, 3},
                                     {76, 30, 66, 21, 3},
                                     {49, 25, 45, 17, 3},
                                     {73, 29, 63, 18, 3},
                                     {67, 25, 58, 18, 3},
                                     {72, 36, 61, 25, 3},
                                     {65, 32, 51, 20, 3},
                                     {64, 27, 53, 19, 3},
                                     {68, 30, 55, 21, 3},
                                     {57, 25, 50, 20, 3},
                                     {58, 28, 51, 24, 3},
                                     {64, 32, 53, 23, 3},
                                     {65, 30, 55, 18, 3},
                                     {77, 38, 67, 22, 3},
                                     {77, 26, 69, 23, 3},
                                     {60, 22, 50, 15, 3},
                                     {69, 32, 57, 23, 3},
                                     {56, 28, 49, 20, 3},
                                     {77, 28, 67, 20, 3},
                                     {63, 27, 49, 18, 3},
                                     {67, 33, 57, 21, 3},
                                     {72, 32, 60, 18, 3},
                                     {62, 28, 48, 18, 3},
                                     {61, 30, 49, 18, 3},
                                     {64, 28, 56, 21, 3},
                                     {72, 30, 58, 16, 3},
                                     {74, 28, 61, 19, 3},
                                     {79, 38, 64, 20, 3},
                                     {64, 28, 56, 22, 3},
                                     {63, 28, 51, 15, 3},
                                     {61, 26, 56, 14, 3},
                                     {77, 30, 61, 23, 3},
                                     {63, 34, 56, 24, 3},
                                     {64, 31, 55, 18, 3},
                                     {60, 30, 48, 18, 3},
                                     {69, 31, 54, 21, 3},
                                     {67, 31, 56, 24, 3},
                                     {69, 31, 51, 23, 3},
                                     {58, 27, 51, 19, 3},
                                     {68, 32, 59, 23, 3},
                                     {67, 33, 57, 25, 3},
                                     {67, 30, 52, 23, 3},
                                     {63, 25, 50, 19, 3},
                                     {65, 30, 52, 20, 3},
                                     {62, 34, 54, 23, 3},
                                     {59, 30, 51, 18, 3}
                                    };





//    int i = 0;

    u_int16_t po_knn_classe_prevista_valor;
    u_int16_t po_knn_classe_prevista_pronto;

    // Mapeamento das portas para o hardware KNN FPGA
    po_knn_classe_prevista_p            = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA, LEITURA);            //Endereço da porta para a classe prevista.
    po_knn_classe_prevista_pronto_p     = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA_PRONTO, LEITURA);     //Endereço da porta para a classe prevista.
    po_knn_dados_p                      = f_Mapear_Memoria(PO_KNN_DADOS, ESCRITA);                      //Endereço dos dados para a classe prevista.
    po_knn_dados_pronto_p               = f_Mapear_Memoria(PO_KNN_DADOS_PRONTO, ESCRITA);
    po_knn_treinamento                  = f_Mapear_Memoria(PO_KNN_TREINAMENTO, ESCRITA);
    po_knn_atributo_n                   = f_Mapear_Memoria(PO_KNN_ATRIBUTO_N, ESCRITA);
    po_knn_reset                        = f_Mapear_Memoria(PO_KNN_RESET, ESCRITA);
    po_knn_k                            = f_Mapear_Memoria(PO_KNN_K, ESCRITA);
    // ---------------------------------------------------------------------------



    if (argc!=1)chr_knn_k = argv[1];

    g_delta_ms_total = 0;

    printf ("FPGA KNN TESTE COMPILACAO 1 PARA O PROJETO 02.NIOS2_SOFT_CORE+VGA+KNN+K.\n");
    printf ("TESTE DA CLASSE KNN FPGA ...\n");

    //*(volatile bool*)po_knn_reset = 0;
    //Informacao de dados para teste
    *(volatile bool*)po_knn_treinamento = 0;

    if (argc == 1) {
        *(volatile u_int16_t*)po_knn_k = 1;
    } else {
        *(volatile u_int16_t*)po_knn_k = (int) *chr_knn_k;
    }

    for (int_loop = 0; int_loop < TOTAL_REGISTROS; int_loop++) {

        //do {

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 0;
            *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][0];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 1;
            *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][1];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 2;
            *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][2];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 3;
            *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][3];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 4;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = 0;                           //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 5;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = 0;                           //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 6;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = 0;                           //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 7;
            *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][4];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            gettimeofday(&start, NULL);
            //int_timeout =0;
            do {
                //int_timeout ++;
                po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

            } while (po_knn_classe_prevista_pronto == 0);
            gettimeofday(&stop, NULL);

            po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;

            delta_ms = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
            g_delta_ms_total = g_delta_ms_total + delta_ms;

        //} while (po_knn_classe_prevista_valor < 1 || po_knn_classe_prevista_valor > 3);



        /*  Calcula o acerto ou erro da previsao */
        int_total_registros ++;
        if (po_knn_classe_prevista_valor == arr_iris_data[int_loop][4]) {

            int_total_registros_corretos++;
            printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos X", po_knn_classe_prevista_valor, arr_iris_data[int_loop][4], (float) delta_ms);

        } else {

            printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos", po_knn_classe_prevista_valor, arr_iris_data[int_loop][4], (float) delta_ms);
        }

       // if (int_timeout >= 10000) {

       //     printf(" TIMEOUT");

      //  }
        printf("\n");

    }

    printf ("\n\nTotal Acertos %d Total Registros %d\n", int_total_registros_corretos, int_total_registros);
    printf ("\n\nTotal Score %.2f%%\n", ((float)int_total_registros_corretos/ (float)int_total_registros) * 100);
    printf ("Tempo Total %5.7f segundo(s) \n", (float)g_delta_ms_total);

    printf ("\n\nCONCLUIDO, SEM ESFORÇO NO HA RESULTADO\n");

    return 0;
}
