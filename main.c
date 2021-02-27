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
  printf("Voulez vous entrer vos propres lettres ou les générer aléatoirement? (1/2)");
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
    printf("Entrez la graine souhaitée pour le générateur aléatoire.");
    scanf("%d",&choix);
    termeini=genLettres(params, choix);
  }
  else
    params = lettresUtilisateurs(termeini);

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