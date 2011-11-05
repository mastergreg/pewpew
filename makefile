#-lgc -ggdb
LDFLAGS :=-lglut -lGL -lGLU -lalut -lopenal
CXXFLAGS :=
CC=g++
PROG=pewpew


CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))

all : $(PROG)
$(PROG) :	$(OBJ_FILES)
	$(CC) -o $(PROG) $(OBJ_FILES) $(LDFLAGS) 



obj/%.o : src/%.cpp src/%.h
	$(CC) $(CXXFLAGS) -c -o $@ $< 
clean:
	rm obj/*.o 



tar:
	tar -uzvf $(PROG).tar *.cpp
	tar -uzvf $(PROG).tar *.h
