#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pantalla.h"
#include "sesion02.h"
#include "Bala.h"
/*
#include
#define
#struct
#typedef
#funciones
*/
///=====================================/* Struct */==================================================================================
///===================================================================================================================================
///===================================================================================================================================
struct EnemigoRep {
        int xE;
        int yE;
        int velocidadEx;
        int velocidadEy;
        int wE;
        int hE;
};
struct EnemigoRep enemigo[10];

struct PERSONAJE {
    int x;
    int y;
    int velocidad;
    int w;
    int h;
};
struct PERSONAJE personaje;

struct Nodo {
    Bala elem;
    struct Nodo * sig;
};
typedef struct Nodo * NodoPtr;
///===================================================================================================================================
///===================================================================================================================================
///=====================================/* Fin Struct */==============================================================================

///=========================/* FUNCIONES */===========================================================================================
///===================================================================================================================================
///===================================================================================================================================

///-|Funciones lista_balas|-----------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------
NodoPtr crea_lista_balas() {
    NodoPtr cabecera = malloc(sizeof(struct Nodo));
    cabecera -> elem = NULL;
    cabecera -> sig = NULL;
    return cabecera;
}

void inserta_lista_balas ( NodoPtr cabecera, Bala b ) {
    NodoPtr auxiliar = cabecera;
    while (auxiliar -> sig != NULL && auxiliar -> sig -> elem != b) {
        auxiliar = auxiliar -> sig;
    }
    if (auxiliar -> sig == NULL) {
        NodoPtr nuevo = malloc(sizeof(struct Nodo)); /*insertar por el principio*/
        nuevo->elem = b;
        nuevo -> sig = cabecera -> sig;
        cabecera -> sig = nuevo;
    }
}
void libera_lista_balas ( NodoPtr cabecera ) {
    NodoPtr actual = cabecera->sig;
    while (actual != NULL) {
        NodoPtr temp = actual;
        actual = actual->sig;
        free(temp->elem);
        free(temp);
    }
    cabecera->sig = NULL;
}
void mueve_lista_balas ( NodoPtr cabecera ) {
    NodoPtr actual = cabecera->sig;
    NodoPtr anterior = cabecera;

    while (actual != NULL) {

        mueve_bala(actual->elem);

        /*Si la bala sale de la pantalla, eliminarla de la lista*/
        if (get_x_bala(actual->elem) > 770 || get_x_bala(actual->elem) < 0 || get_y_bala(actual->elem) < 0 || get_y_bala(actual->elem) > 450) {
            NodoPtr temp = actual;
            anterior->sig = actual->sig;
            actual = actual->sig;
            free(temp->elem);
            free(temp);
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
}
void dibuja_lista_balas ( NodoPtr cabecera ) {
    NodoPtr aux = cabecera->sig;
    while (aux != NULL) {
        dibuja_bala(aux->elem);
        aux = aux->sig;
    }
}
///-|Fin funciones lista_balas|-------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------

///-|Funciones enemigo|---------------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------
void mueve_enemigos( struct EnemigoRep array[], int n ) {
    for (int i = 0; i < n; i++) {
        array[i].xE = array[i].xE + array[i].velocidadEx;
        array[i].yE = array[i].yE + array[i].velocidadEy;
            if (array[i].xE > 760) {
                array[i].xE = 760;
                array[i].velocidadEx = -5;
            }
            if (array[i].xE < 0) {
                array[i].xE = 0;
                array[i].velocidadEx = 5;
            }
            if (array[i].yE < 0) {
                array[i].yE = 0;
                array[i].velocidadEy = 5;
            }
            if (array[i].yE > 430) {
                array[i].yE = 430;
                array[i].velocidadEy = -5;
            }
    }
}

void dibuja_enemigos( struct EnemigoRep array[], int n , Imagen x) {
    for (int i = 0; i < n; i++) {
        dibuja_imagen(x,array[i].xE,array[i].yE,array[i].hE,array[i].wE);
    }
}

int colision_enemigos_objeto( struct EnemigoRep array[], int n, int x, int y, int w, int h) {
    for (int i = 0; i < n; i++) {
        if (solape_rectangulos(x, y, w,h, array[i].xE,array[i].yE, array[i].wE,array[i].hE)) {
          return 1;
        }
    }
    return 0;


}
///-|Fin funciones enemigo|-----------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------

///-|Función bala|--------------------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------

int colision_enemigos_bala(struct EnemigoRep array[], int n, Bala b) {
    for (int i = 0; i < n; i++) {
        colision_bala(b,array[i].xE,array[i].yE, array[i].wE,array[i].hE);
    }
    return 0;
}
///-|Fin función bala|----------------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------

///-|Funcines colisión_bala|----------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------
int colision_lista_balas(NodoPtr cabecera, double x, double y, double w, double h) {
    NodoPtr aux = cabecera->sig;
    while (aux != NULL) {
       if (colision_bala(aux->elem,x,y,w,h)) {
            return 1;
       }
        aux = aux->sig;
    }
    return 0;
}

int colision_enemigos_lista_balas(struct EnemigoRep array[], int n, NodoPtr cabecera) {
    int cont = 0;
        for (int i = 0; i < n; i++) {
           if (colision_lista_balas(cabecera, array[i].xE, array[i].yE, array[i].wE, array[i].hE)) {
                cont++;
                array[i] = array[n - 1];
           }
        }
    return cont;
}
///-|Fin funcines colisión_bala|------------------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------------------------------------------

///===================================================================================================================================
///===================================================================================================================================
///=====================================/* Fin funciones */===========================================================================

///=====================================/* Main */====================================================================================
///===================================================================================================================================
///===================================================================================================================================
int main (int argc, char *argv[]) {

    ///-|Variables|-------------------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------------------------------------------------------------------------------------
    crea_pantalla("Ejemplo 3", 800,480);
    personaje.x = rand() % 760;
    personaje.y = rand() % 430;
    personaje.h = 60;
    personaje.w = 50;
    personaje.velocidad = 5;
    int xt = rand() % 760;
    int yt = rand() % 440;
    int gestionPunto = 0;
    int punto = 0;
    int vidas = 3;
    int n = 3;
    int contador = 0;
    int frecBala = 0;

    for (int i = 0; i < 10; i++) {
        /* Inicializamos los valores del array enemigo */
        enemigo[i].wE = 40;
        enemigo[i].hE = 40;
        enemigo[i].xE = rand() % (800 - enemigo[i].wE);
        enemigo[i].yE = rand() % (480 - enemigo[i].hE);
        enemigo[i].velocidadEx = (rand() % 2) ? 3 : -3;
        enemigo[i].velocidadEy = (rand() % 2) ? 3 : -3;
    }

    Imagen balas[3];
    balas[0] = lee_imagen("alonso\\blandas.bmp",1);
    balas[1] = lee_imagen("alonso\\medias.bmp",1);
    balas[2] = lee_imagen("alonso\\duras.bmp",1);
    Imagen Alo = lee_imagen("alonso\\fernando2.bmp",1);
    Imagen Fia = lee_imagen("alonso\\fia3.bmp",0);
    Imagen pista = lee_imagen("alonso\\pista.bmp",0);
    Imagen Tt = lee_imagen("alonso\\numero01.bmp",0);


    int terminar = 0;
    color_trazo(255,255,255,255);

    FILE * fp = NULL;
    Bala b = NULL;
    NodoPtr c = crea_lista_balas();
    ///-|Fin variables|---------------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------------------------------------------------------------------------------------

    ///-|While|-----------------------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------------------------------------------------------------------------------------
    while ( pantalla_activa() && !terminar ) {
        if (tecla_pulsada(SDL_SCANCODE_D)) {
            personaje.x = personaje.x + personaje.velocidad;
        }
        if (tecla_pulsada(SDL_SCANCODE_A)) {
            personaje.x = personaje.x - personaje.velocidad;
        }
        if (tecla_pulsada(SDL_SCANCODE_W)) {
            personaje.y = personaje.y - personaje.velocidad;
        }
        if (tecla_pulsada(SDL_SCANCODE_S)) {
            personaje.y = personaje.y + personaje.velocidad;
        }
        if (tecla_pulsada(SDL_SCANCODE_RIGHT) && frecBala == 0) {
            b = crea_bala(personaje.x,personaje.y,9.0,0.0,30,30,balas);
            inserta_lista_balas (c, b);
            frecBala = 5;
        }
        if (tecla_pulsada(SDL_SCANCODE_LEFT) && frecBala == 0) {
            b = crea_bala(personaje.x,personaje.y,-9.0,0.0,30,30,balas);
            inserta_lista_balas (c, b);
            frecBala = 5;
        }
        if (tecla_pulsada(SDL_SCANCODE_UP) && frecBala == 0) {
            b = crea_bala(personaje.x,personaje.y,0.0,-9.0,30,30,balas);
            inserta_lista_balas (c, b);
            frecBala = 5;
        }
        if (tecla_pulsada(SDL_SCANCODE_DOWN) && frecBala == 0) {
            b = crea_bala(personaje.x,personaje.y,0.0,9.0,30,30,balas);
            inserta_lista_balas (c, b);
            frecBala = 5;
        }


        if (contador % 50 == 0 && n < 10) {
                n += 1;
                if (enemigo[n].xE == personaje.x && enemigo[n].yE == personaje.y) {
                    enemigo[n].xE = rand() % (800 - enemigo[n].wE);
                    enemigo[n].yE = rand() % (480 - enemigo[n].hE);
                    /* Este condicional nos asegura que si la posición del nuevo enemigo
                    que se crea es igual a la del personaje, genere otra. Para evitar que
                    mate al personaje justo al salir */
                }
            }
        mueve_enemigos(enemigo, n );

        if (solape_rectangulos(personaje.x, personaje.y, personaje.w,personaje.h, xt,yt, 40,40)) {
            xt = rand() % 760;
            yt = rand() % 440;
            personaje.velocidad += 1;
            punto += 1;
            /* Si Alonso coge el tesoro este cambia de posición y Alonso aumenta la velocidad y
             los puntos */
        }

        if (personaje.x > (800 - personaje.w)) {
            personaje.x = (800 - personaje.w);
        }
        if (personaje.x < 0) {
            personaje.x = 0;
        }
        if (personaje.y > (480 - personaje.h)) {
            personaje.y = (480 - personaje.h);
        }
        if (personaje.y < 0) {
            personaje.y = 0;
        }

        if (colision_enemigos_objeto(enemigo, n, personaje.x, personaje.y, personaje.w, personaje.h)) {
            vidas -= 1;
            personaje.velocidad -= 1;
            personaje.x = rand() % (800 - personaje.w);
            personaje.y = rand() % (480 - personaje.h);
        }


        char mensajeVida[20];
        sprintf(mensajeVida,"Vidas: %d\n", vidas );
        char mensajePunto[20];
        sprintf(mensajePunto,"Puntos: %d\n", punto );

        dibuja_imagen(pista,0,0,800,480);

        if (b != NULL) {
            dibuja_lista_balas(c);
            mueve_lista_balas(c);


            if (colision_enemigos_lista_balas(enemigo, n, c) > 0) {
                n -= colision_enemigos_lista_balas(enemigo, n, c);

            }

        }

        dibuja_texto(mensajeVida,15,10);
        dibuja_texto(mensajePunto,15,30);
        dibuja_imagen(Alo,personaje.x,personaje.y,personaje.w,personaje.h);
        dibuja_imagen(Tt,xt,yt, 40, 40);
        dibuja_enemigos(enemigo,n, Fia);
        actualiza_pantalla ();
        espera(40);
        contador++;

        if (frecBala > 0) {
            frecBala -= 1;
        }

        if (vidas == 0 || punto == 33) {
            terminar = 1;
        }

    }
    ///-|Fin while|-------------------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------------------------------------------------------------------------------------

    fp = fopen("records.txt", "r");
    int record = fscanf(fp, "%d", &gestionPunto);
    fclose(fp);
    if (record != 1) {
        fp = fopen("records.txt", "w");
        fprintf(fp,"%d\n", punto);
        fclose(fp);
        } else {
            fp = fopen("records.txt", "w");
            if (gestionPunto < punto) {
            fprintf(fp,"%d\n", punto);

            } else {
                fprintf(fp,"%d\n", gestionPunto);
            }
            fclose(fp);
        }

    libera_imagen(Alo);
    libera_imagen(Tt);
    libera_imagen(Fia);
    libera_imagen(pista);
    libera_lista_balas(c);
    libera_pantalla();


return 0;

}
///===================================================================================================================================
///===================================================================================================================================
///=====================================/* Fin main */================================================================================
