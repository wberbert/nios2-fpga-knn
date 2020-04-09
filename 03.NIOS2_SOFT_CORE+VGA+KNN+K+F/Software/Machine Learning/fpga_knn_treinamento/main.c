#include "main.h"

int main(int argc, char *argv[])
{
    //void *po_knn_classe_prevista_p;
    void *po_knn_dados_p;
    void *po_knn_dados_pronto_p;
    void *po_knn_treinamento;
    void *po_knn_atributo_n;
    void *po_knn_reset;
//    void *po_knn_classe_prevista_pronto_p;

//    int i = 0;

 //   u_int16_t po_knn_classe_prevista_valor;
//    u_int16_t po_knn_classe_prevista_pronto;

    // Mapeamento das portas para o hardware KNN FPGA
//    po_knn_classe_prevista_p            = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA, LEITURA);            //Endereço da porta para a classe prevista.
//    po_knn_classe_prevista_pronto_p     = f_Mapear_Memoria(PO_KNN_CLASSE_PREVISTA_PRONTO, LEITURA);     //Endereço da porta para a classe prevista.
    po_knn_dados_p                      = f_Mapear_Memoria(PO_KNN_DADOS, ESCRITA);                      //Endereço dos dados para a classe prevista.
    po_knn_dados_pronto_p               = f_Mapear_Memoria(PO_KNN_DADOS_PRONTO, ESCRITA);
    po_knn_treinamento                  = f_Mapear_Memoria(PO_KNN_TREINAMENTO, ESCRITA);
    po_knn_atributo_n                   = f_Mapear_Memoria(PO_KNN_ATRIBUTO_N, ESCRITA);
    po_knn_reset                        = f_Mapear_Memoria(PO_KNN_RESET, ESCRITA);
    // ---------------------------------------------------------------------------


    printf ("FPGA KNN TREINAMENTO VERSAO 0.30\n");
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
    *(volatile u_int16_t*)po_knn_dados_p = 8;
    *(volatile u_int16_t*)po_knn_atributo_n = 7;  //Atributo reservado para definiçao da classe
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

    *(volatile bool*)po_knn_dados_pronto_p = 0;     //Registrador de preparaço de dados.
    *(volatile u_int16_t*)po_knn_dados_p = 2;       //Classe
    *(volatile u_int16_t*)po_knn_atributo_n = 7;    //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;     //Registrador de preparaço de dados.

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
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
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
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Quinto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 7;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 10;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Sexto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 47;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 45;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 20;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 14;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Setimo registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 21;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 30;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 18;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Oitavo registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 27;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 53;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 32;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 17;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Nono registro para treinamento.
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
    *(volatile u_int16_t*)po_knn_dados_p = 8;
    *(volatile u_int16_t*)po_knn_atributo_n = 7;  //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo registro para treinamento
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

    *(volatile bool*)po_knn_dados_pronto_p = 0;     //Registrador de preparaço de dados.
    *(volatile u_int16_t*)po_knn_dados_p = 2;       //Classe
    *(volatile u_int16_t*)po_knn_atributo_n = 7;    //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;     //Registrador de preparaço de dados.

    //Decimo primeiro registro para treinamento
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
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo segundo registro para treinamento
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
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo terceiro registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 4;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 7;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 2;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 10;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo quarto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 47;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 45;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 20;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 14;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo quinto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 21;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 5;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 30;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 18;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    //Decimo sexto registro para treinamento
    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 27;
    *(volatile u_int16_t*)po_knn_atributo_n = 0;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 53;
    *(volatile u_int16_t*)po_knn_atributo_n = 1;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 32;
    *(volatile u_int16_t*)po_knn_atributo_n = 2;
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    *(volatile bool*)po_knn_dados_pronto_p = 0;
    *(volatile u_int16_t*)po_knn_dados_p = 17;
    *(volatile u_int16_t*)po_knn_atributo_n = 7; //Atributo reservado para definiçao da classe
    *(volatile bool*)po_knn_dados_pronto_p = 1;

    printf ("CONCLUIDO.\n");

    return 0;
}
