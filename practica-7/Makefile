CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3

# Archivos fuente comunes
COMMON_SOURCES = Robot.cpp Patient.cpp Appointment.cpp Medic.cpp Admin.cpp Agenda.cpp System.cpp User.cpp
COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)

# Archivos fuente específicos
MAIN_SOURCES = main.cpp
CREATE_TABLE_SOURCES = createTableUsersAndSchedule.cpp

# Objetos específicos
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
CREATE_TABLE_OBJECTS = $(CREATE_TABLE_SOURCES:.cpp=.o)

# Headers
HEADERS = Robot.h Patient.h Appointment.h Medic.h Admin.h Agenda.h System.h User.h CustomExeptions.h

# Targets
all: main createTableUsersAndSchedule
	@rm -f $(COMMON_OBJECTS) $(MAIN_OBJECTS) $(CREATE_TABLE_OBJECTS)

main: $(MAIN_OBJECTS) $(COMMON_OBJECTS)
	@$(CC) $(CFLAGS) -o main $(MAIN_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)

createTableUsersAndSchedule: $(CREATE_TABLE_OBJECTS) $(COMMON_OBJECTS)
	@$(CC) $(CFLAGS) -o createTableUsersAndSchedule $(CREATE_TABLE_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(COMMON_OBJECTS) $(MAIN_OBJECTS) $(CREATE_TABLE_OBJECTS) main createTableUsersAndSchedule

.PHONY: all clean