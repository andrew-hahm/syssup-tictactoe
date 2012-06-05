/*
 * tictactoe.c
 *
 *  Created on: May 7, 2012
 *      Author: andhah
 *
 *      Note: Player 0 is represented as 1 in array and O on board
 *      Player 1 is represented as 2 in array and 1 on board
 */

#include <stdio.h>
#include <stdlib.h>

int checkwin();
int getcoord();
int placeitem();
void printmap();
int computer_ai();
int human_predictor();

int checkwin(int board[3][3]) {
    int x, y;

    for (x = 0; x < 3; x++) {
        if (board[x][0] == 1 && board[x][1] == 1 && board[x][2] == 1) {
            return 0;
        } else if (board[x][0] == 2 && board[x][1] == 2 && board[x][2] == 2) {
            return 1;
        }
    }
    for (y = 0; y < 3; y++) {
        if (board[0][y] == 1 && board[1][y] == 1 && board[2][y] == 1) {
            return 0;
        } else if (board[0][y] == 2 && board[1][y] == 2 && board[2][y] == 2) {
            return 1;
        }
    }
    if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) {
        return 0;
    } else if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) {
        return 1;
    }
    if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1) {
        return 0;
    } else if (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2) {
        return 1;
    }

    return -1;
}

int getcoord(int xory) {
    int x = -1;

    do {
        if (xory == 0) {
            printf("Row number: ");
        } else {
            printf("Column number: ");
        }
        scanf("%d", &x);
        if (x > 3 || x < 1) {
            printf("Error: please enter a number between 1 and 3 inclusive.\n");
        }
    } while (x > 3 || x < 1);

    return x;
}

int placeitem(int playernum, int x, int y, int board[3][3], int outputsuppress, int actualplacement) {
    if (board[x][y] == 0) {
        board[x][y] = playernum + 1;
        if (actualplacement == 1) {
            printf("Player %d placed at [%d, %d]\n", playernum + 1, x + 1, y + 1);
        }
        return 0;
    } else {
        if (outputsuppress == 0) {
            printf("Something is already here!\n");
        }
        return 1;
    }
}

void printmap(int board[3][3]) {
    int x, y;

    for (x = 0; x < 3; x++) {
        printf("-------------\n");
        for (y = 0; y < 3; y++) {
            printf("| ");
            if (board[x][y] == 1) {
                printf("O ");
            } else if (board[x][y] == 2) {
                printf("X ");
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }
    printf("-------------\n\n");
}

int computer_ai(int board[3][3], int level, int moves) {
    int wincheck, x, y, placesuccess, noderootmax, bestnodex, bestnodey, bestnoderootmax, numvalues=0;
    int boardcopy[3][3] = { { 0 } };
    int values[3][9] = { { 0 } };

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            boardcopy[x][y] = board[x][y];
        }
    }

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            placesuccess = placeitem(1, x, y, boardcopy, 1, 0);
            if (placesuccess == 1 && level > 1) {
                return 100;
            } else {
                wincheck = checkwin(boardcopy);
                if (wincheck == 1 && level == 1){
                    placeitem(1, x, y, board, 1, 1);
                    return 0;
                } else if (wincheck == 1 && level > 1) {
                    return 1;
                } else if (wincheck == -1) {
                    noderootmax = 0;
                    if (moves + 1 < 9) {
                        noderootmax = human_predictor(boardcopy, level + 1, moves + 1);
                    }
                    values[0][numvalues] = noderootmax;
                    values[1][numvalues] = x;
                    values[2][numvalues] = y;
                    numvalues++;
                }
            }
        }
    }

    bestnoderootmax = values[0][0];
    bestnodex = values[1][0];
    bestnodey = values[2][0];
    for (x = 0; x < numvalues-1; x++) {
        if (values[0][x+1] > values[0][x]) {
            bestnoderootmax = values[0][x+1];
            bestnodex = values[1][x+1];
            bestnodey = values[2][x+1];
        }
    }
    if (level == 1) {
        return placeitem(1, bestnodex, bestnodey, board, 1, 1);
    } else {
        return bestnoderootmax;
    }
}

int human_predictor(int board[3][3], int level, int moves) {
    int wincheck, x, y, placesuccess, noderootmin, bestnoderootmin, numvalues=0;
    int boardcopy[3][3] = { { 0 } };
    int values[3][9] = { { 0 } };

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            boardcopy[x][y] = board[x][y];
        }
    }

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            placesuccess = placeitem(0, x, y, boardcopy, 1, 0);
            if (placesuccess == 1) {
                return -100;
            } else {
                wincheck = checkwin(boardcopy);
                if (wincheck == 0) {
                    return -1;
                } else if (wincheck == -1) {
                    noderootmin = 0;
                    if (moves != 9) {
                        noderootmin = computer_ai(boardcopy, level + 1, moves + 1);
                    }
                    values[0][numvalues] = noderootmin;
                    values[1][numvalues] = x;
                    values[2][numvalues] = y;
                    numvalues++;
                }
            }
        }
    }

    bestnoderootmin = values[0][0];
    for (x = 0; x < numvalues-1; x++) {
        if (values[0][x+1] < values[0][x]) {
            bestnoderootmin = values[0][x+1];
        }
    }
    return bestnoderootmin;
}

int main() {
    int player = 0, moves = 0, end = -1, x, y, successplace;
    int board[3][3] = { { 0 } };

    do {
        successplace = 1;
        printf("Player %d's turn\n", player + 1);

        if (player == 1) {
            x = computer_ai(board, 1, moves);
        } else {
            do {
                x = getcoord(0); /* input and checks bounds */
                y = getcoord(1);
                successplace = placeitem(player, x-1, y-1, board, 0, 1);
            } while (successplace == 1);
        }

        printmap(board);

        if (moves > 3) {
            end = checkwin(board);
        }

        moves++;
        player = (player + 1) % 2;
    } while (end == -1 && moves < 9);

    if (end == -1) {
        printf("Draw\n");
    } else {
        printf("Player %d wins!\n", end + 1);
    }

    return EXIT_SUCCESS;
}
