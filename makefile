CC = gcc
CFLAGS = -Wall -O2
OBJ = main.o game.o render.o input.o score.o

snake: $(OBJ)
	$(CC) $(CFLAGS) -o snake $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o snake
