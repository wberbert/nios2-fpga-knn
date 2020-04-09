#include "main.h"

#define TOTAL_REGISTROS_TREINAMENTO 15
#define TOTAL_REGISTROS_TESTE       150
#define TOTAL_ATRIBUTOS             5


#define KNN_K 1

//int g_int_arr_dados_treinamento[TOTAL_REGISTROS_TREINAMENTO][TOTAL_ATRIBUTOS];
int g_int_arr_dados_teste[TOTAL_ATRIBUTOS];
int g_int_arr_distancias[TOTAL_REGISTROS_TREINAMENTO * 3][2];
int g_int_arr_distancias_ordenadas[TOTAL_REGISTROS_TREINAMENTO * 3][2];

int g_int_arr_distancias_consolidades[3][2];

int g_int_classe_prevista = 0;

int g_arr_classe_prevista [1][2];

int g_int_arr_iris_data_treinamento[15][5] =    {
                                                    {51, 35, 14, 2, 1},
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

int g_int_arr_iris_data_treinamento_b[15][5] =    {
                                                    {47, 32, 16, 2, 1},
                                                    {48, 31, 16, 2, 1},
                                                    {54, 34, 15, 4, 1},
                                                    {52, 41, 15, 1, 1},
                                                    {55, 42, 14, 2, 1},
                                                    {61, 30, 46, 14, 2},
                                                    {58, 26, 40, 12, 2},
                                                    {50, 23, 33, 10, 2},
                                                    {56, 27, 42, 13, 2},
                                                    {57, 30, 42, 12, 2},
                                                    {69, 31, 51, 23, 3},
                                                    {58, 27, 51, 19, 3},
                                                    {68, 32, 59, 23, 3},
                                                    {67, 33, 57, 25, 3},
                                                    {67, 30, 52, 23, 3}
                                                };

int g_int_arr_iris_data_treinamento_c[15][5] =    {
                                                    {48, 30, 14, 3, 1},
                                                    {51, 38, 16, 2, 1},
                                                    {46, 32, 14, 2, 1},
                                                    {53, 37, 15, 2, 1},
                                                    {50, 33, 14, 2, 1},
                                                    {57, 30, 42, 12, 2},
                                                    {57, 29, 42, 13, 2},
                                                    {62, 29, 43, 13, 2},
                                                    {51, 25, 30, 11, 2},
                                                    {57, 28, 41, 13, 2},
                                                    {67, 30, 52, 23, 3},
                                                    {63, 25, 50, 19, 3},
                                                    {65, 30, 52, 20, 3},
                                                    {62, 34, 54, 23, 3},
                                                    {59, 30, 51, 18, 3}
                                                };


int g_int_arr_iris_data_teste[150][5] =         {
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

struct timeval g_start, g_stop;
double g_delta_ms, g_delta_ms_total;

int  g_int_total_registros_corretos = 0;
bool bln_debug = false;

int main(int argc, char *argv[])
{
    int int_P;

    for (int_P=1; int_P < argc; int_P++) {

        //if (argv[int_P] == "debug") bln_Debug = 1;
        if (strcmp(argv[int_P], "debug") == 0) bln_debug = true;

    }

    fnc_testar();

    printf("Sucesso !!!");

    return 0;
}


int fnc_testar (void) {
    int int_loop;

    g_delta_ms_total = 0;

    for (int_loop = 0; int_loop < TOTAL_REGISTROS_TESTE; int_loop++) {

        g_int_arr_dados_teste[0] = g_int_arr_iris_data_teste[int_loop][0];
        g_int_arr_dados_teste[1] = g_int_arr_iris_data_teste[int_loop][1];
        g_int_arr_dados_teste[2] = g_int_arr_iris_data_teste[int_loop][2];
        g_int_arr_dados_teste[3] = g_int_arr_iris_data_teste[int_loop][3];
        g_int_arr_dados_teste[4] = g_int_arr_iris_data_teste[int_loop][4];


        gettimeofday(&g_start, NULL);

        fnc_calcular_distancia_euclidiana();
        fnc_ordenar();
        fnc_obter_k_proximos();


        gettimeofday(&g_stop, NULL);

        g_delta_ms = (double)(g_stop.tv_usec - g_start.tv_usec) / 1000000 + (double)(g_stop.tv_sec - g_start.tv_sec);
        g_delta_ms_total = g_delta_ms_total + g_delta_ms;

        if (g_int_arr_dados_teste[4] == g_int_classe_prevista) {

            g_int_total_registros_corretos++;
            if (bln_debug == true) printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos X\n", g_int_classe_prevista, g_int_arr_dados_teste[4], (float) g_delta_ms);

        } else {

            if (bln_debug == true) printf ("Classe prevista %d\t Classe real %d\t %5.7f Segundos  \n", g_int_classe_prevista, g_int_arr_dados_teste[4], (float) g_delta_ms);

        }

    }

    printf ("\n\nTotal Score %.2f%%\n", ((float)g_int_total_registros_corretos/TOTAL_REGISTROS_TESTE) * 100);
    printf ("Tempo Total %5.7f segundo(s) \n", (float)g_delta_ms_total);

    return 0;

}

int fnc_calcular_distancia_euclidiana (void) {
    int int_distancia   = 0;
    int int_registro    = 0;
    int int_atributo    = 0;

    int int_contador    = 0;

    for (int_registro = 0; int_registro < TOTAL_REGISTROS_TREINAMENTO; int_registro ++) {


        int_distancia = 0;

        g_int_arr_distancias[int_contador][0] = g_int_arr_iris_data_treinamento[int_contador][TOTAL_ATRIBUTOS - 1]; /*Armazena a classe*/

        for (int_atributo = 0; int_atributo < (TOTAL_ATRIBUTOS - 1); int_atributo++) {

            int_distancia = int_distancia + pow((g_int_arr_dados_teste[int_atributo] - g_int_arr_iris_data_treinamento[int_contador][int_atributo]), 2);

        }

        g_int_arr_distancias[int_contador][1] = sqrt(int_distancia) ;

        int_contador ++;

    }

    for (int_registro = 0; int_registro < TOTAL_REGISTROS_TREINAMENTO; int_registro ++) {


        int_distancia = 0;

        g_int_arr_distancias[int_contador][0] = g_int_arr_iris_data_treinamento_b[int_contador][TOTAL_ATRIBUTOS - 1]; /*Armazena a classe*/

        for (int_atributo = 0; int_atributo < (TOTAL_ATRIBUTOS - 1); int_atributo++) {

            int_distancia = int_distancia + pow((g_int_arr_dados_teste[int_atributo] - g_int_arr_iris_data_treinamento_b[int_contador][int_atributo]), 2);

        }

        g_int_arr_distancias[int_contador][1] = sqrt(int_distancia) ;

        int_contador ++;

    }

    for (int_registro = 0; int_registro < TOTAL_REGISTROS_TREINAMENTO; int_registro ++) {


        int_distancia = 0;

        g_int_arr_distancias[int_contador][0] = g_int_arr_iris_data_treinamento_c[int_contador][TOTAL_ATRIBUTOS - 1]; /*Armazena a classe*/

        for (int_atributo = 0; int_atributo < (TOTAL_ATRIBUTOS - 1); int_atributo++) {

            int_distancia = int_distancia + pow((g_int_arr_dados_teste[int_atributo] - g_int_arr_iris_data_treinamento_c[int_contador][int_atributo]), 2);

        }

        g_int_arr_distancias[int_contador][1] = sqrt(int_distancia) ;

        int_contador ++;

    }


    return 0;
}


int fnc_ordenar(void) {
    int int_arr_distancia_armazenada[2][2];
    int int_o = 0, int_i = 0;

    memcpy(g_int_arr_distancias_ordenadas, g_int_arr_distancias, sizeof(g_int_arr_distancias));

    for (int_o = 0; int_o < (TOTAL_REGISTROS_TREINAMENTO * 3); int_o++) {

        for (int_i = 0; int_i < (((TOTAL_REGISTROS_TREINAMENTO * 3) / 2) -1); int_i++) {

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

        for (int_i = 0; int_i < (((TOTAL_REGISTROS_TREINAMENTO * 3)/ 2)); int_i++) {

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
    int int_arr_proximos[TOTAL_REGISTROS_TREINAMENTO * 3][2] = {0};
    int int_k_proximor_maior_total = 0;


    int_k_proximos_posicao = 0;
    int_k_proximor_maior_total = 0;
    bln_achou = 0;

    for (int_a =0; int_a < KNN_K; int_a++) {

        bln_achou = 0;
        int_classe = g_int_arr_distancias_ordenadas[int_a][0];

        for (int_b = 0; int_b < TOTAL_REGISTROS_TREINAMENTO * 3; int_b++) {

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

    for (int_a = 0; int_a < (TOTAL_REGISTROS_TREINAMENTO * 3); int_a++) {

        if (int_arr_proximos[int_a][1] > int_k_proximor_maior_total) {

            int_k_proximor_maior_total = int_arr_proximos[int_a][1];
            int_classe = int_arr_proximos[int_a][0];


        }

    }

    g_int_classe_prevista = int_classe;
    //printf ("Classe prevista %d\n\n", int_classe);

    return 0;

}
