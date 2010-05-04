OBJECTS = SimpleFontTest.o SimpleFont.o image.o bmpwrite.o

.PHONY: all
all: SimpleFontTest.exe

SimpleFontTest.exe: $(OBJECTS)
	g++ -g -o SimpleFontTest.exe $(OBJECTS)
SimpleFontTest.o: SimpleFontTest.cxx SimpleFont.h
	g++ -g -c -o SimpleFontTest.o SimpleFontTest.cxx
SimpleFont.o: SimpleFont.cxx SimpleFont.h
	g++ -g -c -o SimpleFont.o SimpleFont.cxx
image.o: image.cxx image.h rgb.h
	g++ -g -pedantic -c -o image.o image.cxx
bmpwrite.o: bmpwrite.cxx bmpwrite.h image.h rgb.h
	g++ -g -pedantic -c -o bmpwrite.o bmpwrite.cxx

.PHONY: clean
clean:
	rm -f $(OBJECTS) SimpleFontTest.exe
