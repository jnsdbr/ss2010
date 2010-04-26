# variables
CC = g++
PRODUCT = fifo
OBJECTS = FifoClass.o FifoClassTest_2.o
HEADER = FifoClass.h
CFLAGS = -Wall -g
RM = rm

# bindings
$(PRODUCT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# relations
FifoClass.o: FifoClass.cpp $(HEADER)
test.o: test.cpp $(HEADER)
FifoClassTest_1.o: FifoClassTest_1.cpp $(HEADER)
FifoClassTest_2.o: FifoClassTest_2.cpp $(HEADER)

# pattern
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PRODUCT)
	$(RM) $(OBJECTS)
