sources := $(wildcard *.cpp))
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

emca : $(objects)
	g++ -s -o emca $(objects)

.cpp.o:

.PHONY : clean

clean:
	-rm *.o emca
