.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

scrabble: Tile.o Node.o LinkedList.o scrabble.o Board.o Hand.o Bag.o Player.o GameLoop.o utils.o eof_exception.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
