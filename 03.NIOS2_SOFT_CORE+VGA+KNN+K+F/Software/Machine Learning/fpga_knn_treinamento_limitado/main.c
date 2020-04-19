#include "main.h"


int main(int argc, char *argv[])
{
    int     int_total_linhas_arquivo = 0;
    int     int_total_execucoes_parciais = 1;

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
    void    *po_knn_classe_prevista_distancia_p;

    //u_int16_t po_knn_classe_prevista_valor;
    u_int16_t po_knn_classe_prevista_pronto;
    //u_int16_t po_knn_classe_prevista_distancia;

    struct  timeval start, stop;
    double  delta_ms, g_delta_ms_total;

    #endif // FPGA

    printf ("SOFTWARE DESENVOLVIDO PARA O MESTRADO DE SISTEMAS DE INFORMACAO\n");
    printf ("UNIVERSIDADE FEDERAL FLUMINENSE\n\n");

    if (argc < 2) {

        printf ("Usar fpga_hardware_limitado \"Total de execucoes parciais\" \"K proximos\"\n\n");
        return(-1);

    }

    //Armazena o total de execucoes parciais que sera utilizado para as execucoes de classificacao do hardware
    int_total_execucoes_parciais = atoi(argv[1]);


    //Armazena as distancias calculadas para depois ordenar e selecionar a classe mais provavel
    p_reg_distancia = (distancia_t *) malloc(sizeof(distancia_t) * int_total_execucoes_parciais);
    p_reg_distancia_ordenada = (distancia_t *) malloc(sizeof(distancia_t) * int_total_execucoes_parciais);


    f_carregar_arquivo_memoria(ARQUIVO, &int_total_linhas_arquivo);

    #ifdef DEBUG
    printf("DEBUG - REGISTROS CARREGADOS EM MEMORIA\n\n");
    for (int int_registro=0; int_registro<150; int_registro++) {

        printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[int_registro][0], pp_int_dados_teste[int_registro][1], pp_int_dados_teste[int_registro][2], pp_int_dados_teste[int_registro][3], pp_int_dados_teste[int_registro][4], pp_int_dados_teste[int_registro][5]);
    }
    //printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[0][0], pp_int_dados_teste[0][1], pp_int_dados_teste[0][2], pp_int_dados_teste[0][3], pp_int_dados_teste[0][4], pp_int_dados_teste[0][5]);
    //printf ("%d\t%d\t%d\t%d\t%d\t%d\n", pp_int_dados_teste[1][0], pp_int_dados_teste[1][1], pp_int_dados_teste[1][2], pp_int_dados_teste[1][3], pp_int_dados_teste[1][4], pp_int_dados_teste[1][5]);

    #endif // DEBUG

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
    po_knn_classe_prevista_distancia_p  = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA_DISTANCIA, LEITURA);  //Endereço da porta para distancia da classe prevista.
// ---------------------------------------------------------------------------
    #endif // FPGA
    printf("\nTREINAMENTO DO HARDWARE\n\n");

    for (int i=0; i < int_total_execucoes_parciais; i++) {

        pp_int_dados_treinamento = (int **) malloc (sizeof(*p_int_atributo) * TOTAL_HARDWARE_TREINAMENTO);  //ALOCA MEMORIA PARA O NUMERO DE LINHAS DO AQUIVO.
        f_selecionar_dados_treinamento(int_total_linhas_arquivo);

        #ifdef FPGA

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

        *(volatile u_int16_t*)po_knn_k = 1;                                             //temporariamente colocado como 1.

        *(volatile bool*)po_knn_treinamento = 0;                                        //Indica que os dados inseridos serao para teste.

        //Carregar dados de teste.
        for (int b = 0; b < TOTAL_HARDWARE_ATRIBUTOS; b++) {

            *(volatile bool*)po_knn_dados_pronto_p = 0;
            *(volatile u_int16_t*)po_knn_atributo_n = b;
            *(volatile u_int16_t*)po_knn_dados_p = pp_int_dados_teste[0][b];
            *(volatile bool*)po_knn_dados_pronto_p = 1;

        }

        gettimeofday(&start, NULL);
        do {

            po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

        } while (po_knn_classe_prevista_pronto == 0);
        gettimeofday(&stop, NULL);
        delta_ms = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        //po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
        //po_knn_classe_prevista_distancia = *(volatile u_int16_t*)po_knn_classe_prevista_distancia_p;

        p_reg_distancia[i].po_knn_classe_prevista_classe = *(volatile u_int16_t*)po_knn_classe_prevista_p;
        p_reg_distancia[i].po_knn_classe_prevista_distancia = *(volatile u_int16_t*)po_knn_classe_prevista_distancia_p;
        p_reg_distancia[i].int_classe_real = pp_int_dados_teste[0][5];
        p_reg_distancia[i].dbl_tempo_ms = delta_ms;

        //p_reg_distancia = malloc (sizeof(reg_distancia));

        //printf ("Classe prevista %d\t Classe real %d\t Distancia %d\n", po_knn_classe_prevista_valor, pp_int_dados_teste[0][5], po_knn_classe_prevista_distancia);

        #endif // FPGA

        free(pp_int_dados_treinamento);
    }

    #ifdef FPGA
    printf("\nRESULTADO DAS EXECUCOES PARCIAIS\n\n");
    for (int g=0; g < int_total_execucoes_parciais; g++) {

        printf ("Classe prevista %d\t Classe real %d\t Distancia %d\t Tempo %5.7f Segundos", p_reg_distancia[g].po_knn_classe_prevista_classe, p_reg_distancia[g].int_classe_real, p_reg_distancia[g].po_knn_classe_prevista_distancia, (float) p_reg_distancia[g].dbl_tempo_ms);
        if (p_reg_distancia[g].po_knn_classe_prevista_classe == p_reg_distancia[g].int_classe_real) {
            printf(" X\n");
        } else {
            printf("\n");
        }
    }
    #endif // FPGA

    free(p_reg_distancia);
    free(p_reg_distancia_ordenada);

  // p_reg_distancia->classe =1;
//    p_reg_distancia->distancia =2;

//    printf ("Classe prevista %d\t Distancia %d\n", p_reg_distancia->classe, p_reg_distancia->distancia);

    printf ("\nCONCLUIDO.\n");

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

            p_int_atributo = (int *) malloc(sizeof (int) * TOTAL_HARDWARE_ATRIBUTOS);   //ALOCA MEMORIA PARA UMA LINHA DO ARQUIVO.

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

    srand(rand() + time(0));

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
