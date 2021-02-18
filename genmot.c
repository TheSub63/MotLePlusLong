#include "genmot.h"


/*
    Genère un tableau de n lettres aléatoires avec la graine fournie a init_genrand()
*/
char * genLettres(int n)
{
    char consonnes[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    char voyelles[6] = {'a','e','i','o','u','y'};
    init_genrand(21);
    char * res = (char *) malloc (sizeof(char) * n);
    if(res==NULL) exit(1);
    for(int i=0;i<n;i++) {
        res[i] = consonnes[genrand_int32_pos()%20];
        i++;
        if(i<n)
            res[i] = voyelles[genrand_int32_pos()%6];
    }
    return res;
}
