CC = g++
CFLAGS = -Wall -g

SOURCES = main.cpp Robot.cpp Patient.cpp Appointment.cpp Medic.cpp Admin.cpp Agenda.cpp System.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Robot.h Patient.h Appointment.h Medic.h Admin.h Agenda.h System.h

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)
	rm -f $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<