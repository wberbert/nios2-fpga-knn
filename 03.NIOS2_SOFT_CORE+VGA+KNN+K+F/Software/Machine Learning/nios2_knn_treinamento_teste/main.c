#include "main.h"

#define TOTAL_REGISTROS  6
#define TOTAL_ATRIBUTOS  8

#define KNN_K 2

int g_int_arr_dados_treinamento[TOTAL_REGISTROS][TOTAL_ATRIBUTOS];
int g_int_arr_dados_teste[TOTAL_ATRIBUTOS];
int g_int_arr_distancias[TOTAL_REGISTROS][2];
int g_int_arr_distancias_ordenadas[TOTAL_REGISTROS][2];

int g_int_classe_prevista = 0;

struct timeval g_start, g_stop;
double g_delta_ms;

int  g_int_total_registros_corretos = 0;

int main(int argc, char *argv[])
{
   // int a;

    fnc_treinar();

    fnc_testar();

/*

    for (a=0; a < TOTAL_REGISTROS; a++) {

        printf("%d\t%d\n", g_int_arr_distancias[a][0], g_int_arr_distancias[a][1]);

    }

    printf("\n\n");

    for (a=0; a < TOTAL_REGISTROS; a++) {

        printf("%d\t%d\n", g_int_arr_distancias_ordenadas[a][0], g_int_arr_distancias_ordenadas[a][1]);

    }

*/

    printf("Sucesso !!!");

    return 0;
}

int fnc_treinar (void) {
    int int_registro, int_atributo;

    for (int_registro = 0; int_registro < TOTAL_REGISTROS; int_registro++) {

        for (int_atributo = 0; int_atributo < TOTAL_ATRIBUTOS; int_atributo++) {

            g_int_arr_dados_treinamento[int_registro][int_atributo] = 0;

        }

    }

    g_int_arr_dados_treinamento [0][0] = 2;
    g_int_arr_dados_treinamento [0][1] = 4;
    g_int_arr_dados_treinamento [0][2] = 3;
    g_int_arr_dados_treinamento [0][3] = 4;
    g_int_arr_dados_treinamento [0][4] = 0;
    g_int_arr_dados_treinamento [0][5] = 0;
    g_int_arr_dados_treinamento [0][6] = 0;
    g_int_arr_dados_treinamento [0][7] = 2;

    g_int_arr_dados_treinamento [1][0] = 1;
    g_int_arr_dados_treinamento [1][1] = 2;
    g_int_arr_dados_treinamento [1][2] = 3;
    g_int_arr_dados_treinamento [1][3] = 4;
    g_int_arr_dados_treinamento [1][4] = 0;
    g_int_arr_dados_treinamento [1][5] = 0;
    g_int_arr_dados_treinamento [1][6] = 0;
    g_int_arr_dados_treinamento [1][7] = 4;

    g_int_arr_dados_treinamento [2][0] = 1;
    g_int_arr_dados_treinamento [2][1] = 2;
    g_int_arr_dados_treinamento [2][2] = 3;
    g_int_arr_dados_treinamento [2][3] = 4;
    g_int_arr_dados_treinamento [2][4] = 0;
    g_int_arr_dados_treinamento [2][5] = 0;
    g_int_arr_dados_treinamento [2][6] = 0;
    g_int_arr_dados_treinamento [2][7] = 7;

    g_int_arr_dados_treinamento [3][0] = 3;
    g_int_arr_dados_treinamento [3][1] = 5;
    g_int_arr_dados_treinamento [3][2] = 4;
    g_int_arr_dados_treinamento [3][3] = 3;
    g_int_arr_dados_treinamento [3][4] = 0;
    g_int_arr_dados_treinamento [3][5] = 0;
    g_int_arr_dados_treinamento [3][6] = 0;
    g_int_arr_dados_treinamento [3][7] = 8;

    g_int_arr_dados_treinamento [4][0] = 2;
    g_int_arr_dados_treinamento [4][1] = 3;
    g_int_arr_dados_treinamento [4][2] = 4;
    g_int_arr_dados_treinamento [4][3] = 5;
    g_int_arr_dados_treinamento [4][4] = 0;
    g_int_arr_dados_treinamento [4][5] = 0;
    g_int_arr_dados_treinamento [4][6] = 0;
    g_int_arr_dados_treinamento [4][7] = 10;

    g_int_arr_dados_treinamento [5][0] = 2;
    g_int_arr_dados_treinamento [5][1] = 3;
    g_int_arr_dados_treinamento [5][2] = 4;
    g_int_arr_dados_treinamento [5][3] = 5;
    g_int_arr_dados_treinamento [5][4] = 0;
    g_int_arr_dados_treinamento [5][5] = 0;
    g_int_arr_dados_treinamento [5][6] = 0;
    g_int_arr_dados_treinamento [5][7] = 10;


    return 0;
}

