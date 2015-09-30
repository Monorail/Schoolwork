//Alex Berliner
//COP 3223-003
//games.c
//10/31/2011

#include <stdio.h>
#include <time.h>
#include <math.h>

const int QUIT = 4;
const int SIZE = 3;
const int MAX_SQUARE_VALUE = 20;
const int DEFAULT_MAX_GUESS = 100;
const int MAX_RAND_VALUE = 32767;
const int INVALID = -1;
int menu();

int getGuessScore(int max, int numguesses);
int guessGame(int max);

int winningSquare(int square[][SIZE]);
void fillSquare(int square[][SIZE]);
void printSquare(int square[][SIZE]);
int checkRows(int square[][SIZE]);
int checkCols(int square[][SIZE]);
int getSum(int square[][SIZE]);
int validRowCol(int row, int col);

int getSquareScore(int square[][SIZE], int first_sum, int num_turns);
int playSquareGame();

int main(void) {

    srand(time(0));

    int total = 0, choice;

    choice = menu();

    // Loop until the user quits.
    while (choice != QUIT) { //wouldn't while ((choice = menu()) != QUIT) be simpler?

        // Execute the guessing game.
        if (choice == 1) {

            int max;
            printf("What do you want the maximum value in the guessing game to be?\n");
            scanf("%d", &max);

            // If the user chooses an invalid max, reset the game to 100.
            if (max < 2 || max > MAX_RAND_VALUE){
                max = DEFAULT_MAX_GUESS;
                printf("Sorry, you chose an invalid maximum, you'll play with a maximum of 100.\n");
            }
            total += guessGame(max);
        }

        // Execute the square game.
        else if (choice == 2) {
            total += playSquareGame();
        }

        // Print the user's current score.
        else if (choice == 3) {
            printf("Your current score is %d.\n", total);
        }

        // Get the user's next choice.
        choice = menu();
    }

    // Print out the final score.
    printf("Your final score is %d.\n", total);
    return 0;
}


// Precondition(s):  None
// Postcondition(s): Prompts the user with the menu and continues to read in their choice until they
//                   enter a valid choice in between 1 and 4, which then gets returned.
int menu() {
    int option = 0;
    do{
        if (option == -1 ) printf("Sorry that is not a valid choice. Please try again.\n");
        printf("Please enter your choice from one of the following options.\n");
        printf("1. Play the guessing game.\n");
        printf("2. Play the square game.\n");
        printf("3. View your current score.\n");
        printf("4. Quit.\n");
        scanf("%d",&option);
        if (option != 1 && option != 2 && option != 3 && option != 4)option = INVALID;
    }while(option == INVALID);

    return option;
}

// Precondition(s): 1 < max < 32767
// Postcondition(s): Generates a random number in the range 1 to max, inclusive, and allows the
//                user to guess the number. After each guess, the user is told to guess lower or
//                higher, until they guess the correct number. At this point, their score is
//                returned, which is based upon the number of guesses it took them to guess the
//                secret number.
int guessGame(int max) {
    int guess,num,numTurns=0,points = 0;

    num=rand()%max + 1;

    do{//game loop
        numTurns++;
        printf("Please enter your guess(1 - %d).\n",max);
        scanf("%d",&guess);
        while(guess < 1 || guess > max){
            printf("That is not a valid guess.\nPlease enter your guess(1 - %d).\n",max);//error loop
            scanf("%d",&guess);
        }
        if (guess < num)printf("Sorry your guess is too low.\n");
        else if (guess > num)printf("Sorry your guess is too high.\n");
    }while(guess != num);

    printf("You scored %d points for the Guessing Game this time!\nYou got the number in %d turns.\n",getGuessScore(max, numTurns),numTurns);
    return getGuessScore(max, numTurns);
}

// Precondition(s): 1 < max < 32767, represents the maximum possible number in the guessing game, and
//               numguesses represents the number of guesses needed for a guessing game with the
//               raMAX_SQUARE_VALUEnge of choices from 1 to max, inclusive.
// Postcondition(s): Returns the score for the instance of the guessing game described.
int getGuessScore(int max, int numguesses) {

    // Best we can guarantee in a game, using binary search.
    int best = (int)ceil(log(max+1)/log(2));

    // The score is better, the fewer guesses you make.
    int score = 2*best - numguesses;

    // This is so we can avoid giving out negative scores.
    if (score < 0)
        score = 0;

    return score;
}


// Precondition(s): square has dimensions SIZE x SIZE
// Postcondition(s): square is randomly filled with numbers in between 1 and MAX.

void fillSquare(int square[][SIZE]) {
    int i,j;
    for (i = 0;i<SIZE;i++){
        for (j = 0;j<SIZE;j++){
            square[i][j] = rand()%MAX_SQUARE_VALUE+1;
        }
    }
}

// Precondition(s): square has dimensions SIZE x SIZE
// Postcondition(s): prints out the square in SIZE rows,
//                 in a format with 4 spaces per entry, right justified.
void printSquare(int square[][SIZE]) {
    int i,j;
    for (i = 0;i<SIZE;i++){
        for (j = 0;j<SIZE;j++){
            printf("%4d",square[j][i]);
        }
        printf("\n");
    }
}

