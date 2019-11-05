using namespace std; 
class CObjeto{
   public:
      //NUMERO DE TEXTURAS
      #define numTEXT 40
      GLuint texID[numTEXT];

      //NUMERO DE ARCHIVOS OBJ
      #define numOBJ 50

      //ELEMENTOS DE OBJETOS
      vector<nuevoVector3f> tvertex[numOBJ];//vertices
      vector<nuevoVector3f> tnormal[numOBJ];//normales
      vector<nuevoVector2f> tuv[numOBJ]; //textura
      vector<vector<unsigned> > tf_v[numOBJ];//caras

      void dibujado(int id_textura, int id_obj);
      void loadInput(string archivo, int id);
      void loadTextures(const char *texto, int id);
 
};
