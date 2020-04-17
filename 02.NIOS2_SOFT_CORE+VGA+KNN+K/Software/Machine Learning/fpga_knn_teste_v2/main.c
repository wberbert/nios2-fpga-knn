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

    int     iV1, iV2, iV3, iV4, iV5, iV6, iV7, iClasse;
    int     int_P;
    bool    bln_Debug = false;

    FILE    *file;

    char    *chr_knn_k;

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

    for (int_P =1; int_P < argc; int_P++) {

        //if (argv[int_P] == "debug") bln_Debug = 1;
        if (strcmp(argv[int_P], "debug") == 0) bln_Debug = true;
    }


    if (argc == 1) {
        printf ("Usar %s \"nome do arquivo de teste\" \"valor de K\" <debug>", argv[0]);
        //printf("Informe o nome do arquivo de treinamento.\n");
        return(-1);
    }

    if (argc == 2) {
        printf ("Usar %s \"nome do arquivo de teste\" \"valor de K\" <debug>", argv[0]);
        //printf("Informe o valor de K.\n");
        return(-1);
    }

    if (argc!=1)chr_knn_k = argv[2];

    file = fopen(argv[1], "r");

    if(file  == NULL) {
        perror("Erro abrindo arquivo");
        return(-1);
    }

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

    while(fscanf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", &iV1, &iV2, &iV3, &iV4, &iV5, &iV6, &iV7, &iClasse)==8) {

            if (bln_Debug == true) printf ("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", iV1, iV2, iV3, iV4, iV5, iV6, iV7, iClasse);

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 0;
            *(volatile u_int16_t*)po_knn_dados_p = iV1;
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 1;
            *(volatile u_int16_t*)po_knn_dados_p = iV2;
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 2;
            *(volatile u_int16_t*)po_knn_dados_p = iV3;
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 3;
            *(volatile u_int16_t*)po_knn_dados_p = iV4;
            *(volatile bool*)po_knn_dados_pronto_p = 1;

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 4;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = iV5;                         //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 5;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = iV6;                         //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = 6;                        //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = iV7;                         //Move o dado para o registrador. Move zero para os atributos nao utilizados do hardware.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = 7;
            *(volatile u_int16_t*)po_knn_dados_p = iClasse;
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
        if (po_knn_classe_prevista_valor == iClasse) {

            int_total_registros_corretos++;
            if (bln_Debug == true) printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos X", po_knn_classe_prevista_valor, iClasse, (float) delta_ms);

        } else {

            if (bln_Debug == true) printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos", po_knn_classe_prevista_valor, iClasse, (float) delta_ms);
        }

       // if (int_timeout >= 10000) {

       //     printf(" TIMEOUT");

      //  }
        if (bln_Debug == true) printf("\n");

    }

    printf ("\n\nTotal Acertos %d Total Registros %d\t k=%c\n", int_total_registros_corretos, int_total_registros, *chr_knn_k);
    printf ("\n\nTotal Score %.2f%%\n", ((float)int_total_registros_corretos/ (float)int_total_registros) * 100);
    printf ("Tempo Total %5.7f segundo(s) \n", (float)g_delta_ms_total);

    printf ("\n\nCONCLUIDO.\n");

    return 0;
}
