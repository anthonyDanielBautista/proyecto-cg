
class CTeclado{

   public:
      //MOVER ROBOT
      int m_x, m_z;
      //VARIABLES CAMARA
      GLdouble cameraX=-5.0, cameraY=-4.0, cameraZ=1.0; 
      GLdouble deltax=0.0, deltay=0.0, deltaz=0.0;
      GLdouble upX=0.0, upY=0.0, upZ=1.0;
         //GIRAR CAMARA
      GLdouble teta = 1.3, fi=0.8, radio=5.0;
      //CAMBIAR COLOR
      GLuint cambioColor = 0;
      //CAMBIO DE POSICION DE LUZ
      GLfloat luz_posicion1 = 0.0; //PRIMERA VARIABLE
      GLfloat luz_posicion2 = 0.0; //SEGUNDA VARIABLE
      
      void keyboardFunc( unsigned char key, int x, int y );
      void specialFunc( int key, int x, int y );

};
