CC=gcc
CFLAGS=-I. -g -w
DEPS = convert.h
OBJ = convert.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
find: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)