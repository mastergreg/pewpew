#-lgc -ggdb
LDFLAGS :=-lglut -lGL -lGLU -lalut -lopenal
CXXFLAGS :=
CC=g++
PROG=../pewpew


CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,obj/%.o,$(CPP_FILES))
DEP_FILES := $(patsubst %.cpp,dep/%.d,$(CPP_FILES))

all : $(PROG)


$(PROG) : dep obj $(DEP_FILES) $(OBJ_FILES)
	$(CC) -o $(PROG) $(OBJ_FILES) $(LDFLAGS) 

-include $(DEP_FILES)
dep/%.d : %.cpp
	@set -e; $(CC) -MM $(CXXFLAGS) $<  | sed "s,^$*.o,obj/$*.o," > $@;

obj/%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< 
dep:
	mkdir -p dep
obj:
	mkdir -p obj

.PHONY: clean tar

clean:
	rm obj/*.o dep/*.d $(PROG)

tar:
	tar -czvf $(PROG).tar *.cpp *.h
