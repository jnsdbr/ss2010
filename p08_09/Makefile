CC = g++
CFLAGS = -c -Wall -g -lm
LDFLAGS =
SOURCES = Image.cpp BmpRead.cpp BmpWrite.cpp Grafikklasse.cpp SimpleFont.cpp AviWrite.cpp FileIO.cpp Test_GrafikHuelle.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PRODUCT = TestGHuelle
RM = rm

all: $(SOURCES) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) *o $(PRODUCT)
