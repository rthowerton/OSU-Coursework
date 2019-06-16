/* Program: assignment4.cpp
 * Author: Ryan Howerton
 * Date: 2/15/2016
 * Description: create the code for playing Wheel of Fortune using functions and pointers.
 * Input: N/A
 * Output: N/A
*/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/* Function: getPuzzle
 * Description: have the user input a puzzle to solve in the game.
 * Parameters: string* puzzle
 * Pre-conditions: is passed a string*.
 * Post-conditions: fills the string* with a new value.
*/
void getPuzzle(string *puzzle){
   cout<<"Enter the puzzle: ";
   getline(cin, *puzzle);
}

/* Function: getNumPlayers
 * Description: get the number of players for the game.
 * Parameters: int* players
 * Pre-conditions: is passed an int*.
 * Post-conditions: fills the int*.
*/
void getNumPlayers(int *players){
   cout<<"Enter the number of players: ";
   cin>>*players;
}

/* Function: getNumRounds
 * Descritpion: get the desired number of rounds to be played.
 * Parameters: int* rounds
 * Pre-conditions: is passed an int*.
 * Post-conditions: fills the int*.
*/
void getNumRounds(int *rounds){
   cout<<"Enter the number of turns: ";
   cin>>*rounds;
}

/* Function: addMoney
 * Description: adds money accumulated over the round to the player's stash.
 * Parameters: int*** bank, int*** turnCash
 * Pre-conditions: is passed an int*** with a real value and an int*** with another real value.
 * Post-conditions: int*** bank contains a real value.
*/
void addMoney(int ***bank, int ***turnCash){
   ***bank += ***turnCash;
}

/* Function: convertInitialMessage
 * Description: encodes the user-entered puzzle to a series of "_" and " "
 * Parameters: string** puzzle, puzzleBlanks
 * Pre-conditions: is given a reference to the puzzle string and a copy of the puzzle string.
 * Post-conditions: converts the copy to a series of '-' and ' ' in the same general order as the original.
*/
void convertInitialMessage(string **puzzle, string **puzzleBlanks){
   string puzzleCopy = **puzzle, blanksCopy = **puzzleBlanks;
   for(int i = 0; i < puzzleCopy.length(); i++){
      if(puzzleCopy.at(i) == ' ')
         blanksCopy.at(i) = ' ';//where there are spaces, they are... still spaces.
      else
         blanksCopy.at(i) = '-';//where there are letters, they are now dashes.
   }
   **puzzleBlanks = blanksCopy;
   cout<<**puzzleBlanks<<endl;
}

/* Function: convertPuzzleConsonants
 * Description: called by guessLetter to show the current puzzle with correctly added letters
 * Parameters: string***** puzzle, string***** puzzleBlanks, char***** guess
 * Pre-conditions: is passed two strings*****, one containing the puzzle, one containing the blanked puzzle, and a char***** containing the current guess.
 * Post-conditions: prints out the series of '-' and ' ' along with the guessed letters in their places.
*/
void convertPuzzleConsonants(string *****puzzle, string *****puzzleBlanks, char *****guess){
   string puzzleCopy = *****puzzle, blanksCopy = *****puzzleBlanks;
   char guessCopy = *****guess;
   for(int i = 0; i < puzzleCopy.length(); i++){
      if(puzzleCopy.at(i) == guessCopy)
	 blanksCopy.at(i) = guessCopy;
   }
   *****puzzleBlanks = blanksCopy;
   cout<<*****puzzleBlanks<<endl;
}

/* Function: convertPuzzleVowels
 * Description: is called by buyVowel to show the puzzle in its current state.
 * Parameters: string**** puzzle, string**** guess
 * Pre-conditions: is passed two string****, one with the puzzle and one with the encrypted puzzle, and a char**** with the current guessed letter
 * Post-conditions: prints out the encrypted puzzle in its current state.
*/
void convertPuzzleVowels(string ****puzzle, string ****puzzleBlanks, char ****guess){
   string puzzleCopy = ****puzzle, blanksCopy = ****puzzleBlanks;
   char guessCopy = ****guess;
   for(int i = 0; i < puzzleCopy.length(); i++){
      if(puzzleCopy.at(i) == guessCopy)
	 blanksCopy.at(i) = guessCopy;
   }
   ****puzzleBlanks = blanksCopy;
   cout<<****puzzleBlanks;
}

