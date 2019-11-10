
class CTeclado{

   public:
      //MOVER ROBOT
      int m_x, m_z;
      //VARIABLES CAMARA
         //DESPLAZAMIENTO
         //GIRO
      GLfloat pX=-13, pY=2.4, pZ=3.6; 
      GLfloat upX=0.0, upY=1.0, upZ=0.0;
      GLfloat teta = 1.873542278417901, fi=-0.24168671525247656, radio=6.7082039325;
      
       //CAMBIAR COLOR
      GLuint cambioColor = 0;
      
      //CAMBIO DE POSICION DE LUZ
      GLfloat luz_posicion1 = 0.0; //PRIMERA VARIABLE
      GLfloat luz_posicion2 = 0.0; //SEGUNDA VARIABLE
      
      void keyboardFunc( unsigned char key, int x, int y );
      void specialFunc( int key, int x, int y );

};
