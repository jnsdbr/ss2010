# variables
CC = g++
PRODUCT = test
OBJECTS = FifoClass.o test.o
HEADER = FifoClass.h
CFLAGS = -Wall -g
RM = rm

# bindings
$(PRODUCT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

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
