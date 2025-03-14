#ifndef __Bala_H__
#define __Bala_H__
#include "Pantalla.h"

/**
    \mainpage Bala
    La biblioteca Bala incluye una estructura para definir una bala y consta de varias funciones para implementar.
*/

/**
   \file Bala.h
   \brief  Fichero de cabecera para poder usar las funciones de Bala.
*/

/**
    \brief TDA BalaRep
 */
typedef struct BalaRep * Bala;

/**
    \brief La funci�n devuelve una estructura tipo Bala.

    La func�n debe ser creada en el momento en el disparamos una bala.

    \param x posici�n de Bala en el eje de abscisas.
    \param y posici�n de Bala en el eje de ordenadas.
    \param vx velocidad de Bala en el eje de abscisas.
    \param vy velocidda de Bala en el eje de ordenadas.
    \param w anchura de Bala.
    \param h altura de Bala.
    \param img[] array de imagenes que puede tomar Bala.

    \return Bala
*/
Bala crea_bala (double x, double y, double vx, double vy, int w, int h, Imagen img[]);

/**
    \brief La funci�n libera de memoria el espacio ocupado por Bala.

    \param b Bala a liberar.
*/
void libera_bala( Bala b );

/**
    \brief La funci�n mueve Bala.

    La funci�n suma a la posici�n de Bala su velocidad, en sus respectivos ejes.

    \param b Bala a mover.
*/
void mueve_bala( Bala b );
/**
    \brief La funci�n dibuja Bala.

    Dentro de la funci�n se llama a la funci�n dibuja_imagen del modulo "Patalla.h".

    \param b Bala a dibujar.
*/
void dibuja_bala( Bala b );

/**
    \brief La funci�n accede a la posici�n de Bala en el eje de abscisas.

    \param b Bala de la que queremos su posici�n.

    \return posici�n Bala
*/
double get_x_bala( Bala b );

/**
    \brief La funci�n accede a la posici�n de Bala en el eje de ordenadas.

    \param b Bala de la que queremos su posici�n.

    \return posici�n Bala
*/
double get_y_bala( Bala b );

/**
    \brief La funci�n detecta si Bala a colisionado.

    \param b Bala que queremos ver si ha colisionado.
    \param x posici�n del objeto con el que colisiona en el eje de abscisas.
    \param y posici�n del objeto con el que colisiona en el eje de ordenadas.
    \param w anchura objeto con el que colisiona.
    \param h altura objeto con el que colisiona.

    \return 1 si ha colisiona.
*/
int colision_bala( Bala b, double x, double y, double w, double h );

#endif
