#include <stdio.h>
#include <math.h>

int rows = 3;
int columns = 3;
char board[3][3];
/*Dedicate the Chars to a variable so I can change them, also check for wins using a variable rather than declaring the char each time.
*/
char p1m = 'X';
char p2m = 'O';
int turn_count = 0;
game_over;
int win_condition = 3;

void initialize_board();
void tile_finder(int square, int* row, int* column);
void display_board(char board[3][3]);
void player_turn();

int main()
{
    initialize_board();
    printf_s("%c and %c\n", p1m, p2m);
    while (!check_win()) {
        /*Check for a win for each step to allow for characters to see the board when they get the last successful spot, 
        * and check for a cats game and be able to display the board
        */
        display_board(board);
        check_win();
        player_turn(p1m);
        check_win();
        display_board(board);
        check_win();
        player_turn(p2m);
        check_win();
    }
    return 0;
}


void tile_finder(int square, int* row, int* column) {
    *row = (square - 1) / 3;
    *column = (square - 1) % 3;
}

void display_board(char board[3][3]) {
    /*Print either a char, or a number based on what value exists in the array
    */
    for (int rowcounter = 0; rowcounter < 3; rowcounter++) {
        for (int columncounter = 0; columncounter < 3; columncounter++) {
            printf_s(" %c ", board[rowcounter][columncounter]);
            if (columncounter < 2) {
                /*vertical spacer between columncounters
                */
                printf_s("|");
            }
        }
        printf_s("\n");
        if (rowcounter < 2) {
            /*horizontal counter between rows
            */
            printf_s("---|---|---\n");
        }
    }
}

void initialize_board() {
    /*
     * reset the values to clear the board
     */
    int counter = 49;
    for (int rows = 0; rows < 3; rows++) {
        for (int columns = 0; columns < 3; columns++) {
            board[rows][columns] = (char)counter;
            counter++;
        }
    }
}

void player_turn(char symbol) {
    int choice, row, column;
    do {
        printf_s("Player %c, select a square ( 1 - 9 ): \n", symbol);
        scanf_s("%d", &choice);
        tile_finder(choice, &row, &column);
        if (check_available(row, column)) {
            board[row][column] = symbol;
            turn_count++;
            break;
        }
        else {
            printf_s("That tile is already taken. Try again.\n");
        }
    } while (1);
}

void mark_board(int row, int column, char symbol) {
    board[row][column] = symbol;
}

int check_available(int row, int column) {
    int tile_value = (int)board[row][column];
    if (tile_value < 49 || tile_value > 57) {
        printf_s("Not valid square!");
        return 0;
    }
    return 1;
    /*
     * This will check to see if the board contains a char that is outside of the numbers 1 - 9
     * if the tile is between these char values the check available will return false
     */
}

int check_win() {
    /*Check the rows and columns, and diagonals for consecutive chars, if there is nothing, and the turn count is less than 9, return 0
    * This is to prevent the game from not calling a cats game while the board is full of chars.
    */
    if (turn_count < 9) {
        for (int i = 0; i < 3; i++) {
            /*Go through each row and check for 3 consecutive player chars.
            */
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                if (board[i][0] == p1m) {
                    printf_s("X wins!\n");
                    display_board(board);
                    return 1;
                }
                else if (board[i][0] == p2m) {
                    printf_s("O wins!\n");
                    display_board(board);
                    return 1;
                }
            }

            /*Check the columns for 3 consecutive chars
            */
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                if (board[0][i] == p1m) {
                    printf_s("X wins!\n");
                    display_board(board);
                    return 1;
                }
                else if (board[0][i] == p2m) {
                    printf_s("O wins!\n");
                    display_board(board);
                    return 1;
                }
            }
        }

        /*Now check the diagonals for 3 consecutive chars
        */
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == p1m) {
                printf_s("X wins!\n");
                display_board(board);
                return 1;
            }
            else if (board[0][0] == p2m) {
                printf_s("O wins!\n");
                display_board(board);
                return 1;
            }
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == p1m) {
                printf_s("X wins!\n");
                display_board(board);
                return 1;
            }
            else if (board[0][2] == p2m) {
                printf_s("O wins!\n");
                display_board(board);
                return 1;
            }
        }

        return 0; /*This means there are not 3 consecutive chars, and the turn count is less than 9
        */
    }
    else {
        printf_s("Cats Game!\n");
        return 1;
    }
}

