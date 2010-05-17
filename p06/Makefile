CC = g++
CFLAGS = -c -Wall -g -lm
LDFLAGS =
SOURCES = BmpWrite.cpp Image.cpp Grafikklasse.cpp P6_Test.cpp SimpleFont.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PRODUCT = GrafikTest
RM = rm

all: $(SOURCES) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) *o $(PRODUCT)
