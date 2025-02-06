#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pantalla.h"
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

int main (int argc, char *argv[]) {

    crea_pantalla("Ejemplo 3", 800,480);
    int xt = rand() % 760;
    int yt = rand() % 440;
    int x = rand() % 730;
    int y = rand() % 420;
    int xE = rand() % 750;
    int yE = rand() % 430;
    int punto = 0;
    int velocidadE = 5;
    int velocidadPersonaje = 5;
    int vidas = 3;
    Imagen Alo = lee_imagen("C:\\Users\\Usuario\\Escritorio\\UM\\1_Curso_2024-2025\\TP\\Practicas_TP\\SS\\s03_new\\alonso\\fernando.bmp",0);
    Imagen Fia = lee_imagen("C:\\Users\\Usuario\\Escritorio\\UM\\1_Curso_2024-2025\\TP\\Practicas_TP\\SS\\s03_new\\alonso\\fia.bmp",0);
    Imagen pista = lee_imagen("C:\\Users\\Usuario\\Escritorio\\UM\\1_Curso_2024-2025\\TP\\Practicas_TP\\SS\\s03_new\\alonso\\pista.bmp",0);
    Imagen Tt = lee_imagen("C:\\Users\\Usuario\\Escritorio\\UM\\1_Curso_2024-2025\\TP\\Practicas_TP\\SS\\s03_new\\alonso\\33.bmp",0);
    while ( pantalla_activa() ) {
        if (tecla_pulsada(SDL_SCANCODE_RIGHT)) {
            x = x + velocidadPersonaje;
        }
        if (tecla_pulsada(SDL_SCANCODE_LEFT)) {
            x = x - velocidadPersonaje;
        }
        if (tecla_pulsada(SDL_SCANCODE_UP)) {
            y = y - velocidadPersonaje;
        }
        if (tecla_pulsada(SDL_SCANCODE_DOWN)) {
            y = y + velocidadPersonaje;
        }
        if (solape_rectangulos(x, y, 70,60, xt,yt, 40,40)) {
            xt = rand() % 760;
            yt = rand() % 440;
            velocidadPersonaje += 1;
            punto += 1;
        }
        if (x > 730) {
            x = 730;
        }
        if (x < 0) {
            x = 0;
        }
        if (y > 420) {
            y = 420;
        }
        if (y < 0) {
            y = 0;
        }
        xE = xE + velocidadE;
        if (xE > 760) {
            xE = 760;
            velocidadE = -5;
        }
        if (xE < 0) {
            xE = 0;
            velocidadE = 5;
        }
        if (solape_rectangulos(x, y, 70,60, xE,yE, 50,50)) {
            vidas -= 1;
            velocidadPersonaje -= 1;
            xE = rand() % 750;
            yE = rand() % 430;
        }
        if (vidas == 0) {
            libera_imagen(Alo);
            libera_pantalla();
        }


        dibuja_imagen(pista,0,0,800,480);

        dibuja_imagen(Alo,x,y,70,60);
        dibuja_imagen(Tt,xt,yt, 40, 40);
        dibuja_imagen(Fia,xE,yE,50,50);
        actualiza_pantalla ();
        espera(40);
    }
    libera_pantalla();
    printf("%d\n", punto);
    return 0;

return 0;

}
