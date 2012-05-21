all:
	gcc -Wall -pedantic-errors -Werror -Wno-long-long -Wno-format -Wno-format-extra-args -g -o tictactoe tictactoe.c
    
clean:
	rm -f tictactoe