/* Function: guessLetter
 * Description: takes user input for the current guessed letter.
 * Parameters: string**** puzzle, puzzleBlanks, char**** guess.
 * Pre-conditions: is given two string****, one with the puzzle and one witht he encrypted puzzle, and a char**** to fill with the next guess.
 * Post-conditions: fills the char**** with a good letter.
*/
int guessLetter(string ****puzzle, string ****puzzleBlanks, char ****guess){
   string puzzleCopy = ****puzzle;
   int count = 0;
   cout<<"Guess a letter: ";
   cin>>****guess;
   char guessCopy = ****guess;
   for(int i = 0; i < puzzleCopy.length(); i++){
      if(puzzleCopy.at(i) == guessCopy)
         count++;
   }
   convertPuzzleConsonants(&puzzle, &puzzleBlanks, &guess);
   cout<<"There is/are "<<count<<" "<<****guess<<"!"<<endl;
   return count;
}

/* Function: spinWheel
 * Description: if the player chose to spin the wheel, generates a random number to simulate spinning the wheel. Calls guessLetter on account of a good random number. Otherwise ends player's turn.
 * Parameters: int*** turnCash, string*** puzzle, puzzleBlanks, char*** guesses
 * Pre-conditions: is passed the above parameters filled with good values.
 * Post-conditions: returns an integer to either continue or end the player's turn.
*/
int spinWheel(int ***turnCash, string ***puzzle, string ***puzzleBlanks, char ***guess){
   int temp, numLetters;
   srand(time(NULL));
   temp = rand() % 22;
   if(temp == 0){
      cout<<"You are bankrupt!"<<endl;//bummer
      ***turnCash = 0;
      return 0;
   }
   else if(temp > 0 && temp < 21){
      cout<<"Your wheel landed on "<<temp<<"!"<<endl;
      numLetters = guessLetter(&puzzle, &puzzleBlanks, &guess);//call guessLetter, return to add to total.
      ***turnCash += numLetters * temp;
      return 1;
   }
   else if(temp == 21){
      cout<<"Lose a turn!"<<endl;//not as bad as 0
      return 0;
   }
}

/* Function: buyVowel
 * Description: if the player chose to buy a vowel, takes the player's account info and then subtracts 10 assuming the player can buy a vowel. Calls addVowel to add the vowel to the list of guessed letters.
 * Parameters: int*** bank, int*** turnCash, string*** puzzle, puzzleBlanks, char*** guess
 * Pre-conditions: all arguments are filled with real values
 * Post-conditions: user's stash is reduced by 10, vowel has been added to list of letters guessed.
*/
int buyVowel(int ***bank, int ***turnCash, string ***puzzle, string ***puzzleBlanks, char ***guess){
   string puzzleCopy = ***puzzle, blanksCopy = ***puzzleBlanks;
   int count = 0, okay = 0;
   cout<<"Choose your vowel: ";
   cin>>***guess;
   char vowel = ***guess;
   for(int i = 0; i < puzzleCopy.length(); i++){
      if(puzzleCopy.at(i) == vowel)
	 count++;
   }
   if(count != 0)
      okay = 1;
   convertPuzzleVowels(&puzzle, &puzzleBlanks, &guess);
   cout<<"There are "<<count<<" "<<***guess<<"!"<<endl;
   if(***turnCash >= 10)
      ***turnCash -= 10;
   else
      ***bank -= 10;
   return okay;
}

/* Function: guessPuzzle
 * Description: if the player chose to guess the puzzle, checks the user input against the actual puzzle. If player guessed correctly, returns 1 to end the round. Otherwise the player loses his/her turn.
 * Parameters: string*** puzzle
 * Pre-conditions: is passed a reference to the puzzle.
 * Post-conditions: returns an integer of 0 or 1.
*/
int guessPuzzle(string ***puzzle){
   string guess, puzzleCopy = ***puzzle;
   cin.ignore();
   cin.clear();
   cout<<"Enter your guess: ";
   getline(cin, guess);
   if(guess.compare(puzzleCopy) == 0){
      cout<<"Correct!\n"<<***puzzle<<endl;
      return 1;
   }
   else{
      cout<<"Wrong."<<endl;
      return 0;
   }
}

