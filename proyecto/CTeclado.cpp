#include "GL/freeglut.h"
#include <iostream>
#include <GL/glut.h>

#include "CTeclado.h"
using namespace std;

void CTeclado::keyboardFunc( unsigned char key, int x, int y )
{
   GLfloat d = 0.2; //variacion del desplazamiento
    switch ( key )
    {
    case 27: 
        exit(0);
        break;
    case 'v':
		cout << "Unhandled key press " << key << "." << endl;
		cambioColor++;
		if(cambioColor==4) 
		    cambioColor = 0;
        break;
      
      //MOVER CAMARA  
      case 'a':
         pX+=d;
         break;
      case 'A':
         pX-=d;
         break;
      case 's':
         pY+=d;
         break;
      case 'S':
         pY-=d;
         break;
      case 'd':
         pZ+=d;
         break;
      case 'D':
         pZ-=d;
         break;
    
      //MOVER ROBOT
      case 'q':
         m_x+=1.0;
         break;
      case 'Q':
         m_x-=1.0;
         break;
      case 'w':
         m_z+=1.0;
         break;
      case 'W':
         m_z-=1.0;
         break;
       
    default:
        cout << "Unhandled key press " << key << "." << endl;
    }
    glutPostRedisplay();
}

void CTeclado::specialFunc( int key, int x, int y )
{  
   GLfloat pi = 3.14159;  
   GLfloat razonGiro = (2.0*pi/180);
   
    switch ( key )
    {
    case GLUT_KEY_UP:
        teta-=razonGiro;
		break;
    case GLUT_KEY_DOWN:
         teta+=razonGiro;
		break;
    case GLUT_KEY_LEFT:
         fi-=razonGiro;
		break;
    case GLUT_KEY_RIGHT:
         fi+=razonGiro;
		break;
    }
      
    glutPostRedisplay();
}
