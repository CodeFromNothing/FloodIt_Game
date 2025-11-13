#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define COULEUR 6
#define TAILLE 12


void initialiser(int Grille[TAILLE][TAILLE])
{
    srand(time(0));
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            Grille[i][j] = (rand()%COULEUR);
        }
    }    
}

void afficherGrille(int Grille[TAILLE][TAILLE])
{
    char *couleurs[] = {
        "\033[41m",
        "\033[42m", 
        "\033[43m", 
        "\033[44m", 
        "\033[45m",
        "\033[46m"
    };

    char reset[]= "\033[0m";
    
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            printf("%s  %s", couleurs[Grille[i][j]], reset);
        }
        printf("\n");
    }
    printf("\n");
}

int fin(int Grille[TAILLE][TAILLE])
{
    int r = 1;
    int s = Grille[0][0];
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (s != Grille[i][j])
            {
                r = 0;
                break;
            }
        }
    }
    return r;
}

void remplir(int Grille[TAILLE][TAILLE], int couleur_courant, int couleur_nouvel, int i, int j)
{
    Grille[i][j] = couleur_nouvel;
    if ((Grille[i + 1][j] == couleur_courant) && (i+1 < TAILLE && j < TAILLE))
    {
        remplir(Grille, couleur_courant, couleur_nouvel, i + 1, j);
    }
    if ((Grille[i][j + 1] == couleur_courant) && (i < TAILLE && j+1 < TAILLE))
    {
        remplir(Grille, couleur_courant, couleur_nouvel, i, j + 1);
    }
} 

void main()
{
    int Grille[TAILLE][TAILLE] = {0};
    int count = 0;
    int couleur_nouvel;
    int check;
    int couleur_courant;
    initialiser(Grille);
    afficherGrille(Grille);
    printf("voici le catalogue des couleurs : rouge: 0, vert: 1, jaune: 2, bleu: 3, violet: 4, cyan: 5\n");
    for (int i = 0; i < 23; i++)
    {
        count += 1;
        couleur_courant = Grille[0][0];
        printf("entrer la couleur que vous souhaitez : ");
        scanf("%d", &couleur_nouvel);
        remplir(Grille, couleur_courant, couleur_nouvel, 0, 0);
        couleur_courant = couleur_nouvel;
        afficherGrille(Grille);
        check = fin(Grille);
        if (check == 1)
        {
            printf("felicitations!!");
            break;
        }
        else
        {
            printf("nombre de tentatives : %d\n", i);
        }
        printf("voici le catalogue des couleurs : rouge: 0, vert: 1, jaune: 2, bleu: 3, violet: 4, cyan: 5\n");
    }
    if (count == 23)
    {
        printf("tu as echoue");
    }
}