/* Function: playerTurn
 * Description: calls all functions to enact a single player's turn.
 * Parameters: int** bank, int** turnCash, string** puzzle, puzzleBlanks char** guess
 * Pre-conditions: all arguments point to good values.
 * Post-conditions: returns an integer to describe whether the player guessed correctly or incorrectly.
*/
int playerTurn(int **bank, int **turnCash, string **puzzle, string **puzzleBlanks, char **guess){
   int choice, turn = 1, correct = 0;
   while(turn == 1){
      cout<<"Spin the wheel (1), buy a vowel (2), or solve the puzzle (3): ";
      cin>>choice;
      if(choice == 1){
	 turn = spinWheel(&turnCash, &puzzle, &puzzleBlanks, &guess);
      }
      else if(choice == 2 && **bank >= 10 || choice == 2 && **turnCash >= 10){
	 turn = buyVowel(&bank, &turnCash, &puzzle, &puzzleBlanks, &guess);
      }
      else if(choice == 3){
	 correct = guessPuzzle(&puzzle);
         turn = 0;
      }
      return correct;//tells whether or not puzzle has been solved
      cout<<"Total money: $"<<**bank + **turnCash<<endl;
   }
   addMoney(&bank, &turnCash);
}
/* Function: gameRound
 * Description: calls playerTurn depending on how many players were said to be in the game for however long it takes to win a round.
 * Parameters: int numPlayers, int* bankOne, bankTwo, bankThree, turnCash, string* puzzle, puzzleBlanks, char*  guess
 * Pre-conditions: all arguments are real values.
 * Post-conditions: returns an integer whenever the round is complete.
*/
void gameRound(int numPlayers, int *bankOne, int *bankTwo, int *bankThree, int *turnCash, string *puzzle, string *puzzleBlanks, char *guess){
   convertInitialMessage(&puzzle, &puzzleBlanks);
   int correct = 0;
   while(correct == 0){
      cout<<"Player 1:"<<endl;
      correct = playerTurn(&bankOne, &turnCash, &puzzle, &puzzleBlanks, &guess);
      if(correct == 1)//if puzzle has been solved, this round is over
	 break;
      if(numPlayers == 2){
	 cout<<"Player 2:"<<endl;
         correct = playerTurn(&bankTwo, &turnCash, &puzzle, &puzzleBlanks, &guess);
         if(correct == 1)
	    break;
      }
      if(numPlayers == 3){
	 cout<<"Player 3:"<<endl;
         correct = playerTurn(&bankThree, &turnCash, &puzzle, &puzzleBlanks, &guess);
         if(correct == 1)
	    break;
      }
   }
}
/* Function: determineWinner
 * Description: determines which player won the game
 * Parameters: int bankOne, bankTwo, bankThree
 * Pre-conditions: each bank is filled with the money each player accrued, respectively.
 * Post-conditions: correctly determines winner.
*/
void determineWinner(int bankOne, int bankTwo, int bankThree){
   if(bankOne > bankTwo && bankOne > bankThree)
      cout<<"Player 1 wins!"<<endl;
   else if(bankTwo > bankOne && bankTwo > bankThree)
      cout<<"Player 2 wins!"<<endl;
   else if(bankThree > bankOne && bankThree > bankTwo)
      cout<<"Player 3 wins!"<<endl;
}

/* Function: playGame
 * Description: starts the game.
 * Parameters: int numPlayers, numRounds
 * Pre-conditions: correct number of players and desired rounds
 * Post-conditions: game works properly.
*/
void playGame(int numPlayers, int numRounds){
   int cashOne = 0, cashTwo = 0, cashThree = 0, turnCash = 0, players = numPlayers;
   string puzzle, puzzleBlanks;
   char guess;
   for(int i = 0; i < numRounds; i++){
      cin.ignore();
      cin.clear();
      getPuzzle(&puzzle);
      puzzleBlanks = puzzle;
      gameRound(players, &cashOne, &cashTwo, &cashThree, &turnCash, &puzzle, &puzzleBlanks, &guess);
   }//however many rounds there are, afterwards determine who won.
   determineWinner(cashOne, cashTwo, cashThree);
}

/* Function: main
 * Description: gets the necessary info and starts the starting of the game.
 * Parameters: none
 * Pre-conditions: N/A
 * Post-conditions: N/A
*/
int main(){
   int numPlayers, numRounds;
   getNumPlayers(&numPlayers);
   getNumRounds(&numRounds);
   playGame(numPlayers, numRounds);
   return 0;
}
