# variables
CC = g++
PRODUCT = csv2xml
OBJECTS = list.o file.o csv2xml.o
HEADER = P1.h
CFLAGS = 
RM = rm

# bindings
$(PRODUCT): $(OBJECTS) 
	$(CC) -o $@ $^

# relations
csv2xml.o: csv2xml.cpp $(HEADER)
list.o: list.cpp $(HEADER)
file.o: file.cpp $(HEADER)

# pattern
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PRODUCT)
	$(RM) $(OBJECTS)
