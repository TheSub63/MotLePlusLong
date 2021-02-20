#include "genmot.h"


/*
    Genère un tableau de n lettres aléatoires avec la graine fournie a init_genrand()
*/
char * genLettres(int n)
{
    char consonnes[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    char voyelles[6] = {'a','e','i','o','u','y'};
    init_genrand(25);
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

char * genLettresMenu(int c, int v)
{
    int i = 0;
    char consonnes[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    char voyelles[6] = {'a','e','i','o','u','y'};
    init_genrand(25);
    char * res = (char *) malloc (sizeof(char) * (c+v));
    if(res==NULL) exit(1);
    for(i=0;i<c;i++) {
        res[i] = consonnes[genrand_int32_pos()%20];
        printf("%c\n", res[i]);
    }
    for(i;i<c+v;i++)
    {
        res[i] = voyelles[genrand_int32_pos()%6];
        printf("%c\n", res[i]);
    }
    res[i+1] = '\0';
    return res;
}

char * retirerAccent(char * message)
{
    char * accent = "ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç";
    char * sansAccent = "AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc";
    char * messageCourt;
    int i=0,j=0,k=0,taille;
 
    taille=strlen(message);
 
    for (i=0;i<=taille;i++)
    {
        for(j=0;j<=104;j=j+2)
        {
            if((message[i]==accent[j])&&(message[i+1]==accent[j+1]))
            {
                message[i]=sansAccent[j/2];
                for(k=i+1;k<taille;k++)
                {
                    message[k]=message[k+1];
                }
                char * buf;
                memcpy(buf, message, taille - 1);
                buf[taille] = '\0';
                taille=strlen(message);
            }
        }
    }
 
    return message;
}