# variables
CC = g++
PRODUCT = RationaleZahl
OBJECTS = RationaleZahl.o Test_RationaleZahl.o
HEADER = RationaleZahl.h
CFLAGS = 
RM = rm

# bindings
$(PRODUCT): $(OBJECTS) 
	$(CC) -o $@ $^

# relations
RationahlZahl.o: RationalZahl.cpp $(HEADER)
Test_RationaleZahl.o: Test_RationaleZahl.cpp $(HEADER)

# pattern
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PRODUCT)
	$(RM) $(OBJECTS)
