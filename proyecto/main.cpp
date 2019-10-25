#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
//#include "vecmath.h"


#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <assert.h>


#define numTEXT 10
GLuint texID[numTEXT];

using namespace std;

//CLASES
class nuevoVector3f { 
    public:
        float vectorPosicion[3];
        nuevoVector3f(float posicion_x = 0, float  posicion_y= 0, float posicion_z= 0) { 
            vectorPosicion[0] = posicion_x;
            vectorPosicion[1] = posicion_y;
            vectorPosicion[2] = posicion_z;
        }
        float& operator[] ( int posicion ){ 
            return vectorPosicion[posicion];
        }   
};

class nuevoVector2f { 
    public:
        float vectorPosicion[2];
        nuevoVector2f(float posicion_x = 0, float  posicion_y= 0) { 
            vectorPosicion[0] = posicion_x;
            vectorPosicion[1] = posicion_y;
        }
        float& operator[] ( int posicion ){ 
            return vectorPosicion[posicion];
        }   
};


//VARIABLES GLOBALES
#define numOBJ 10
vector<nuevoVector3f> tvertex[numOBJ];
vector<nuevoVector3f> tnormal[numOBJ];
vector<nuevoVector2f> tuv[numOBJ];
vector<vector<unsigned> > tf_v[numOBJ];

//DESPLAZARCE EN EL ESCENARIO
GLfloat mover_x = 0.0;
GLfloat mover_y = 0.0;
GLfloat mover_z = 0.0;

GLuint cambioColor = 0;//CAMBIO DE COLOR: PREGUNTA 2.1
	//CAMBIO DE POSICION DE LUZ: PREGUNTA 2.2
GLfloat luz_posicion1 = 0.0; //PRIMERA VARIABLE
GLfloat luz_posicion2 = 0.0; //SEGUNDA VARIABLE



//PROTOTIPOS
void dibujado(int id_textura, int id_obj);
void loadInput(string archivo, int id);
void loadTextures(const char *texto, int id);
void keyboardFunc( unsigned char key, int x, int y );
void specialFunc( int key, int x, int y );
void drawScene(void);
void initRendering();
void reshapeFunc(int w, int h);

void generarTexturas();

//
int main( int argc, char** argv )
{
    glutInit(&argc,argv);

    // We're going to animate it, so double buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 600, 600 );
    glutCreateWindow("ESCENARIO");

    // Initialize OpenGL parameters.
    initRendering();

   generarTexturas();
 
    glutKeyboardFunc(keyboardFunc); 
    glutSpecialFunc(specialFunc);   

    glutReshapeFunc( reshapeFunc );
    
    glutDisplayFunc( drawScene );

    glutMainLoop( );

    return 0;	// This line is never reached.
}


void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        //PREGUNTA 2.1: CAMBIO DE COLOR
		cout << "Unhandled key press " << key << "." << endl;
		cambioColor++;
		if(cambioColor==4) // 4 TIPO DE COLORES
		    cambioColor = 0;
        break;
      case 'a':
         mover_x+=1.0;
         break;
      case 'A':
         mover_x-=1.0;
         break;
      case 's':
         mover_y+=1.0;
         break;
      case 'S':
         mover_y-=1.0;
         break;
      case 'd':
         mover_z+=1.0;
         break;
      case 'D':
         mover_z-=1.0;
         break;
       
    default:
        cout << "Unhandled key press " << key << "." << endl;
    }
    glutPostRedisplay();
}

void specialFunc( int key, int x, int y )
{
		//PREGUNTA 2.2: CAMBIO DE POSICION DE LA LUZ
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
        luz_posicion2-=0.5;
		cout << "Unhandled key press: up arrow." << endl;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
         luz_posicion2+=0.5;
		cout << "Unhandled key press: down arrow." << endl;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
         luz_posicion1-=0.5;
		cout << "Unhandled key press: left arrow." << endl;
		break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
         luz_posicion1+=0.5;
		cout << "Unhandled key press: right arrow." << endl;
		break;
    }
    glutPostRedisplay();
}

