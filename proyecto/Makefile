CC = g++
CFLAGS = -Wall
PROG = textures

SRCS = main.cpp nuevoVector3f.cpp nuevoVector2f.cpp CObjeto.cpp CTeclado.cpp 
ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGL -lGLU -lfreeimage
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
