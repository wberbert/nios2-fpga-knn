#include "main.h"

int main(int argc, char *argv[])
{
    void *po_knn_classe_prevista_p;
    void *po_knn_dados_p;
    void *po_knn_dados_pronto_p;
    void *po_knn_treinamento;
    void *po_knn_atributo_n;
    void *po_knn_reset;
    void *po_knn_classe_prevista_pronto_p;

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
    // ---------------------------------------------------------------------------

    //printf ("Endereco mapeado %p\n", po_knn_classe_prevista_p);
    //printf ("Endereco mapeado %p\n", po_knn_dados_p);
    //printf ("Endereco mapeado %p\n", po_knn_dados_pronto_p);

    printf ("FPGA KNN TREINAMENTO VERSAO 0.01\n");
    printf ("TREINAMENTO DO FPGA ...\n");

    *(volatile bool*)po_knn_reset = 1;
    *(volatile bool*)po_knn_reset = 0;

    *(volatile bool*)po_knn_treinamento = 1;

    //Primeiro registro para treinamento.
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 3;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 0;
    *(volatile u_int16_t*)po_knn_atributo_n = 15;  //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Segundo registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 1;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 3;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 15; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Terceiro registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 6;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 6;
    *(volatile u_int16_t*)po_knn_atributo_n = 15; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Quarto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 15; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;


    printf ("CONCLUIDO.\N");


    //Informacao de dados para teste
    *(volatile bool*)po_knn_treinamento = 0;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 1;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 3;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 15; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;


    //*(volatile bool*)po_knn_dados_pronto_p = 0;


    //*(volatile bool*)po_knn_reset = 1;
    //*(volatile bool*)po_knn_reset = 0;

    *(volatile u_int16_t*)po_knn_atributo_n = 0;

//    po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;
//    printf ("Classe prevista pronto %d\n", po_knn_classe_prevista_pronto);

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

   *(volatile u_int16_t*)po_knn_atributo_n = 1;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);


    *(volatile u_int16_t*)po_knn_atributo_n = 2;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);


    *(volatile u_int16_t*)po_knn_atributo_n = 3;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);


    *(volatile u_int16_t*)po_knn_atributo_n = 4;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 5;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 6;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 7;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 8;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 9;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 10;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 11;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 12;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 13;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 14;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);

    *(volatile u_int16_t*)po_knn_atributo_n = 15;

    do {

        po_knn_classe_prevista_pronto = *(volatile u_int16_t*)po_knn_classe_prevista_pronto_p;

    } while (po_knn_classe_prevista_pronto == 0);

    po_knn_classe_prevista_valor = *(volatile u_int16_t*)po_knn_classe_prevista_p;
    printf ("Distancia Euclidiana %d\n", po_knn_classe_prevista_valor);



    printf("Sucesso !!!");

    return 0;
}
