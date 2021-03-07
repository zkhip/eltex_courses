CC=gcc
TARGET=calc
SOURCES=calc.c libmycalc.so
OBJECTS=add.o sub.o mul.o div.o

.PHONY: clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) calc.c -o $@ -L. -lmycalc

libmycalc.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

*.o: *.c
	$(CC) $^ -c

clean:
	rm -rf *.o *.a $(TARGET)