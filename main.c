#include "genmot.h"

/**

  Enlever les accents
  Pouvoir trouver des mots de longueur < params
  Nettoyer l'usage de dico
  Proposer un menu permettant de saisir consonnes/voyelles jusqu'à input  --> Retour en direct
*/

void menuConsonnesVoyelles(char * lettres)
{
  int c = 0, v = 0;
  char input;
  printf("Tapez c pour une consonne, v pour une voyelle et q pour lancer l'algorithme.");
  while(scanf("%c",&input)==1)
  {
    if(input == 'c') c++;
    else if(input == 'v') v++;
    else if(input == 'q') break;
  }
  //lettres = genLettres(c, v);
}

typedef struct
{
  char * mot;
  int longueur;
} solution;

int utiliseLettre(char * dico, char * lettres, int params, int profondeur, solution * s)
{
  int i=0, j, res = 1;
  char * temp = (char *) malloc(params-1);
  strcpy(temp, lettres);
  //printf("%s \n",lettres);
  //printf("Verif mot %s contient les lettres %s nb de lettres %d \n", dico, lettres, params);
  while(i < params && res == 1)
  {
    printf("test");
    //printf("Lettre %c == lettre %c ?\n", dico[0], lettres[i]);
    if(dico[0] == '\0')
    {
      printf("Fin du mot");
      if(profondeur>s->longueur) 
      {
        res = 0;
        params = 0;
      } 
    }
    if(dico[0] == temp[i]) 
    {
      res = 0;
      //printf("Le mot %s contient la lettre %c \n", dico, temp[i]);
    }
    //printf("i: %d params : %d res : %d", i, params, res);
    i++;
  }
  //printf("fin boucle");
  if(res == 0)
  {
    //printf("%s \n",lettres);
    for(i=i-1; i<params-1; i++)
      temp[i] = temp[i + 1];
    //printf("%s \n",lettres);

    if(params>1)
    {
      //printf("params !=0");
      printf("%s %s %d\n", dico+1, temp, params -1);
      res = utiliseLettre(dico + 1, temp, params - 1, profondeur + 1, s);
    }
  }
  //printf("fin récu");
  //printf("res : %d", res);
  return res; 
}

int main(int argc, char *argv[])
{
  int i;
  int params = 6, p = 0;
  char * termeini;
  char terme[16][16];
  char * mot;
  char ** dico = (char **) malloc (100 * sizeof(char *));
  size_t len = 0;
  ssize_t read;
  termeini=genLettres(params);
  termeini = "testab";
  //printf("Liste de lettres : \n");
  for(i=0;i<params;i++)  
    printf("%c\n", termeini[i]);

  for(i=0;i<params;i++)  // initialise terme[][]
    terme[params][i]=termeini[i];


	/*testerCalcul(params);

  afficheSolution(meilleurcalcul);

	free(termeini);
  resetSolution();*/

  FILE *file  = fopen("liste_francais_test.txt", "r"); // read only 
           
  // test for files not existing. 
  if (file == NULL ) 
  {   
    //printf("Error! Could not open file\n"); 
    exit(-1);
  }

  solution motLePlusLong;
  motLePlusLong.mot = "";
  motLePlusLong.longueur = 0;

  i=0;
  while ((read = fscanf(file,"%s",mot)) != -1) {
    //printf("%s \n", mot);
    if(!utiliseLettre(mot, termeini, params, p, &motLePlusLong))
    {
      printf("ajout en cours");
      motLePlusLong.mot = (char *) malloc(params);
      strcpy(motLePlusLong.mot, mot);
      motLePlusLong.longueur = strlen(mot);
      printf("ajouté %s \n", mot);
    }
    //printf("netx\n");
    i++;
  } 
  printf("Résultat : \n%s \nLongueur : %d", motLePlusLong.mot, motLePlusLong.longueur);

	return(0);
}