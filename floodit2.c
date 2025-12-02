/* Fichier modèle pour l'utilisation de la SDL2 
   Ne pas oublier l'édition des liens avec les bonnes bibliothèques 
    -lSDL2 -lSDL2_image -lSDL2_ttf 
   cela suffit pour ada et les machines virtuelles de l'ISIMA 
   pour vos installation, il faudra peut etre ajuster les options suivantes :
   -I/opt/local/include -L/opt/local/lib 

*/
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

// type utilisable pour definir une couleur de type RVBA
typedef struct palette_t {
    Uint8 r; 
    Uint8 g;
    Uint8 b;
    Uint8 a; 
} palette_t;

/* VARIABLES GLOBALES */

SDL_Window   * window   = NULL; // fenetre utilisee par le programme
SDL_Renderer * renderer = NULL; // moteur de rendu SDL
SDL_Texture  * logo     = NULL; // image chargee
TTF_Font     * font1    = NULL; // polices de caracteres
TTF_Font     * font2    = NULL;
int            width    = 870;  // largeur de la fenetre
int            height   = 480;  // hauteur de la fenetre


/*
   Cette fonction est appelee des qu'il est necessaire de dessiner la fenetre
*/
void dessinerFenetre()
{

   SDL_Rect rect;

   /* on prépare/efface le renderer */
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderClear(renderer);

   /* dessiner en blanc */
   SDL_SetRenderDrawColor(renderer, 255, 150, 255, 255);
   rect.x = rect.y = 0;
   rect.w = rect.h = 600;
   SDL_RenderFillRect(renderer, &rect );

   /* afficher le renderer dans la fenetre */
   SDL_RenderPresent(renderer);
}



int main(int argc, char ** argv) {

    int            running = 1;
    SDL_Event      event;
    bool           img_init   = true;
    bool           ttf_init   = true;
    
    /* ********************************************************************* */
    /* SECTION DES INITIALISATIONS                                           */
    /* ********************************************************************* */
 
    // Note : je n'ai pas envie d'empiler les if/else imbriques
    // first of all : initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)  /* SDL_INIT_EVERYTHING */ {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;   
    }

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SLD_Log() */
    }

    SDL_Delay(500);

    // Initialisation de la bibliotheque SDL2_image
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: jpg et/ou png non supportes!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        img_init = false;   
    }

    // Initialisation de la bibliotheque SDL2_ttf
    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
        ttf_init = false;
    }

    if ((img_init) && (ttf_init)) {
        window = SDL_CreateWindow("Exemple SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
                                    //SDL_WINDOW_FULLSCREEN ); 
                                     SDL_WINDOW_SHOWN |  SDL_WINDOW_RESIZABLE);
        SDL_Delay(500);
    }
    
    if (window == 0) {
        fprintf(stderr, "Erreur a la creation de la fenetre : %s\n", SDL_GetError()); 
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /* | SDL_RENDERER_PRESENTVSYNC */
        if (renderer == 0) {
            fprintf(stderr, "Erreur de creation d'un renderer : %s\n", SDL_GetError());
        }
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    int compteur = 1000;
    while (compteur>0)
    {
        while (SDL_PollEvent(&event))
        {
	        dessinerFenetre();
        }
        --compteur;
        SDL_Delay(10);   
    }

    SDL_DestroyRenderer(renderer);

    if ((window) && (renderer)) {
        // utilisation de la transparence ?
        // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // fenetre et moteur de rendu operationnels = chargement des ressources

        font1 = TTF_OpenFont("chlorinar.regular.ttf", 72 ); 
        font2 = TTF_OpenFont("fake.receipt.ttf", 72 ); 

        if ((font1 == 0) || (font2==0)) {
            fprintf(stderr, "Erreur d'initialisation police : %s\n", TTF_GetError());
            fprintf(stderr, "Avez-vous pense a mettre dans le repertoire le fichier de la police\n"); 
        }
        SDL_Surface *image = NULL;
        image=IMG_Load("loic.png");

        if(!image) {
            printf("IMG_Load: %s\n", IMG_GetError());
        } else {
            logo = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
        }
    }

    if (font1 && font2 && logo) {
    
        /* ********************************************************************* */
        /* BOUCLE DES EVENEMENTS                                                 */
        /* ********************************************************************* */
    
        while (running) {


            while (SDL_PollEvent(&event)) {

                switch(event.type) {
                    case SDL_WINDOWEVENT:
                        printf("window event\n");
                        switch (event.window.event)  {
                            case SDL_WINDOWEVENT_CLOSE:  
                                printf("appui sur la croix\n");
                                break;
                            case SDL_WINDOWEVENT_SIZE_CHANGED:
                                width = event.window.data1;
                                height = event.window.data2;
                                printf("Nouvelle taille : %d %d\n", width, height);
                            default:
                                dessinerFenetre();
                        }   
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                        printf("Clic :%d %d\n", event.button.x, event.button.y);
                        dessinerFenetre();
                        break;
                    case SDL_QUIT : 
                        printf("On quitte\n");    
                        running = 0;
                }
            }
            SDL_Delay(1);
        }
    }

    /* ********************************************************************* */
    /* RENDU DES RESSOURCES                                                  */
    /* ********************************************************************* */

    if (font1) TTF_CloseFont(font1);
    if (font2) TTF_CloseFont(font2);
    if (logo)  SDL_DestroyTexture(logo);
    
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window)   SDL_DestroyWindow(window);

    if (img_init) IMG_Quit();
    if (ttf_init) TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit(); // ouf, on a fini

    return EXIT_SUCCESS;
}
