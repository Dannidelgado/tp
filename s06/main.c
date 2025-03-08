#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pantalla.h"
/*
#include
#define
#struct
#typedef
#funciones
*/
// w = ancho y h = altura
int dentro_rectangulo ( int x, int y, int w, int h, int px, int py ) {
    // x <= px; px < (x + w)
    // y <= py; py < (y + h)
    if (x <= px && px < (x + w) && y <= py && py < (y + h)) {
        return 1;
    }
    else {
        return 0;
    }
}

double distancia_punto_punto ( double x1, double y1, double x2, double y2 ) {
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

int solape_circunferencias( int x1, int y1, int r1, int x2, int y2, int r2 ) {
    return r1 + r2 > distancia_punto_punto(x1,y1,x2,y2);
}

int solape_rectangulos( int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2 ) {
    if ( x1 + w1 < x2 || x1 > x2 + w2 || y1 > y2 + h2 || y1 + h1 < y2) {
        return 0;
    } else {
        return 1;
    }

}

struct EnemigoRep {
        int xE;
        int yE;
        int velocidadEx;
        int velocidadEy;
        int wE;
        int hE;
    };
struct PERSONAJE {
    int x;
    int y;
    int velocidad;
    int w;
    int h;
};

struct BalaRep {
    double x;
    double y;
    double velocidadBalax;
    double velocidadBalay;
    int w;
    int h;
    Imagen img;

};

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

typedef struct BalaRep * Bala;

Bala crea_bala (double x, double y, double vx, double vy, int w, int h, Imagen img[]) {
    Bala b = malloc(sizeof(struct BalaRep));
    b->x = x;
    b->y = y;
    b->w = w;
    b->h = h;
    b->velocidadBalax = vx;
    b->velocidadBalay = vy;
    b->img = img[rand() % 3];

    return b;
}

void libera_bala( Bala b ) {
    free(b);
}

void mueve_bala( Bala b ) {
    b->x = b->x + b->velocidadBalax;
    b->y = b->y + b->velocidadBalay;
}

void dibuja_bala( Bala b ){
    dibuja_imagen(b->img,b->x,b->y,b->w,b->h);
}

double get_x_bala( Bala b ) {
    return b->x;
}

double get_y_bala( Bala b ) {
    return b->y;
}

int colision_bala( Bala b, double x, double y, double w, double h ) {
    if (solape_rectangulos(x, y, w, h, b->x, b->y, b->w,b->h)) {
          return 1;
        } else {
            return 0;
        }
}

int colision_enemigos_bala(struct EnemigoRep array[], int n, Bala b) {
    for (int i = 0; i < n; i++) {
        if (solape_rectangulos(b->x, b->y, b->w,b->h, array[i].xE,array[i].yE, array[i].wE,array[i].hE)) {
            array[i] = array[n - 1];
            return 1;
        }
    }
    return 0;
}

int main (int argc, char *argv[]) {

    crea_pantalla("Ejemplo 3", 800,480);
    struct PERSONAJE personaje;
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

    struct EnemigoRep enemigo[10];
    for (int i = 0; i < 10; i++) {
        enemigo[i].wE = 40;
        enemigo[i].hE = 40;
        enemigo[i].xE = rand() % (800 - enemigo[i].wE);
        enemigo[i].yE = rand() % (480 - enemigo[i].hE);
        enemigo[i].velocidadEx = (rand() % 2) ? 3 : -3;
        enemigo[i].velocidadEy = (rand() % 2) ? 3 : -3;
        /*
        if (enemigo[i].xE == personaje.x || enemigo[i].yE == personaje.y) {
            enemigo[i].xE = rand() % (800 - enemigo[i].wE);
            enemigo[i].yE = rand() % (480 - enemigo[i].hE);
        }
        */
    }
    Imagen balas[3];
    balas[0] = lee_imagen("alonso\\blandas.bmp",1);
    balas[1] = lee_imagen("alonso\\medias.bmp",1);
    balas[2] = lee_imagen("alonso\\duras.bmp",1);
    Imagen Alo = lee_imagen("alonso\\fernando2.bmp",1);
    Imagen Fia = lee_imagen("alonso\\fia3.bmp",0);
    Imagen pista = lee_imagen("alonso\\pista.bmp",0);
    Imagen Tt = lee_imagen("alonso\\33.bmp",0);

    Bala b = NULL;
    int terminar = 0;
    color_trazo(255,255,255,255);

    FILE * fp = NULL;



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
        if (tecla_pulsada(SDL_SCANCODE_RIGHT)) {
            b = crea_bala(personaje.x,personaje.y,9.0,0.0,30,30,balas);
        }
        if (tecla_pulsada(SDL_SCANCODE_LEFT)) {
            b = crea_bala(personaje.x,personaje.y,-9.0,0.0,30,30,balas);
        }
        if (tecla_pulsada(SDL_SCANCODE_UP)) {
            b = crea_bala(personaje.x,personaje.y,0.0,-9.0,30,30,balas);
        }
        if (tecla_pulsada(SDL_SCANCODE_DOWN)) {
            b = crea_bala(personaje.x,personaje.y,0.0,9.0,30,30,balas);
        }





        if (contador % 50 == 0 && n < 10) {
                n += 1;
            }




        if (solape_rectangulos(personaje.x, personaje.y, personaje.w,personaje.h, xt,yt, 40,40)) {
            xt = rand() % 760;
            yt = rand() % 440;
            personaje.velocidad += 1;
            punto += 1;
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



        mueve_enemigos(enemigo, n );

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


        if (vidas == 0) {
            terminar = 1;
        }




        dibuja_imagen(pista,0,0,800,480);

        dibuja_texto(mensajeVida,15,10);
        dibuja_texto(mensajePunto,15,30);

        if (b != NULL) {
            dibuja_bala(b);
            get_x_bala(b);
            get_y_bala(b);
            mueve_bala(b);

            if (colision_enemigos_bala(enemigo, n, b)) {
                n -= 1;
                libera_bala(b);
                b = NULL;
            } else if (b->x > (800 - b->w) || b->x < 0 || b->y < 0 || b->y > (480 - b->h)) {
                libera_bala(b);
                b = NULL;
            }


        }


        dibuja_imagen(Alo,personaje.x,personaje.y,personaje.w,personaje.h);
        dibuja_imagen(Tt,xt,yt, 40, 40);
        dibuja_enemigos(enemigo,n, Fia);
        actualiza_pantalla ();
        espera(40);
        contador++;
    }

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
    libera_pantalla();
    libera_bala(b);
    return 0;

return 0;

}
