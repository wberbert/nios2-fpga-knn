#include "main.h"


int main(int argc, char *argv[])
{
    int     int_total_linhas_arquivo = 0;
    //void *po_knn_classe_prevista_p;
    #ifdef  FPGA
    void    *po_knn_dados_p;
    void    *po_knn_dados_pronto_p;
    void    *po_knn_treinamento;
    void    *po_knn_atributo_n;
    void    *po_knn_reset;
    void    *po_knn_classe_prevista_p;
    void    *po_knn_classe_prevista_pronto_p;
    void    *po_knn_k;

    u_int16_t po_knn_classe_prevista_valor;
    u_int16_t po_knn_classe_prevista_pronto;
    #endif // FPGA

    printf ("SOFTWARE DESENVOLVIDO PARA O MESTRADO DE SISTEMAS DE INFORMACAO\n");
    printf ("UNIVERSIDADE FEDERAL FLUMINENSE\n\n");



    f_carregar_arquivo_memoria(ARQUIVO, &int_total_linhas_arquivo);

    #ifdef DEBUG
    printf("DEBUG - REGISTROS CARREGADOS EM MEMORIA\n\n");
    for (int int_registro=0; int_registro<150; int_registro++) {

        printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[int_registro][0], pp_int_dados_teste[int_registro][1], pp_int_dados_teste[int_registro][2], pp_int_dados_teste[int_registro][3], pp_int_dados_teste[int_registro][4], pp_int_dados_teste[int_registro][5]);
    }
    //printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[0][0], pp_int_dados_teste[0][1], pp_int_dados_teste[0][2], pp_int_dados_teste[0][3], pp_int_dados_teste[0][4], pp_int_dados_teste[0][5]);
    //printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[1][0], pp_int_dados_teste[1][1], pp_int_dados_teste[1][2], pp_int_dados_teste[1][3], pp_int_dados_teste[1][4], pp_int_dados_teste[1][5]);

    #endif // DEBUG

    f_selecionar_dados_treinamento(int_total_linhas_arquivo);

    printf("\nTREINAMENTO DO HARDWARE\n\n");

    #ifdef FPGA
//--- FGPA HARDWARE DE2-115 -- TREINAMENTO
    po_knn_dados_p                      = f_Mapear_Memoria(PO_KNN_DADOS, ESCRITA);                      //Dados para treinamento.
    po_knn_dados_pronto_p               = f_Mapear_Memoria(PO_KNN_DADOS_PRONTO, ESCRITA);               //Indica que os dados enviados estao prontos.
    po_knn_treinamento                  = f_Mapear_Memoria(PO_KNN_TREINAMENTO, ESCRITA);                //Indica se o hardware esta em modo treinamento ou modo teste.
    po_knn_atributo_n                   = f_Mapear_Memoria(PO_KNN_ATRIBUTO_N, ESCRITA);                 //Numero do atributo representado pelos dados.
    po_knn_reset                        = f_Mapear_Memoria(PO_KNN_RESET, ESCRITA);                      //Reset do hardware.
    po_knn_k                            = f_Mapear_Memoria(PO_KNN_K, ESCRITA);                          //Endereço da porta para o valor de K.
    po_knn_classe_prevista_p            = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA, LEITURA);            //Endereço da porta para a classe prevista.
    po_knn_classe_prevista_pronto_p     = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA_PRONTO, LEITURA);     //Endereço da porta para a classe prevista.
