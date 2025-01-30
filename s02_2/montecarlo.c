#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double distancia ( double x1, double y1, double x2, double y2 ) {
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

int main () {
    int N;
    double L = 4;
    double radio = L / 2;
    double x,y; // punto x e y

    printf("Introduzca el número de puntos a generar: ");
    scanf("%d", &N);

    srand(time(NULL));

    int c = 0;
    for (int i = 0; i < N; i++) {
        x = (double)rand() / RAND_MAX * L - radio;
        y = (double)rand() / RAND_MAX * L - radio;

        if ((distancia(x,y,0,0)) <= radio) {
            c += 1;
        }
    }

    double pi = 4.0 * c / N;

    printf("%f\n", pi);

}
