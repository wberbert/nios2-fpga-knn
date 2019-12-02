#include "main.h"

#define TOTAL_REGISTROS 15

int main(int argc, char *argv[])
{
    //void *po_knn_classe_prevista_p;
    void    *po_knn_dados_p;
    void    *po_knn_dados_pronto_p;
    void    *po_knn_treinamento;
    void    *po_knn_atributo_n;
    void    *po_knn_reset;
    int     int_loop;

    int     arr_iris_data[15][5] =  {{51, 35, 14, 2, 1},
                                     {49, 30, 14, 2, 1},
                                     {47, 32, 13, 2, 1},
                                     {46, 31, 15, 2, 1},
                                     {50, 36, 14, 2, 1},
                                     {70, 32, 47, 14, 2},
                                     {64, 32, 45, 15, 2},
                                     {69, 31, 49, 15, 2},
                                     {55, 23, 40, 13, 2},
                                     {65, 28, 46, 15, 2},
                                     {63, 33, 60, 25, 3},
                                     {58, 27, 51, 19, 3},
                                     {71, 30, 59, 21, 3},
                                     {63, 29, 56, 18, 3},
                                     {65, 30, 58, 22, 3}
                                    };
    //----------------------------------------------------------------------------
    po_knn_dados_p                      = f_Mapear_Memoria(PO_KNN_DADOS, ESCRITA);                      //Dados para treinamento.
    po_knn_dados_pronto_p               = f_Mapear_Memoria(PO_KNN_DADOS_PRONTO, ESCRITA);               //Indica que os dados enviados estao prontos.
    po_knn_treinamento                  = f_Mapear_Memoria(PO_KNN_TREINAMENTO, ESCRITA);                //Indica se o hardware est em modo treinamento ou modo teste.
    po_knn_atributo_n                   = f_Mapear_Memoria(PO_KNN_ATRIBUTO_N, ESCRITA);                 //Numero do atributo representado pelos dados.
    po_knn_reset                        = f_Mapear_Memoria(PO_KNN_RESET, ESCRITA);                      //Reset do hardware.

    // ---------------------------------------------------------------------------


    printf ("FPGA KNN IRIS TREINAMENTO COMPILACAO 2\n");
    printf ("TREINAMENTO DO FPGA ...\n");

    *(volatile bool*)po_knn_reset = 1;          //Reseta o hardware, para incializaçao interna.
    *(volatile bool*)po_knn_reset = 0;          //Estado normal para execucao de instrucoes.
    *(volatile bool*)po_knn_treinamento = 1;    //Indica que os dados inseridos serao para treinamento.

    for (int_loop = 0; int_loop < TOTAL_REGISTROS; int_loop++) {

         printf("%d\t%d\t%d\t%d\t%d\n", arr_iris_data[int_loop][0],arr_iris_data[int_loop][1],arr_iris_data[int_loop][2],arr_iris_data[int_loop][3],arr_iris_data[int_loop][4]);

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 0;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][0];  //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 1;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][1];  //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 2;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][2];  //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 3;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][3];  //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

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

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dados.
        *(volatile u_int16_t*)po_knn_atributo_n = 7;                        //Atributo numero 7 e utilizado para definir a classe dos dados inseridos.
        *(volatile u_int16_t*)po_knn_dados_p = arr_iris_data[int_loop][4];  //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dados estao prontos.

    }


    printf ("CONCLUIDO.\n");

    return 0;
}
