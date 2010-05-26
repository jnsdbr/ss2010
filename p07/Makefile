CC = g++
CFLAGS = -c -Wall -g -lm
LDFLAGS =
SOURCES = Image.cpp BmpWrite.cpp Grafikklasse.cpp SimpleFont.cpp AviWrite.cpp FileIO.cpp GrafikKiste.cpp Test_GrafikKiste.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PRODUCT = Test
RM = rm

all: $(SOURCES) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) *o $(PRODUCT)
