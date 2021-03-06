# Algortihmique d'Aide à la Décision

  Par Clément Guilbert
## Dossier n°2 : Mot le plus long

### Introduction

Afin de poursuivre dans l'adaptation de solutions pour le jeux "des chiffres et des lettres", j'ai décidé d'adapter un solveur de l'épreuve du mot le plus log. Dans celle-ci, les candidats reçoivent une série de lettres à partir desquelles ils doivent former le mot le plus long possible. Il est possible de ne pas utiliser toutes les lettres.

Cet algorithme sera également fait en C et proposera soit de tirer aléatoirement un nombre équitable de voyelles et de consonnes, soit de laisser le joueur entrer ses propres lettres.

### Principe
L'idée principale d'un tel algorithme est d'effectuer récursivement les opérations possibles tant qu'elles améliorent l'écart au résultat. En parcourant plusieurs arbres récursif, on peut ainsi favoriser des branches par rapport à d'autres et conserver la solution optimale.
Pour résoudre ce problème, j'ai choisi de parcourir un dictionnaire de mots français en vérifiant pour chaque mot si l'une des lettres proposés correspond à la première. Si ce n'est pas le cas, la boucle s'arrête et passe au mot suivant, sinon, elle continue en excluant la lettre. Si le mot est entièrement faisable avec la liste de lettres proposée, il est sauvegardé ainsi que sa longueur, à condition qu'il soit plus long que la solution précédente s'il y en a une.

### Code
#### Main.c
``` C
#include "genmot.h"

int main(int argc, char *argv[])
{
  /**
    Allocation de déclaration des variables
  */
  int params = 12, p = 0, i = 0, choix = 1;

  /**
   *  Choix entre la génération aléatoire et la soumission de lettres par l'utilisateur 
  */
  printf("Voulez vous entrer vos propres lettres ou les générer aléatoirement? (1 pour entrer / 2 pour générer)");
  scanf("%d",&choix);
  while ((getchar()) != '\n'); //Vide le buffer


  char * termeini = (char *) malloc(params * sizeof(char));
  char * mot = (char *) malloc(MAX_LEN * sizeof(char));
  ssize_t read;
  solution motLePlusLong;
  motLePlusLong.mot = "";
  motLePlusLong.longueur = 0;
  
  if(choix == 1)
  {
    params = lettresUtilisateurs(termeini);
  }
  else
  {
    printf("Entrez la graine (nombre entier) souhaitée pour le générateur aléatoire.");
    scanf("%d",&choix);
    termeini=genLettres(params, choix);
  }

  /**
    Affichage des lettres reçues
  */
  for(i=0;i<params;i++)  
    printf("%c\n", termeini[i]);

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
  printf("Resultat : \n%s \nLongueur : %d \n", motLePlusLong.mot, motLePlusLong.longueur);
	
  /**
   * Fermeture du fichier et libération des allocations mémoires
  */
  fclose(file);
  free(termeini);
  free(mot);
  free(motLePlusLong.mot);
  return(0);
}

```
#### genmot.h
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Period parameters */  
#define N 624
#define M 397
#define MAX_LEN 128
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s);

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void);

/* generates a random POSITIVE number on [0,0xffffffff]-interval */
unsigned long genrand_int32_pos(void);

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void);
/* generates a random number on [0,1]-real-interval */
double genrand_real1(void);

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void);

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) ;
/* These real versions are due to Isaku Wada, 2002/01/09 added */

typedef struct
{
  char * mot;
  int longueur;
} solution;

char * genLettres(int n, int seed);

int utiliseLettre(char * mot, char * lettres, int params, int profondeur, solution * s);

int lettresUtilisateurs(char * lettres);
```
#### genmot.c
```c
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
    char * res = calloc ( n + 1 ,sizeof(char) );
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
    Retourne 0 si la solution est recevable
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
  Retourne le nombre de lettres entrées
*/
int lettresUtilisateurs(char * lettres)
{
  printf("\nEntrez les lettres que vous voulez tester :");
  fgets(lettres, 100, stdin); 
  return strlen(lettres); 
}
```

### Tests et Code Review

Après les tests d'Aymeric, j'ai pu mettre en évidence certains problèmes, notamment l'allocation des lettres lors d'une génération aléatoire. Aymeric avait fait remarqué qu'une variable pouvait être non initialisée dans le strcpy d'utiliseLettres. Il s'agissait en fait de *lettres, pas temp, qui pouvait être nul depuis la génération. En utilisant calloc dans genLettres, le comportement non initialisé est pris en charge.
J'ai également modifié un peu le menu utilsateur en le rendant plus explicite.
