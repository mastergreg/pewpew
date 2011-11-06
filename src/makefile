#-lgc -ggdb
LDFLAGS :=-lglut -lGL -lGLU -lalut -lopenal
CXXFLAGS :=-Wall -Wextra -Wuninitialized -O2 -flto
CC=g++
PROG=../pewpew


CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

all : $(PROG)


$(PROG) : $(DEP_FILES) $(OBJ_FILES)
	$(CC) -o $(PROG) $(OBJ_FILES) $(LDFLAGS) 

-include $(DEP_FILES)
%.d : %.cpp
	echo "Building dep files"
	@set -e; $(CC) -MM $(CXXFLAGS) $<  > $@;

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< 

.PHONY: clean tar

clean:
	rm *.o *.d $(PROG)

tar:
	tar -uzvf $(PROG).tar *.cpp
	tar -uzvf $(PROG).tar *.h
	cp $(PROG.tar)
