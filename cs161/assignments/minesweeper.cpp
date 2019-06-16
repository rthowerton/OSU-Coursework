/* Program: minesweeper.cpp
 * Author: Ryan Howerton
 * Date: 3/13/2016
 * Description: simulates the game minesweeper, minus the GUI.
 * Input: rows, columns, mines
 * Output: none*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct square{//creates an object type square to fill the board.
   bool bomb, flagged, isRevealed;
   int numMines;
};

/* Function: convertArguments
 * Description: Converts the command line args to ints and stores them.
 * Parameters: numArgs (argc), arguments(argv), *rows, *cols, *mines
 * Pre-Conditions: rows cols and mines are passed as addresses to storage vars.
 * Post-Conditions: rows, cols, and mines are filled with good input.*/
int convertArguments(int numArgs, char** arguments, int* rows, int* cols, int* mines){
   for(int i = 0; i < numArgs; i++){
      if(arguments[i][0] = '-'){//if line contains defining name
	 if(arguments[i][1] == 'r')
	    *rows = atoi(arguments[i+1]);//assign value to rows
	 else if(arguments[i][1] == 'c')
	    *cols = atoi(arguments[i+1]);//assign value to cols
	 else if(arguments[i][1] == 'm')
	    *mines = atoi(arguments[i+1]);//assign value to mines
      }
   }
   if(numArgs != 7 || *rows <= 0 || *cols <= 0 || *mines <= 0){//ensures good values only
      cout<<"Invalid command line input."<<endl;
      return 0;
   }
   return 1;
}

/* Function: makeBoard
 * Description: makes a board of squares using rows and cols.
 * Parameters: rows, cols
 * Pre-Conditions: rows and cols are both ints.
 * Post-Conditions: a board of squares exists and is stored.*/
square** makeBoard(int rows, int cols){
   square** temp;//is a placeholder 2d array
   temp = new square*[rows];//creates a 2d array
   for(int i = 0; i < rows; i++)
      temp[i] = new square[cols];
   return temp;
}

/* Function: getNumbers
 * Description: assigns numbers to each square on the board.
 * Parameters: board[][], rows, cols, y, x
 * Pre-Conditions: board is a two dimensional array of squares of size [rows][cols]
 * Post-Conditions: each square has been assigned a number value.*/
void getNumbers(square** board, int rows, int cols, int y, int x){
   for(int i = 0; i < rows; i++){//for each row
      for(int j = 0; j < cols; j++){//for each column
	 if((y >= i-1 && y <= i+1) && (x >= j-1 && x <= j+1))//if the mine is near the square
	    board[i][j].numMines++;
      }
   }
}

/* Function: placeBombs
 * Description: randomly places all mines on the board.
 * Parameters: board[][], rows, cols, mines
 * Pre-Conditions: board is a 2d array of squares of size [rows][cols].
 * Post-Conditions: mines have been placed equal to the number specified.*/
void placeBombs(square** board, int rows, int cols, int mines){
   int x, y;//will contain coordinates of each mine
   for(int i = 0; i < mines; i++){
      x = rand()%cols;//x coordinate of mine
      y = rand()%rows;//y coordinate of mine
      if(board[y][x].bomb == false){//if does not contain mine
	 board[y][x].bomb = true;//now contains mine
	 getNumbers(board, rows, cols, y, x);//assigns numbers to surrounding squares
      }
      else
	 i--;
   }
}

/* Function: printBoard
 * Description: prints board showing revealed/flagged squares only.
 * Parameters: board[][], rows, cols
 * Pre-Conditions: board is a 2d array of squares of size [rows][cols].
 * Post-Conditions: prints board only showing revealed/flagged squares.*/
void printBoard(square** board, int rows, int cols){
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
	 if(board[i][j].flagged == true)//if is flagged
	    cout<<"[!]";
	 else if(board[i][j].isRevealed == true)//if is revealed
	    cout<<"["<<board[i][j].numMines<<"]";
	 else
	    cout<<"[ ]";
      }
      cout<<endl;
   }
}

/* Function: printFullBoard
 * Description: prints the board showing everything.
 * Parameters: board[][], rows, cols
 * Pre-Conditions: the game is over.
 * Post-Conditions: prints full board.*/
