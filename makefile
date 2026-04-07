all: card stockpile foundation game main.cpp
	g++ -pedantic-errors -g main.cpp card stockpile foundation game -o main
card: card.cpp card.h
	g++ -pedantic-errors -g -c card.cpp -o card
stockpile: stockpile.cpp stockpile.h
	g++ -pedantic-errors -g -c stockpile.cpp -o stockpile
foundation: foundation.cpp foundation.h
	g++ -pedantic-errors -g -c foundation.cpp -o foundation
game: game.cpp game.h
	g++ -pedantic-errors -g -c game.cpp -o game