int fnc_testar (void) {

    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 0;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 2;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    if (g_int_arr_dados_teste[7] == g_int_classe_prevista) g_int_total_registros_corretos++;

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);

    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    if (g_int_arr_dados_teste[7] == g_int_classe_prevista) g_int_total_registros_corretos++;

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);

    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    if (g_int_arr_dados_teste[7] == g_int_classe_prevista) g_int_total_registros_corretos++;

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);

    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);


    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    if (g_int_arr_dados_teste[7] == g_int_classe_prevista) g_int_total_registros_corretos++;

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);


    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    if (g_int_arr_dados_teste[7] == g_int_classe_prevista) g_int_total_registros_corretos++;

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);


    g_int_arr_dados_teste[0] = 2;
    g_int_arr_dados_teste[1] = 3;
    g_int_arr_dados_teste[2] = 4;
    g_int_arr_dados_teste[3] = 5;
    g_int_arr_dados_teste[4] = 0;
    g_int_arr_dados_teste[5] = 0;
    g_int_arr_dados_teste[6] = 0;
    g_int_arr_dados_teste[7] = 10;

    gettimeofday(&g_start, NULL);
    fnc_calcular_distancia_euclidiana();
    fnc_ordenar();
    fnc_obter_k_proximos();
    gettimeofday(&g_stop, NULL);

    g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
    printf("%5.7f Segundos\n", (double) g_delta_ms);

    printf ("Classe prevista %d\t Classe real %d\n", g_int_classe_prevista, g_int_arr_dados_teste[7]);


    printf ("\n\nTotal Score %.2f%%\n", ((float)g_int_total_registros_corretos/TOTAL_REGISTROS) * 100);

    return 0;

}

int fnc_calcular_distancia_euclidiana (void) {
    int int_distancia   = 0;
    int int_registro    = 0;
    int int_atributo    = 0;

    for (int_registro = 0; int_registro < TOTAL_REGISTROS; int_registro ++) {


        int_distancia = 0;

        g_int_arr_distancias[int_registro][0] = g_int_arr_dados_treinamento[int_registro][TOTAL_ATRIBUTOS - 1]; /*Armazena a classe*/

        for (int_atributo = 0; int_atributo < (TOTAL_ATRIBUTOS - 1); int_atributo++) {

            int_distancia = int_distancia + pow((g_int_arr_dados_teste[int_atributo] - g_int_arr_dados_treinamento[int_registro][int_atributo]), 2);

        }

        g_int_arr_distancias[int_registro][1] = sqrt(int_distancia) ;

    }

    return 0;
}

