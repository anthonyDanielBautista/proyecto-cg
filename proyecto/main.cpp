/*
   MOVIMIENTO DE LA CAMARA:
      USO DE LAS TECLAS MAYÚSCULAS Y MINÚSCULAS
      TRASLACIÓN: A->eje X, S->eje Y, D->eje Z
      ROTACIÓN RESPECTO A SU EJE: Z->GIRA RESPECTO AL EJE Z Y EL RADIO ,
                                  X-> GIRA EN EL PLANO X E Y
*/

#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <assert.h>

#include "nuevoVector3f.h"
#include "nuevoVector2f.h"
#include "CObjeto.h"
#include "CTeclado.h"

using namespace std;

//INSTANCIA
CObjeto objeto;
CTeclado teclado;

void keyboardFunc_2( unsigned char key, int x, int y ){
   teclado.keyboardFunc( key, x, y );
}
void specialFunc_2( int key, int x, int y ){
   teclado.specialFunc(  key,  x,  y );
}

//PROTOTIPOS
void drawScene(void);
void initRendering();
void reshapeFunc(int w, int h);
void generarTexturas();

//
int main( int argc, char** argv )
{
   glutInit(&argc,argv);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowPosition( 60, 60 );
   glutInitWindowSize( 600, 600 );
   glutCreateWindow("ESCENARIO");

   initRendering();
   
   //OBJETOS
   generarTexturas();

   //TECLADO
   glutKeyboardFunc(keyboardFunc_2); 
   glutSpecialFunc(specialFunc_2);   

   glutReshapeFunc( reshapeFunc );

   glutDisplayFunc( drawScene );

   glutMainLoop( );

   return 0;	
}


void drawScene(void)
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode( GL_MODELVIEW );  
   glLoadIdentity();      
   
   //-----------------------CAMARA-------------------  
   GLdouble x = teclado.cameraX+teclado.deltax; 
   GLdouble y = teclado.cameraY+teclado.deltay;   
   GLdouble z = teclado.cameraZ+teclado.deltaz;  
   GLdouble r = teclado.radio;
   GLdouble teta = teclado.teta;
   GLdouble fi = teclado.fi;
   gluLookAt(x, y, z, r*sin(teta)*cos(fi)+teclado.deltax ,r*sin(teta)*sin(fi)+teclado.deltay, r*cos(teta)+teclado.deltaz, teclado.upX, teclado.upY,teclado.upZ);
   
   
   //-----------------------------ILUMINACION --------------------------
  
   GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                              {0.9, 0.5, 0.5, 1.0},
                              {0.5, 0.9, 0.3, 1.0},
                              {0.3, 0.8, 0.9, 1.0}};

     //VARIACION DE DIFERENTES TIPOS DE COLORES
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[teclado.cambioColor]);

   GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat shininess[] = {100.0};

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


   GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};

     //AUMENTO Y DISMINUCION DE LA LUZ
   GLfloat Lt0pos[] = {1.0f, teclado.luz_posicion1, teclado.luz_posicion2, 1.0f};

   glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0diff);
   glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);



   //------------------------------------------------
   //GRAFICA DE OBJETOS
   
   glRotatef(90.0, 1.0, 0.0, 0.0);
 
   glScalef(0.4, 0.4, 0.4);

   //ROBOT
   glPushMatrix();
   glScalef(0.3, 0.3, 0.3);
   glTranslatef(3.0,2.6,0.0);
   glTranslatef(teclado.m_x,0.0,teclado.m_z);//MUEVE EN EL Z, X

   for(int i=0; i<31; i++)
      objeto.dibujado(i,i);

   glPopMatrix();
   //HABITACION
   objeto.dibujado(31, 31);
   objeto.dibujado(32, 32);
   objeto.dibujado(33, 33);
   //MUEBLES
   objeto.dibujado(34, 34);//cama
   objeto.dibujado(35, 35);//colchon
   objeto.dibujado(34, 36);//escritorio
   objeto.dibujado(34, 37);//librero
   objeto.dibujado(34, 38);//mesa
   objeto.dibujado(34, 39);//silla en escritorio

   glutSwapBuffers();
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);   
    glEnable(GL_LIGHTING);    
    glEnable(GL_LIGHT0);    
    
}

void reshapeFunc(int w, int h)
{
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}



