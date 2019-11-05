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

using namespace std; 

//DIBUJO DE LOS TRIANGULOS CON LOS ARCHIVOS .OBJ CON SU TEXTURA
void CObjeto:: dibujado(int id_textura, int id_obj) // id: id de la textura
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

//LEYENDO Y GUARDANDO LOS ARCHIVOS .OBJ 
void CObjeto:: loadInput(string archivo, int id) {

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

void CObjeto:: loadTextures(const char *texto, int id) {
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

