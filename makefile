#-lgc -ggdb
LIBS=-lglut -lGL -lGLU
EXTRA_FLAGS=-O2
PROG=pewpew
all: ${PROG}
joystick.o: joystick.cpp joystick.h
	g++ -c joystick.cpp ${EXTRA_FLAGS}
game_object.o: game_object.cpp game_object.h
	g++ -c game_object.cpp ${EXTRA_FLAGS}
vector2D.o: vector2D.h vector2D.cpp
	g++ -c vector2D.cpp -lm ${EXTRA_FLAGS}
ships.o: ships.h ships.cpp	
	g++ -c ships.cpp ${LIBS} ${EXTRA_FLAGS}
drawables.o: drawables.cpp drawables.h
	g++ -c drawables.cpp ${LIBS} ${EXTRA_FLAGS}
peripherals.o:	peripherals.cpp peripherals.h
	g++ -c peripherals.cpp ${LIBS} -o peripherals.o ${EXTRA_FLAGS}
level.o:  level.cpp level.h
	g++ -c 	level.cpp ${LIBS} ${EXTRA_FLAGS}  
menu_items.o: menu_items.cpp menu_items.h
	g++ -c menu_items.cpp ${LIBS} ${EXTRA_FLAGS}
menu.o: menu.cpp menu.h menu_items.o
	g++ -c menu.cpp ${LIBS} ${EXTRA_FLAGS}
OBJECTS=game_object.o ships.o vector2D.o drawables.o level.o joystick.o menu.o menu_items.o
${PROG}:	${PROG}.cpp ${PROG}.h ${OBJECTS}
	g++  ${PROG}.cpp ${OBJECTS} ${LIBS} -o ${PROG} ${EXTRA_FLAGS}  
clean:
	rm *.o ${PROG}.tar



tar:
	tar -uzvf ${PROG}.tar *.cpp
	tar -uzvf ${PROG}.tar *.h
