CC = g++
CFLAGS = -c -Wall -g -lm
LDFLAGS =
SOURCES = Kiste.cpp Test_Kiste.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PRODUCT = Test_Kiste
RM = rm

all: $(SOURCES) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) *o $(PRODUCT)
