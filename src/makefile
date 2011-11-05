#-lgc -ggdb
LIBS=-lglut -lGL -lGLU -lalut -lopenal
EXTRA_FLAGS=-Wall -Wextra -Wuninitialized -O2 -flto
PROG=pewpew
all: ${PROG}


CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(CPP_FILES:.cpp=.o)
${PROG}:	${OBJ_FILES}
	g++  ${OBJ_FILES} ${LIBS} -o ${PROG} ${EXTRA_FLAGS}  
	cp ${PROG} ../
%.o: %cpp
	g++ ${EXTRA_FLAGS} -c -o $@ $<
clean:
	rm *.o 



tar:
	tar -uzvf ${PROG}.tar *.cpp
	tar -uzvf ${PROG}.tar *.h
