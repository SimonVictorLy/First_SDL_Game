# OBJ (.o) files will be compiled -c first 
# then the linker will be called -o to link th files

#OBJS specifies which files to compile as part of the project
OBJS = main.o CTexture.o Entity.o

#CC specifies which compiler we're using
CC = g++

#CFLAGS additional compilation options e.g w - suppresses all warnings
CFLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Executable name
OBJ_NAME = run

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OBJ_NAME) $(OBJS) $(LFLAGS)

main.o: main.cpp def.h
	$(CC) -c main.cpp

CTexture.o: CTexture.cpp def.h
	$(CC) -c CTexture.cpp 

Entity.o: Entity.cpp def.h
	$(CC) -c Entity.cpp

#This is the target that compiles our executable
clean:
	rm $(OBJ_NAME) $(OBJS)