void drawScene(void)
{
    //int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_MODELVIEW );  
    glLoadIdentity();              
 
   //---------------------------------------------------
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.9, 0.5, 0.5, 1.0},
                                 {0.5, 0.9, 0.3, 1.0},
                                 {0.3, 0.8, 0.9, 1.0}};
    //PREGUNTA 2.1:
        //VARIACION DE DIFERENTES TIPOS DE COLORES
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[cambioColor]);

    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    
    //PREGUNTA 2.2:
        //AUMENTO Y DISMINUCION DE LA LUZ
	GLfloat Lt0pos[] = {1.0f, luz_posicion1, luz_posicion2, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);



   //------------------------------------------------
   //GRAFICA DE OBJETOS
   glScalef(0.4, 0.4, 0.4);
   glTranslatef(mover_x, mover_y, mover_z);
   //glRotatef(mover_x, 1.0, 1.0, 0.0);
      //HABITACION
   //dibujado(0, 0);
   //dibujado(1, 1);
   //dibujado(2, 2);
      //MUEBLES
   dibujado(3, 3);//cama
   dibujado(4, 4);//colchon
   dibujado(3, 5);//escritorio
   dibujado(3, 6);//librero
   dibujado(3, 7);//mesa
   dibujado(3, 8);//silla en escritorio

   
   //------------------------------------------------

    
	// Dump the image to the screen.
      glutSwapBuffers();
}
//DIBUJO DE LOS TRIANGULOS CON LOS ARCHIVOS .OBJ CON SU TEXTURA
void dibujado(int id_textura, int id_obj) // id: id de la textura
{    
   vector<nuevoVector3f>vertex = tvertex[id_obj];
   vector<nuevoVector3f> normal = tnormal[id_obj];
   vector<nuevoVector2f> uv = tuv[id_obj];
   vector<vector<unsigned> >  f_v = tf_v[id_obj];
     
     glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, texID[id_textura]);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     for(unsigned int j=0; j < f_v.size(); j++) 
     {
			vector<unsigned> &v = f_v[j];
        
         unsigned c = v[2], f = v[5], i = v[8]; //NORMALES
         unsigned a = v[0], d = v[3], g = v[6]; //PROPIO VERTICE
         unsigned b = v[1], e = v[4], h = v[7]; //TEXTURA
			glBegin(GL_TRIANGLES);
         glNormal3d(normal[c-1][0],normal[c-1][1],normal[c-1][2]); 
         glTexCoord2f(uv[b-1][0], uv[b-1][1]);
         glVertex3d(vertex[a-1][0],vertex[a-1][1],vertex[a-1][2]);
            
         glNormal3d(normal[f-1][0],normal[f-1][1],normal[f-1][2]);
         glTexCoord2f(uv[e-1][0], uv[e-1][1]);
         glVertex3d(vertex[d-1][0],vertex[d-1][1],vertex[d-1][2]);
            
         glNormal3d(normal[i-1][0],normal[i-1][1],normal[i-1][2]);
         glTexCoord2f(uv[h-1][0], uv[h-1][1]);
         glVertex3d(vertex[g-1][0],vertex[g-1][1],vertex[g-1][2]);
         glEnd();
      }

      glDisable(GL_TEXTURE_2D);

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

//LEYENDO Y GUARDANDO LOS ARCHIVOS .OBJ 


void loadInput(string archivo, int id) {

   vector<nuevoVector3f>vertex;
   vector<nuevoVector3f> normal;
   vector<nuevoVector2f> uv;
   vector<vector<unsigned> > f_v;

   ifstream file(archivo);
   while (!file.eof()) 
   {
      string linea;
      getline(file, linea);
      stringstream str(linea);
      string inicio;
      str >> inicio; //primera palabra

      float v1, v2, v3;

      if (inicio == "vt") {
          str >> v1 >> v2;
          nuevoVector2f textura( v1, v2 );
          uv.push_back(textura);
      }
      else if (inicio == "vn") {
          str >> v1 >> v2 >> v3;
          nuevoVector3f normales( v1, v2, v3 );
          normal.push_back(normales);
      }
      else if (inicio == "v") {
          str >> v1 >> v2 >> v3;
          nuevoVector3f vertices( v1, v2, v3 );
          vertex.push_back(vertices);
      }

      else if (inicio == "f") {
         unsigned int total[9];
         vector<unsigned >  total_2;
         string linea2 = linea.substr(2, linea.size());
         //CONVERTIR '/' EN ' '
         for(int i=0; i< (int)linea2.length(); i++){
            if(linea2[i]=='/' )
               linea2[i] = ' ';
         }
         stringstream face_str(linea2);
          for(int i=0; i< (int)sizeof(total); i++){
            face_str>> total[i];
            total_2.push_back(total[i]);
         }
         f_v.push_back(total_2);  

      }

   }
  
   file.close();
   //SE ALMACENA
   tvertex[id] = vertex;
   tnormal[id] = normal;
   tuv[id] = uv;
   tf_v[id] = f_v;

   
}

void loadTextures(const char *texto, int id) {
 	//glGenTextures(numTEXT,texID);  // Obtener el Id textura .
    void* imgData;      // Puntero a data del Archivo.
    int imgWidth;   // Ancho de Imagen
    int imgHeight;  // Alto.
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(texto);
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, texto, 0);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData) {
         //printf("Textura cargada, tamanio %dx%d\n", imgWidth, imgHeight);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format = GL_RGB;
		}
         else{
            format = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID[id] );  // Cargando textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format,GL_UNSIGNED_BYTE, imgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura \n");
        }
}

void generarTexturas()
{
   
   //CARGANDO TEXTURA
   glGenTextures(numTEXT,texID);  // Obtener el Id textura .
   loadTextures("obj/casa/pared.jpg", 0);
   loadTextures("obj/casa/techo.jpg", 1);
   loadTextures("obj/casa/piso.jpg", 2);

   loadTextures("obj/muebles/madera.jpg", 3);
   loadTextures("obj/muebles/colchon.jpg", 4);
   
   //CARGANDO OBJETOS
      //HABITACION
   loadInput("obj/casa/pared.obj",0);
   loadInput("obj/casa/techo.obj",1);
   loadInput("obj/casa/piso.obj",2);

      //MUEBLES
   loadInput("obj/muebles/cama.obj",3);
   loadInput("obj/muebles/colchon.obj",4);
   loadInput("obj/muebles/escritorio.obj",5);
   loadInput("obj/muebles/librero.obj",6);
   loadInput("obj/muebles/mesa.obj",7);
   loadInput("obj/muebles/silla.obj",8);
}

