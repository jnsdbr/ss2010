# variables
CPP = c++
CFLAGS = -Wall -g
RM = rm

TARGETS = fifo1 fifo2
HEADER = FifoClass.h
OBJECTS = FifoClass.o FifoClassTest_1.o
OBJECTS2 = FifoClass.o FifoClassTest_2.o

all: ${TARGETS}

fifo1: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o fifo1

fifo2: $(OBJECTS2)
	$(CPP) $(CFLAGS) $(OBJECTS2) -o fifo2

clean:
	$(RM) *.o $(TARGETS)	