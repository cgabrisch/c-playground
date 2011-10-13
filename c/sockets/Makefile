OBJECTS = sockutil.o tserver.o
EXECUTABLE = tserver

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

sockutil.o tserver.o: sockutil.h

.PHONY: clean

clean: 
	rm -f $(EXECUTABLE) $(OBJECTS)
