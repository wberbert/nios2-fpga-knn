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

    int     iV1, iV2, iV3, iV4, iV5, iV6, iV7, iClasse;

    FILE    *file;

    if (argc == 1) {
        printf("Informe o nome do arquivo de treinamento.\n");
        return(-1);
    }

    file = fopen(argv[1], "r");

    if(file  == NULL) {
        perror("Error opening file");
        return(-1);
    }

/*    while(fscanf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", &iV1, &iV2, &iV3, &iV4, &iV5, &iV6, &iV7, &iClasse)==8)
    {
        //puts(iLinha);

        printf ("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", iV1, iV2, iV3, iV4, iV5, iV6, iV7, iClasse);

    }
    return 0;
*/
    //----------------------------------------------------------------------------
    po_knn_dados_p                      = f_Mapear_Memoria(PO_KNN_DADOS, ESCRITA);                      //Dados para treinamento.
    po_knn_dados_pronto_p               = f_Mapear_Memoria(PO_KNN_DADOS_PRONTO, ESCRITA);               //Indica que os dados enviados estao prontos.
    po_knn_treinamento                  = f_Mapear_Memoria(PO_KNN_TREINAMENTO, ESCRITA);                //Indica se o hardware est em modo treinamento ou modo teste.
    po_knn_atributo_n                   = f_Mapear_Memoria(PO_KNN_ATRIBUTO_N, ESCRITA);                 //Numero do atributo representado pelos dados.
    po_knn_reset                        = f_Mapear_Memoria(PO_KNN_RESET, ESCRITA);                      //Reset do hardware.

    // ---------------------------------------------------------------------------

    printf ("FPGA KNN IRIS TREINAMENTO VERSAO 2\n");
    printf ("TREINAMENTO DO FPGA ...\n");

    *(volatile bool*)po_knn_reset = 1;          //Reseta o hardware, para incializaçao interna.
    *(volatile bool*)po_knn_reset = 0;          //Estado normal para execucao de instrucoes.
    *(volatile bool*)po_knn_treinamento = 1;    //Indica que os dados inseridos serao para treinamento.

    while(fscanf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", &iV1, &iV2, &iV3, &iV4, &iV5, &iV6, &iV7, &iClasse)==8) {

        printf ("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", iV1, iV2, iV3, iV4, iV5, iV6, iV7, iClasse);

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 0;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = iV1;                         //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 1;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = iV2;                         //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 2;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = iV3;                         //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dado.
        *(volatile u_int16_t*)po_knn_atributo_n = 3;                        //Indica o numero do atributo.
        *(volatile u_int16_t*)po_knn_dados_p = iV4;                         //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dado esta pronto.

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

        *(volatile bool*)po_knn_dados_pronto_p = 0;                         //Incializa registrador de dados.
        *(volatile u_int16_t*)po_knn_atributo_n = 7;                        //Ultimo atributo e utilizado para definir a classe dos dados inseridos.
        *(volatile u_int16_t*)po_knn_dados_p = iClasse;                     //Move o dado para o registrador.
        *(volatile bool*)po_knn_dados_pronto_p = 1;                         //Indica que os dados estao prontos.

    }


    printf ("CONCLUIDO.\n");

    return 0;
}
