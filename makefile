all: game.c level_maker.c
	clang game.c -lncurses -std="c17" -Ofast -o g
	clang level_maker.c -lncurses -std="c17" -Ofast -o lm