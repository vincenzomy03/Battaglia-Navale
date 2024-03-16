#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#define RIGHE 6   //righe della matrice
#define COLONNE 6   //colonne della matrice
#define NAVI 6    //navi da generare nel campo da gioco
#define TENTATIVI 10    //tentativi per affondare le navi

int campo[RIGHE][COLONNE] = { {0}, {0} };    //dichiaro una matrice e la inizializzo a 0
int i, j;    //variabili globali da utilizzare nei cicli di iterazioni
int campo_gioco;


//dichiarazione funzioni
void generazione_campo ();
void generazione_navi ();
void inserimento_coordinate ();
void mostra_campo ();

int main ()
{

   srand (time (NULL));   //generazione random dei valori
   generazione_navi();    //generazione random delle navi
   inserimento_coordinate ();    //chiamata della funzione per l'inserimento delle coordinate
   mostra_campo ();    //chiamata della funzione per la visualizzazione della matrice

  return 0;
}

//funzione che genera la matrice inizializzata a 0, con la presenza delle navi (1)
void generazione_campo ()
{

  generazione_navi ();
  
}

//funzione che genera randomicamente le navi, posizionandole in posti casuali all'interno della matrice
void generazione_navi ()
{
    int navi_generate;
    
  for (navi_generate = 0; navi_generate < NAVI; navi_generate++)
    {
      do
	{
	  i = rand () % RIGHE;    // vengono selezionati casualmente una
	  j = rand () % COLONNE;  // posizione nella matrice campo
	}
      while (campo[i][j] != 0);
      campo[i][j] = 1;
    }
}

//funzione per l'inserimento delle coordinate nel campo
void inserimento_coordinate ()
{
  char colonna;
  int x, y, punteggio = 0;
  int tentativo = 0, nave_affondata = 0;
  bool posizioni_colpite[RIGHE][COLONNE] = { false };
  bool nave_colpita[RIGHE][COLONNE] = { false };

  printf ("****************BATTAGLIA NAVALE****************\n");
  printf ("****************User Vs Computer****************\n\n");

  do
  {
    printf ("Inserisci le coordinate delle navi nemiche (es. A1): ");
    scanf (" %c%d", &colonna, &y);
    colonna = toupper (colonna);
    x = colonna - 'A';

    if (x < 0 || x >= COLONNE || y < 1 || y > RIGHE)    //condizione che controlla l'insermento delle coordinate
    {
      printf ("Coordinate errate!\n\n");
    }
    else if (posizioni_colpite[y - 1][x] == true)
    {
      printf("Hai già sparato in questa posizione, riprova.\n\n");
    }
    else if(nave_colpita[y - 1][x] == true)
    {
     printf ("Hai già colpito questa nave in questa posizione, riprova.\n\n");
    }
    else if (campo[y - 1][x] == 1)
    {
      printf ("Nave affondata!\n\n");  
      tentativo++;                       
      nave_colpita[y - 1][x] = true; 
      punteggio += 10;                  
      nave_affondata++;                  
    }
    else if (campo[y - 1][x] == 0)
    {
      printf ("Nave non colpita!\n\n");
      tentativo++;
      posizioni_colpite[y - 1][x] = true;
    }
  }while (tentativo < TENTATIVI || nave_affondata == NAVI);    //ciclo che continua fino al termine dei tentativi o delle navi
  
  if (nave_affondata == NAVI)
    {
      printf
	("Partita terminata con %d punti, hai affondato tutte le navi nemiche!\n\n", punteggio);
    }
  else
    {
      printf
	("Partita terminata con %d punti, hai affondato %d nave/i nemiche.\n\n", punteggio, nave_affondata);
    }
}


//funzione che mostra il campo da gioco
void mostra_campo ()
{
  printf ("Ecco il campo dell'avversario: \n\n");
  printf ("\tA\tB\tC\tD\tE\tF\n\n");
  for (i = 0; i < RIGHE; i++)
    {
      printf ("%d\t", i + 1);
      for (j = 0; j < COLONNE; j++)
	{
	  printf ("%d\t", campo[i][j]);
	}
      printf ("\n\n");
    }
}