// Precondition(s): square has dimensions SIZE x SIZE
// Postconditions(s): If all SIZE rows add up to the same value, this value is returned.
//                    Otherwise, -1 is returned to indicate at least 2 different row sums.
int checkRows(int square[][SIZE]) {
    int check = 0, oldval=0,newval = 0,same = 1;
    int i,j;

    for (i=0;i<SIZE;i++)oldval+=square[0][i];

    for (i = 1;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            newval += square[j][i];
        }
        if (oldval != newval) same = -1;//same set to -1 if any arent the same val
        oldval = newval;
        newval = 0;
    }
    if (same ==-1)oldval = -1;//must return oldval, so converts oldval to include same
    return oldval;
}

// Precondition(s): square has dimensions SIZE x SIZE.
// Postconditions(s): Returns 1 if all the rows and columns of square add to the same value.
//                    Returns 0 otherwise.
int winningSquare(int square[][SIZE]) {
    //printf("winningSquare() = %d\ncheckRows = %d\ncheckCols = %d\n",(checkRows(square) != -1 && checkRows(square) == checkCols(square)),checkRows(square), checkCols(square));
    if (checkRows(square) != -1 && checkRows(square) == checkCols(square))return 1;
    else return 0;
}

// Precondition(s): square has dimensions SIZE x SIZE.
// Postconditions(s): If all SIZE columns add up to the same value, this value is returned.
//                    Otherwise, -1 is returned to indicate at least 2 different column sums.
int checkCols(int square[][SIZE]) {
    int check = 0, oldval= 0,newval = 0,same = 1;
    int i,j;

    for (i=0;i<SIZE;i++)oldval+=square[0][i];

    for (i = 1;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            newval += square[i][j];
            }
        if (oldval != newval) same = -1;//same set to -1 if any arent the same val
        oldval = newval;
        newval = 0;
    }
    if (same ==-1)oldval = -1;//must return oldval, so converts oldval to include same
    return oldval;
}

// Precondition(s): square has dimensions SIZE x SIZE.
// Postconditions(s): Returns the sum of all the integers stored in square.
int getSum(int square[][SIZE]) {
    int i,j,val = 0;
    for (i = 0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            val += square[i][j];//sums all nodes and returns
            }
    }
    return val;
}

// Precondition(s): None
// Postcondition(s): Executes the square game and returns the user's score.
int playSquareGame() {
    int Xchange,Ychange,turns,newval;
    int square[SIZE][SIZE];
    fillSquare(square);
    int origSum = getSum(square);

    while(!winningSquare(square)){
        turns=0;
        printSquare(square);
        printf("Enter the row(0-%d) and column(0-%d) of the square you want to change.\n",SIZE-1,SIZE-1);
        scanf("%d%d",&Xchange,&Ychange);
        //printf("Xchange = %d\nYchange = %d\n",Xchange,Ychange);
        //printf("validrowcol = %d\n",validRowCol(Xchange,Ychange));

        while(validRowCol(Xchange,Ychange)){
            printf("Sorry, those values aren't in between 0 and %d.\nEnter the row(0-%d) and column(0-%d) of the square you want to change.\n",SIZE-1,SIZE-1,SIZE-1);//error message loop
            scanf("%d%d",&Xchange,&Ychange);
        }

        printf("What is the new value?\n");
        scanf("%d",&newval);

        square[Xchange][Ychange] = newval;
    }
    printf("Great job, here is your final square:\n");
    printSquare(square);
    printf("You scored %d points for the Square Game this time!\n",getSquareScore(square,origSum,turns));
    return getSquareScore(square,origSum,turns);
}

// Precondition(s): none
// Postcondition(s): Returns 1 if 0 <= row < SIZE and 0 <= col < SIZE. Returns 0 otherwise.
int validRowCol(int row, int col) {
    if ((0 > row || row > SIZE-1) || (0 > col || col > SIZE-1)) return 1;//conditions for valid rows and columns
    else return 0;
}

// Precondition(s): square is the end result of the square game, first_sum is the
//                  original sum of the values in the square at the starting of that
//                  instance of the square game and num_turns is the number of turns
//                  taken in that instance of the square game.
// Postcondition(s): The score of the given instance of the square game is returned.
int getSquareScore(int square[][SIZE], int first_sum, int num_turns) {

    // Calculate the difference in sum between the original and winning square.
    int new_sum = getSum(square);
    int diff = abs(new_sum - first_sum);

    // Calculate the number of squares that didn't have to be changed, assuming that each
    // square was changed only once.
    int turn_diff = SIZE*SIZE - num_turns;

    // Don't let this fall below 0.
    if (turn_diff < 0)
        turn_diff = 0;

    // This is the turn difference plus a weighted value that ranges from 0 to SIZE x SIZE.
    // The weighting is based on what percentage the difference of the sum of the square is
    // from the original sum of the square. The lower the percentage, the closer your score
    // is to SIZE x SIZE.
    return turn_diff + SIZE*SIZE*(first_sum - diff)/first_sum;
}