void printFullBoard(square** board, int rows, int cols){
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
	 if(board[i][j].bomb == true)//there is bomb
	    cout<<"[*]";
	 else
	    cout<<"["<<board[i][j].numMines<<"]";//there is no bomb
      }
      cout<<endl;
   }
}

/* Function: flag
 * Description: flags a specified square.
 * Parameters: board[][], row, col, rows, cols
 * Pre-Conditions: board is a 2d array of squares of size [rows][cols].
 * Post-Conditions: Square is flagged.*/
void flag(square** board, int row, int col, int rows, int cols){
   if(row < 0 || row >= rows || col < 0 || col >= cols)//tests if row and col are good
      cout<<"Invalid coordinate to flag."<<endl;
   else if(board[row][col].flagged == true)//tests if square is already flagged
      cout<<"Square already flagged."<<endl;
   else
      board[row][col].flagged = true;
   printBoard(board, rows, cols);//prints board in current state
}

/* Function: open
 * Description: reveals a specified square.
 * Parameters: board[][], row, col, rows, cols
 * Pre-Conditions: board is a 2d array of squares of size [rows][cols].
 * Post-Conditions: square is revealed.*/
int open(square** board, int row, int col, int rows, int cols){
   int done = 0;
   if(row < 0 || row >= rows || col < 0 || col >= cols)//tests if row and col are good
      cout<<"Invalid coordinate to open."<<endl;
   else if(board[row][col].bomb == true){//checks if square is a mine
      cout<<"Get rekt."<<endl;
      done = 1;//ends game
      printFullBoard(board, rows, cols);//prints full board
   }
   else if(board[row][col].isRevealed == true)//tests if square is already revealed
      cout<<"Square already opened."<<endl;
   else{
      board[row][col].isRevealed = true;
      printBoard(board, rows, cols);
   }
   return done;
}

/* Function: checkWin
 * Description: checks if player has won.
 * Parameters: board[][], rows, cols
 * Pre-Conditions: board is a 2d array of squares of size [rows][cols].
 * Post-Conditions: determines if player did or did not win.*/
int checkWin(square** board, int rows, int cols){
   int done = 1;
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
	 if((board[i][j].isRevealed == false) && (board[i][j].bomb == false)){
	    done = 0;
	    i = rows-1;
	    break;
	 }
      }
   }
   if(done == 1){//if player won
      cout<<"Great job! You won!"<<endl;
      printFullBoard(board, rows, cols);
   }
   return done;
}


/* Function: playGame
 * Description: this function calls all game functions
 * Parameters: board[][], rows, cols
 * Pre-Conditions: board is fully initialized.
 * Post-Conditions: game works properly.*/
void playGame(square** board, int rows, int cols){
   int choice, row, col, done = 0;
   while(done == 0){//until game is over
      cout<<"Enter 1 to flag a square, 2 to open a square: "<<endl;//player options
      cin>>choice;
      if(choice == 1){//if flag a square
	 cout<<"Row: ";
	 cin>>row;
	 cout<<"Column: ";
	 cin>>col;
	 flag(board, row, col, rows, cols);//flag square
      }
      else if(choice == 2){//if open a square
	 cout<<"Row: ";
	 cin>>row;
	 cout<<"Column: ";
	 cin>>col;
	 if(done = open(board, row, col, rows, cols))
	    break;
	 done = checkWin(board, rows, cols);//check if game is over
      }
   }
}

/* Function: main
 * Description: is main function.
 * Parameters: argc, argv[][]
 * Pre-Conditions: argv contains -r (x) -c (y) -m (z)
 * Post-Conditions: game works properly.*/
int main(int argc, char* argv[]){
   srand(time(NULL));//seed random number generator
   int rows, cols, mines, cont = 1;
   cont = convertArguments(argc, argv, &rows, &cols, &mines);//converts to integers
   while(cont == 1){
      square** board = makeBoard(rows, cols);//creates the board
      placeBombs(board, rows, cols, mines);//places bombs
      printFullBoard(board, rows, cols);//for testing purposes
      printBoard(board, rows, cols);//print empty board
      playGame(board, rows, cols);//play the game
      cout<<"Enter 1 to play again, 0 to finish: ";//when finished
      cin>>cont;
      if(cont == 0)
	 break;
      if(cont == 1){
	 cout<<"Rows: ";
	 cin>>rows;
	 cout<<"Columns: ";
	 cin>>cols;
      }
   }
   return 0;
}
