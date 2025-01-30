#include <stdio.h>
#include <math.h>
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

int main2 () {

    if (dentro_rectangulo(0,0,10,20,1,2) != 1) {
        printf("Error 1\n");
    }

    printf("%f\n", distancia_punto_punto(0.0,0.0,10.0,0.0));

    if (solape_circunferencias(0,0, 7, 10,0, 4) != 1) {
        printf("Error");
    }

    if (solape_rectangulos(21,0, 20,10, 19,7, 1,4) != 0) {
        printf("Error");
    }


}
