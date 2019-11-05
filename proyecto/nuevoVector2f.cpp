#include "nuevoVector2f.h"

nuevoVector2f::nuevoVector2f(float posicion_x = 0, float  posicion_y= 0) { 
   vectorPosicion[0] = posicion_x;
   vectorPosicion[1] = posicion_y;
}

float& nuevoVector2f:: operator[] ( int posicion ){ 
   return vectorPosicion[posicion];
}   


