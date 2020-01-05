#include "main.h"


int main(int argc, char *argv[])
{

    int     iV1, iV2, iV3, iV4;

    FILE    *file, *fileo;

    file = fopen("Skin_NonSkin.txt", "r");

    if(file  == NULL) {
        perror("Error opening file");
        return(-1);
    }

    fileo = fopen("Skin_NonSkin_normalizado.txt", "w+");

    if(fileo  == NULL) {
        perror("Error opening file");
        return(-1);
    }
    while(fscanf(file, "%d\t%d\t%d\t%d\n", &iV1, &iV2, &iV3, &iV4)==4) {

        printf ("%d\t%d\t%d\t%d\n", iV1, iV2, iV3, iV4);

        fprintf (fileo, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", iV1, iV2, iV3, 0, 0, 0, 0, iV4);


    }


    printf ("CONCLUIDO.\n");

    return 0;
}
