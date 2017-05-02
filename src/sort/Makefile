CC=clang
CFLAGS=-Weverything -Werror

TARGET=sort
SRC=benchmark.c
OBJ=sort.o util.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ) $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

sanity: $(OBJ) main.c
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o $(TARGET)

