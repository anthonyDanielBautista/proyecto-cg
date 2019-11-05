class nuevoVector3f { 
    public:
        float vectorPosicion[3];
        nuevoVector3f(float posicion_x, float  posicion_y, float posicion_z);
        float& operator[] ( int posicion );
};