// ---------------------------------------------------------------------------


    *(volatile bool*)po_knn_reset = 1;          //Reseta o hardware, para incializaçao interna.
    *(volatile bool*)po_knn_reset = 0;          //Estado normal para execucao de instrucoes.
    *(volatile bool*)po_knn_treinamento = 1;    //Indica que os dados inseridos serao para treinamento.


    for (int a = 0; a < TOTAL_HARDWARE_TREINAMENTO; a++) {

        for (int b =0; b < TOTAL_HARDWARE_ATRIBUTOS; b++) {

            *(volatile bool*)po_knn_dados_pronto_p = 0;                             //Incializa registrador de dado.
            *(volatile u_int16_t*)po_knn_atributo_n = b;                            //Indica o numero do atributo.
            *(volatile u_int16_t*)po_knn_dados_p = pp_int_dados_treinamento[a][b];  //Move o dado para o registrador.
            *(volatile bool*)po_knn_dados_pronto_p = 1;                             //Indica que os dado esta pronto.
        }


    }

    #endif // FPGA

    printf("\nTESTE DO HARDWARE\n\n");

    #ifdef FPGA
    *(volatile u_int16_t*)po_knn_k = 1;

    *(volatile bool*)po_knn_treinamento = 0;        //Indica que os dados inseridos serao para teste.

    for (int b = 0; b < TOTAL_HARDWARE_ATRIBUTOS; b++) {

        *(volatile bool*)po_knn_dados_pronto_p = 0;
        *(volatile u_int16_t*)po_knn_atributo_n = b;
        *(volatile u_int16_t*)po_knn_dados_p = pp_int_dados_teste[0][b];
        *(volatile bool*)po_knn_dados_pronto_p = 1;

    }

    do {
        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;

    printf ("Classe prevista %d\t Classe real %d\n", po_knn_classe_prevista_valor, pp_int_dados_teste[0][5]);

    #endif // FPGA

    printf ("CONCLUIDO.\n");

    return 0;
}

int f_total_linhas_arquivo (char * str_arquivo) {
    int int_total_linhas = 0;
    char chr_info;
    FILE *pfile;

    pfile = fopen (ARQUIVO,"r");

    while(fread(&chr_info, sizeof(char), 1, pfile)==1) {

        if (chr_info == '\n') {
            int_total_linhas ++;
        }

    }

    fclose(pfile);

    return int_total_linhas;
}

void f_carregar_arquivo_memoria (char *str_arquivo, int *int_total_linhas_arquivo) {
    FILE    *pfile;
    int     int_registro =0;
    int     a1,a2,a3,a4,a5,a6;

    pfile = fopen(str_arquivo, "r");

    if(pfile  == NULL) {
        perror("Error opening file");
        return;
    }

    *int_total_linhas_arquivo = f_total_linhas_arquivo(str_arquivo);

    pp_int_dados_teste = (int **) malloc (sizeof(*p_int_atributo) * (*int_total_linhas_arquivo));  //ALOCA MEMORIA PARA O NUMERO DE LINHAS DO AQUIVO.

    int_registro = 0;
    while(true) {


        if (fscanf(pfile, "%d\t%d\t%d\t%d\t%d\t%d\t\n", &a1, &a2, &a3, &a4, &a5, &a6)==6) {

            p_int_atributo = (int *) malloc(sizeof (int) * 6);                                          //ALOCA MEMORIA PARA UMA LINHA DO ARQUIVO.

            *(p_int_atributo + 0) = a1;
            *(p_int_atributo + 1) = a2;
            *(p_int_atributo + 2) = a3;
            *(p_int_atributo + 3) = a4;
            *(p_int_atributo + 4) = a5;
            *(p_int_atributo + 5) = a6;
            pp_int_dados_teste[int_registro] = p_int_atributo;

            //printf("%d\n", int_registro);
           // printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[int_registro][0], pp_int_dados_teste[int_registro][1], pp_int_dados_teste[int_registro][2], pp_int_dados_teste[int_registro][3], pp_int_dados_teste[int_registro][4], pp_int_dados_teste[int_registro][5]);

            int_registro++;

        } else {
            //free(p_int_atributo);
            break;
        }
    }


}

void f_selecionar_dados_treinamento(int int_total_registros_treinamento) {
    time_t t;

    srand((unsigned) &t);

    pp_int_dados_treinamento = (int **) malloc (sizeof(*p_int_atributo) * TOTAL_HARDWARE_TREINAMENTO);  //ALOCA MEMORIA PARA O NUMERO DE LINHAS DO AQUIVO.

    #ifdef DEBUG
    printf("\nDEBUG - REGISTROS DE TREINAMENTO CARREGADOS EM MEMORIA\n\n");
    #endif // DEBUG

    for (int a=0; a < TOTAL_HARDWARE_TREINAMENTO; a++) {

        pp_int_dados_treinamento[a] = pp_int_dados_teste[rand() % int_total_registros_treinamento];
        #ifdef DEBUG
        printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_treinamento[a][0], pp_int_dados_treinamento[a][1], pp_int_dados_treinamento[a][2], pp_int_dados_treinamento[a][3], pp_int_dados_treinamento[a][4], pp_int_dados_treinamento[a][5]);
        #endif // DEBUG
    }

}