void generarTexturas()
{

   //CARGANDO TEXTURA
   glGenTextures(numTEXT,objeto.texID);  // Obtener el Id textura .
   objeto.loadTextures("obj/robot/textura/cabeza.png", 0);
   objeto.loadTextures("obj/robot/textura/cintura.png", 1);
   objeto.loadTextures("obj/robot/textura/pecho.png", 2);
   objeto.loadTextures("obj/robot/textura/pierna_d_1.png", 3);
   objeto.loadTextures("obj/robot/textura/pierna_d_2.png", 4);
   objeto.loadTextures("obj/robot/textura/pierna_d_3.png", 5);
   objeto.loadTextures("obj/robot/textura/pierna_i_1.png", 6);
   objeto.loadTextures("obj/robot/textura/pierna_i_2.png", 7);
   objeto.loadTextures("obj/robot/textura/pierna_i_3png", 8);
   objeto.loadTextures("obj/robot/textura/hombro_d.png", 9);
   objeto.loadTextures("obj/robot/textura/codo_d.png", 10); 
   objeto.loadTextures("obj/robot/textura/articulacion_c_m_d.png", 11);
   objeto.loadTextures("obj/robot/textura/palma_d.png", 12);
   objeto.loadTextures("obj/robot/textura/dedo.png", 13);
   objeto.loadTextures("obj/robot/textura/dedo_d_1.png", 14);
   objeto.loadTextures("obj/robot/textura/dedo.png", 15);
   objeto.loadTextures("obj/robot/textura/dedo_d_2.png", 16);
   objeto.loadTextures("obj/robot/textura/dedo.png", 17);
   objeto.loadTextures("obj/robot/textura/dedo_d_3.png", 18);
   objeto.loadTextures("obj/robot/textura/dedo.png", 19);
   objeto.loadTextures("obj/robot/textura/hombro_i.png", 20);
   objeto.loadTextures("obj/robot/textura/codo_i.png", 21);
   objeto.loadTextures("obj/robot/textura/articulacion_i.png", 22);
   objeto.loadTextures("obj/robot/textura/palma_d.png", 23);
   objeto.loadTextures("obj/robot/textura/dedo.png", 24);
   objeto.loadTextures("obj/robot/textura/dedo_i_1.png", 25);
   objeto.loadTextures("obj/robot/textura/dedo.png", 26);
   objeto.loadTextures("obj/robot/textura/dedo_i_2.png",27);
   objeto.loadTextures("obj/robot/textura/dedo.png", 28);
   objeto.loadTextures("obj/robot/textura/dedo_i_3.png", 29);
   objeto.loadTextures("obj/robot/textura/dedo.png", 30);


   //CARGANDO OBJETOS
   objeto.loadInput("obj/robot/partes/cabeza.obj",0);
   objeto.loadInput("obj/robot/partes/cintura.obj",1);
   objeto.loadInput("obj/robot/partes/pecho.obj",2);
   objeto.loadInput("obj/robot/partes/pierna_d_1.obj",3);
   objeto.loadInput("obj/robot/partes/pierna_d_2.obj",4);
   objeto.loadInput("obj/robot/partes/pierna_d_3.obj",5);
   objeto.loadInput("obj/robot/partes/pierna_i_1.obj",6);
   objeto.loadInput("obj/robot/partes/pierna_i_2.obj",7);
   objeto.loadInput("obj/robot/partes/pierna_i_3.obj",8);
   objeto.loadInput("obj/robot/partes/hombro_d.obj",9);
   objeto.loadInput("obj/robot/partes/codo_d.obj",10); 
   objeto.loadInput("obj/robot/partes/articulacion.obj",11);
   objeto.loadInput("obj/robot/partes/palma_d.obj",12);
   objeto.loadInput("obj/robot/partes/dedo_4.obj",13);
   objeto.loadInput("obj/robot/partes/dedo_1_1.obj",14);
   objeto.loadInput("obj/robot/partes/dedo_1_2.obj",15);
   objeto.loadInput("obj/robot/partes/dedo_2_1.obj",16);
   objeto.loadInput("obj/robot/partes/dedo_2_2.obj",17);
   objeto.loadInput("obj/robot/partes/dedo_3_1.obj",18);
   objeto.loadInput("obj/robot/partes/dedo_3_2.obj",19);
   objeto.loadInput("obj/robot/partes/hombro_i.obj",20);
   objeto.loadInput("obj/robot/partes/codo_i.obj",21);
   objeto.loadInput("obj/robot/partes/articulacion_i.obj",22);
   objeto.loadInput("obj/robot/partes/palma_i.obj",23);
   objeto.loadInput("obj/robot/partes/dedo_i_4.obj",24);
   objeto.loadInput("obj/robot/partes/dedo_i_1_1.obj",25);
   objeto.loadInput("obj/robot/partes/dedo_i_1_2.obj",26);
   objeto.loadInput("obj/robot/partes/dedo_i_2_1.obj",27);
   objeto.loadInput("obj/robot/partes/dedo_i_2_2.obj",28);
   objeto.loadInput("obj/robot/partes/dedo_i_3_1.obj",29);   
   objeto.loadInput("obj/robot/partes/dedo_i_3_2.obj",30);
   
   //CARGANDO TEXTURA
   objeto.loadTextures("obj/casa/pared.jpg", 31);
   objeto.loadTextures("obj/casa/techo.jpg", 32);
   objeto.loadTextures("obj/casa/piso.jpg", 33);
   objeto.loadTextures("obj/muebles/madera.jpg", 34);
   objeto.loadTextures("obj/muebles/colchon.jpg", 35);
   
   //CARGANDO OBJETOS
      //HABITACION
   objeto.loadInput("obj/casa/pared.obj",31);
   objeto.loadInput("obj/casa/techo.obj",32);
   objeto.loadInput("obj/casa/piso.obj",33);

      //MUEBLES
   objeto.loadInput("obj/muebles/cama.obj",34);
   objeto.loadInput("obj/muebles/colchon.obj",35);
   objeto.loadInput("obj/muebles/escritorio.obj",36);
   objeto.loadInput("obj/muebles/librero.obj",37);
   objeto.loadInput("obj/muebles/mesa.obj",38);
   objeto.loadInput("obj/muebles/silla.obj",39);
}

