class nuevoVector2f { 
    public:
        float vectorPosicion[2];
        nuevoVector2f(float posicion_x, float  posicion_y);
        float& operator[] ( int posicion );
};

