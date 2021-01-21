CC       = gcc
CFLAGS   = -Wall -Werror -Wextra -pedantic
#INCLUDES = -lncurses -ltinfo

UTILS = utils
BOARD = board
GAME  = game
MAIN  = main

$(UTILS).o: $(UTILS).c $(UTILS).h
	$(CC) -c $(CFLAGS) $(UTILS).c -o $(UTILS).o

$(BOARD).o: $(BOARD).c $(BOARD).h $(UTILS).o
	$(CC) -c $(CFLAGS) $(BOARD).c -o $(BOARD).o

$(GAME).o: $(GAME).c $(GAME).h $(UTILS).o
	$(CC) -c $(CFLAGS) $(GAME).c -o $(GAME).o

$(MAIN): $(MAIN).c $(GAME).o $(BOARD).o $(UTILS).o
	$(CC) $(CFLAGS) $(MAIN).c $(GAME).o $(BOARD).o $(UTILS).o -o $(MAIN)

tests: tests.c $(GAME).o $(BOARD).o $(UTILS).o
	$(CC) $(CFLAGS) tests.c $(GAME).o $(BOARD).o $(UTILS).o -o tests

RM = rm -f
.PHONY: clean
clean:
	$(RM) $(MAIN)
	$(RM) tests
	$(RM) *.o