int fnc_ordenar(void) {
    int int_arr_distancia_armazenada[2][2];
    int int_o = 0, int_i = 0;

    memcpy(g_int_arr_distancias_ordenadas, g_int_arr_distancias, sizeof(g_int_arr_distancias));

    for (int_o = 0; int_o < TOTAL_REGISTROS; int_o++) {

        for (int_i = 0; int_i < ((TOTAL_REGISTROS / 2) -1); int_i++) {

            int_arr_distancia_armazenada[0][0] = g_int_arr_distancias_ordenadas[(2 * int_i) + 1][0]; /*Armazena a classe*/
            int_arr_distancia_armazenada[0][1] = g_int_arr_distancias_ordenadas[(2 * int_i) + 1][1]; /*Armazena a distancia*/

            int_arr_distancia_armazenada[1][0] = g_int_arr_distancias_ordenadas[(2 * int_i) + 2][0]; /*Armazena a classe*/
            int_arr_distancia_armazenada[1][1] = g_int_arr_distancias_ordenadas[(2 * int_i) + 2][1]; /*Armazena a distancia*/

            if (int_arr_distancia_armazenada[0][1] > int_arr_distancia_armazenada[1][1]) {

                g_int_arr_distancias_ordenadas[(2 * int_i) + 1][0] = int_arr_distancia_armazenada[1][0];
                g_int_arr_distancias_ordenadas[(2 * int_i) + 1][1] = int_arr_distancia_armazenada[1][1];

                g_int_arr_distancias_ordenadas[(2 * int_i) + 2][0] = int_arr_distancia_armazenada[0][0];
                g_int_arr_distancias_ordenadas[(2 * int_i) + 2][1] = int_arr_distancia_armazenada[0][1];

            }

        }

        for (int_i = 0; int_i < ((TOTAL_REGISTROS / 2)); int_i++) {

            int_arr_distancia_armazenada[0][0] = g_int_arr_distancias_ordenadas[(2 * int_i)][0]; /*Armazena a classe*/
            int_arr_distancia_armazenada[0][1] = g_int_arr_distancias_ordenadas[(2 * int_i)][1]; /*Armazena a distancia*/

            int_arr_distancia_armazenada[1][0] = g_int_arr_distancias_ordenadas[(2 * int_i) + 1][0]; /*Armazena a classe*/
            int_arr_distancia_armazenada[1][1] = g_int_arr_distancias_ordenadas[(2 * int_i) + 1][1]; /*Armazena a distancia*/

            if (int_arr_distancia_armazenada[0][1] > int_arr_distancia_armazenada[1][1]) {

                g_int_arr_distancias_ordenadas[(2 * int_i)][0] = int_arr_distancia_armazenada[1][0];
                g_int_arr_distancias_ordenadas[(2 * int_i)][1] = int_arr_distancia_armazenada[1][1];

                g_int_arr_distancias_ordenadas[(2 * int_i) + 1][0] = int_arr_distancia_armazenada[0][0];
                g_int_arr_distancias_ordenadas[(2 * int_i) + 1][1] = int_arr_distancia_armazenada[0][1];

            }

        }
    }

    return 0;
}

int fnc_obter_k_proximos(void) {
    unsigned short bln_achou = 0;
    int int_a = 0, int_b =0;
    int int_classe = 0;
    int int_k_proximos_posicao = 0;
    int int_arr_proximos[TOTAL_REGISTROS][2] = {0};
    int int_k_proximor_maior_total = 0;


    int_k_proximos_posicao = 0;
    int_k_proximor_maior_total = 0;
    bln_achou = 0;

    for (int_a =0; int_a < KNN_K; int_a++) {

        bln_achou = 0;
        int_classe = g_int_arr_distancias_ordenadas[int_a][0];

        for (int_b = 0; int_b < TOTAL_REGISTROS; int_b++) {

            if (int_classe == int_arr_proximos[int_b][0]) {

                int_arr_proximos[int_b][1] = int_arr_proximos[int_b][1] + 1;
                bln_achou = 1;
                break;

            }

        }

        if (bln_achou == 0) {

            int_arr_proximos[int_k_proximos_posicao][0] = int_classe;
            int_arr_proximos[int_k_proximos_posicao][1] = 1;
            int_k_proximos_posicao++;

        }

    }

    for (int_a = 0; int_a < TOTAL_REGISTROS; int_a++) {

        if (int_arr_proximos[int_a][1] > int_k_proximor_maior_total) {

            int_k_proximor_maior_total = int_arr_proximos[int_a][1];
            int_classe = int_arr_proximos[int_a][0];


        }

    }

    //printf ("Classe prevista %d\n\n", int_classe);

    g_int_classe_prevista = int_classe;

    return 0;

}
