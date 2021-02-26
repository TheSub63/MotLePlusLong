#include "genmot.h"

//VALGRIND + MENU INPUT LETTRES

int main(int argc, char *argv[])
{
  /**
    Allocation de déclaration des variables
  */
  int params = 10, p = 0, i = 0;
  char * termeini = (char *) malloc(params * sizeof(char));
  char * mot = (char *) malloc(params * sizeof(char));
  char ** dico = (char **) malloc (100 * sizeof(char *));
  ssize_t read;
  solution motLePlusLong;
  motLePlusLong.mot = "";
  motLePlusLong.longueur = 0;
  //termeini=genLettres(params);
  params = lettresUtilisateurs(termeini);
  printf("params : %d \n", params);
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
      //printf("Ok");
      motLePlusLong.mot = (char *) malloc(params * sizeof(char));
      strcpy(motLePlusLong.mot, mot);
      motLePlusLong.longueur = strlen(mot);
    }
    i++;
  }
  /**
    Affichage de la solution
  */
  printf("Resultat : \n%s \nLongueur : %d", motLePlusLong.mot, motLePlusLong.longueur);
	return(0);
}