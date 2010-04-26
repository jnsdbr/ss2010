# variables
CC = g++
PRODUCT = poly
OBJECTS = BmpWrite.o Image.o Polynomtest.o
HEADER = Polynom.h
CFLAGS = -Wall -g
RM = rm

# bindings
$(PRODUCT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# relations
BmpWrite.o: BmpWrite.cpp BmpWrite.h
Image.o: Image.cpp Image.h
Polynomtest.o: Polynomtest.cpp $(HEADER)

# pattern
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PRODUCT)
	$(RM) $(OBJECTS)
