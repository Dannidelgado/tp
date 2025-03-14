#include "Bala.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pantalla.h"
#include "sesion02.h"


struct BalaRep {
    double x;
    double y;
    double velocidadBalax;
    double velocidadBalay;
    int w;
    int h;
    Imagen img;

};


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
