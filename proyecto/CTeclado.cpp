#include "GL/freeglut.h"
#include <iostream>
#include <GL/glut.h>

#include "CTeclado.h"
using namespace std;

void CTeclado::keyboardFunc( unsigned char key, int x, int y )
{
   GLdouble razonCamara = 0.2;
   GLdouble razonGiro = 0.1;
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
         deltax+=razonCamara;
         break;
      case 'A':
         deltax-=razonCamara;
         break;
      case 's':
         deltay+=razonCamara;
         break;
      case 'S':
         deltay-=razonCamara;
         break;
      case 'd':
         deltaz+=razonCamara;
         break;
      case 'D':
         deltaz-=razonCamara;
         break;

      //GIRAR CAMARA: COORDENADA POLAR 
      case 'z': //GIRA RESPECTO AL EJE Z Y EL RADIO
         teta+=razonGiro;
         break;
      case 'Z':
         teta-=razonGiro;
         break;
      case 'x': //GIRA EN EL PLANO X E Y
         fi+=razonGiro;
         break;
      case 'X':
         fi-=razonGiro;
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
    switch ( key )
    {
    case GLUT_KEY_UP:
        luz_posicion2-=0.5;
		break;
    case GLUT_KEY_DOWN:
         luz_posicion2+=0.5;
		break;
    case GLUT_KEY_LEFT:
         luz_posicion1-=0.5;
		break;
    case GLUT_KEY_RIGHT:
         luz_posicion1+=0.5;
		break;
    }
    glutPostRedisplay();
}
