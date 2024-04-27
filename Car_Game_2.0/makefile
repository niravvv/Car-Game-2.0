CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = game.o terminal.o player.o cars.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

game.o : game.c game.h
	$(CC) -c game.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

player.o : player.c player.h
	$(CC) -c player.c $(CFLAGS)

cars.o : cars.c cars.h
	$(CC) -c cars.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
