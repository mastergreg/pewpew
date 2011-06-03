LIBS=-lgc -lglut -lGL -lGLU -lm
EXTRA_FLAGS=-Wall -Wextra
PROG=pewpew
all: ${PROG}
game_object.o: game_object.cpp game_object.h
	gcc -c game_object.cpp ${EXTRA_FLAGS}
vector.o: vector.h vector.cpp
	g++ -c vector.cpp -lm ${EXTRA_FLAGS}
ships.o: ships.h ships.cpp	
	g++ ${LIBS} -c ships.cpp ${EXTRA_FLAGS}
drawables.o: drawables.cpp drawables.h
	g++ ${LIBS} -c drawables.cpp ${EXTRA_FLAGS}
${PROG}:	pewpew.cpp vector.o ships.o game_object.o drawables.o
	g++ ${LIBS} game_object.o ships.o vector.o drawables.o pewpew.cpp -o ${PROG} ${EXTRA_FLAGS}
clean:
	rm *.o ${PROG}.tar



tar:
	tar -czvf ${PROG}.tar *