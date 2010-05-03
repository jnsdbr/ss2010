CC = g++
CFLAGS = -c -Wall -g -lm
LDFLAGS =
SOURCES = BmpWrite.cpp Image.cpp Polynom.cpp Polynomtest.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PRODUCT = Polymolly
RM = rm

all: $(SOURCES) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) *o $(PRODUCT)
