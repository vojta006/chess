SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)
TARGET = program

CFLAGS = -ggdb

LFLAGS = -lSDL -lSDL_image -lSDL_net

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

%.o: %.cpp
	g++ -MMD -MP $(CFLAGS) -c $< -o $@
	
clear:
	rm *.o *.d 

-include $(DEPENDS)
