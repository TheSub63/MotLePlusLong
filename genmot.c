#include "genmot.h"

/*
    Genère un tableau de n lettres aléatoires avec la graine fournie a init_genrand()
*/
char * genLettres(int n, int seed)
{
    /**
        Déclaration des tableaux de consonnes et de voyelles
    */
    char consonnes[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    char voyelles[6] = {'a','e','i','o','u','y'};

    /**
        Initialisation du générateur aléatoire avec une graine particulière
    */
    init_genrand(seed);
    char * res = (char *) malloc (sizeof(char) * (n+1));
    if(res==NULL) exit(1);
    /**
        Tirage d'un nombre équivalent de consonnes et de voyelles
    */
    for(int i=0;i<n;i++) {
        res[i] = consonnes[genrand_int32_pos()%20];
        i++;
        if(i<n)
            res[i] = voyelles[genrand_int32_pos()%6];
    }
    return res;
}

/**
    Vérifie chaque mot récursivement afin de trouver le plus long
    Paramètres :
      - mot : le mot à vérifier
      - lettres : les lettres à utiliser
      - params : le nombre de lettres
      - profondeur : indique l'itération de l'algorithme pour un mot
      - s : meilleure solution actuelle
*/
int utiliseLettre(char * mot, char * lettres, int params, int profondeur, solution * s)
{
  /*
    Déclaration des paramètres et stockage des lettres disponibles dans une chaine temporaire
  */
  int i=0, res = 1;
  int taille = 100;
  taille = params+1;
  char temp[taille];
  strcpy(temp,lettres);

  /*
    Boucle de vérification de chaque lettre à la lettre du mot correspondant à l'index de profondeur
    Tant qu'il reste des lettres, que la lettre n'est pas trouvée ou que le mot n'est pas trouvé
  */
  while(i < params && res == 1)
  {
    if(mot[0] == '\0')
    {
      /*
        Si le mot est terminé, on arrête la boucle et si le mot actuel est plus long que la solution, on renvoie res à 0
      */
      if(profondeur>s->longueur) 
      {
        res = 0;
        params = 0;
      } 
    }

    if(mot[0] == temp[i]) 
    {
      res = 0;
    }
    i++;
  }

  /*
    Si la lettre correspond
  */
  if(res == 0)
  {
    /*
      On enlève la lettre de la variable temporaire
    */
    for(i=i-1; i<params-1; i++)
      temp[i] = temp[i + 1];

    /*
      Si le mot n'est pas terminé, la fonction continue, sinon, le mot est une nouvelle solution
    */
    if(params>1)
    {
      res = utiliseLettre(mot + 1, temp, params - 1, profondeur + 1, s);
    }
  }
  return res; 
}

/**
    Fonction servant à retirer les accents d'un mot => Problème à la lecture
*/
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


/*
  Initialise la liste de lettres avec celles proposées par l'utilisateur
*/
int lettresUtilisateurs(char * lettres)
{
  printf("\nEntrez les lettres que vous voulez tester :");
  fgets(lettres, 100, stdin); 
  return strlen(lettres); 
}