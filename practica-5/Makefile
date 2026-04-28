CC = g++
CFLAGS = -Wall -g

SOURCES = main.cpp Coleccion.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Coleccion.h

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<