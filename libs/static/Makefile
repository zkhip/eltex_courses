CC=gcc
TARGET=calc
SOURCES=calc.c libmycalc.a
OBJECTS=add.o sub.o mul.o div.o

.PHONY: clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) calc.c -o $@ -L. -lmycalc

libmycalc.a: $(OBJECTS)
	ar rc $@ $^

*.o: *.c
	$(CC) $^ -c

clean:
	rm -rf *.o *.a $(TARGET)