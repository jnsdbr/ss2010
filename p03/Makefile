# variables
CC = g++
PRODUCT = test
OBJECTS = FifoClass.o test.o
HEADER = FifoClass.h
CFLAGS =
RM = rm

# bindings
$(PRODUCT): $(OBJECTS)
$(CC) -o $@ $^

# relations
FifoClass.o: FifoClass.cpp $(HEADER)
test.o: test.cpp $(HEADER)

# pattern
%.o: %.c
$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
$(RM) $(PRODUCT)
$(RM) $(OBJECTS)