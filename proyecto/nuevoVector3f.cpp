#include "nuevoVector3f.h"


nuevoVector3f::nuevoVector3f(float posicion_x = 0, float  posicion_y= 0, float posicion_z= 0) { 
            vectorPosicion[0] = posicion_x;
            vectorPosicion[1] = posicion_y;
            vectorPosicion[2] = posicion_z;
        }
        
 float& nuevoVector3f::  operator[] ( int posicion ){ 
            return vectorPosicion[posicion];
        }   


