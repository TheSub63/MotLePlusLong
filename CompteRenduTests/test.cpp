#define CATCH_CONFIG_MAIN

#include "genmot.h"

#include "catch.hpp"

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


/*
  Initialise la liste de lettres avec celles proposées par l'utilisateur
*/
int lettresUtilisateurs(char * lettres)
{
  printf("\nEntrez les lettres que vous voulez tester :");
  fgets(lettres, 100, stdin); 
  return strlen(lettres); 
}

/*
  Maintest
*/

char * maintest(char * lettres){
    int p =0,i=0,params = strlen(lettres);
    char * termeini = lettres;
  char * mot = (char *) malloc(MAX_LEN * sizeof(char));
  ssize_t read;
  solution motLePlusLong;
  motLePlusLong.mot = (char*) "";
  motLePlusLong.longueur = 0;

  /**
    Ouverture du fichier de mots
  */
  FILE *file  = fopen("liste_francais.txt", "r");
  if (file == NULL ) 
    exit(-1);
  
  /**
    Boucle de lecture de la liste et remplissage de la solution avec le mot trouvé le plus long
  */
  while ((read = fscanf(file,"%s",mot)) != -1) {
    if(!utiliseLettre(mot, termeini, params, p, &motLePlusLong))
    {
      motLePlusLong.mot = (char *) malloc(params * sizeof(char));
      strcpy(motLePlusLong.mot, mot);
      motLePlusLong.longueur = strlen(mot);
    }
    i++;
  }
  /**
    Affichage de la solution
  */
  return(motLePlusLong.mot);
	
  /**
   * Fermeture du fichier et libération des allocations mémoires
  */
  fclose(file);
  free(mot);
  free(motLePlusLong.mot);
}

TEST_CASE("Tests Main"){
    std::string res = maintest((char *) "azertyuiop");
    std::string val = "poireau";
    std::string res2 = maintest((char *) "a r yui p");
    std::string val2 = "pair";
    REQUIRE(res == val);
    REQUIRE(res2 == val2);
}

TEST_CASE("Tests utiliseLettres"){
    solution sol;
    sol.mot = (char *)"";
    sol.longueur = 0;
    int prof = 0;
    char * lettres = (char *) "azertyuiop";
    REQUIRE(utiliseLettre((char *) "partie", lettres, strlen(lettres), prof, &sol) == 0);
    sol.mot = (char *)"partie";
    sol.longueur = 6;
    REQUIRE(utiliseLettre((char *) "paye", lettres, strlen(lettres), prof, &sol) == 1);
    REQUIRE(utiliseLettre((char *) "poireau", lettres, strlen(lettres), prof, &sol) == 0);
}