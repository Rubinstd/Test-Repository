#include <stdio.h>
#include <stdlib.h>
#include <time.h> // contains prototype for function time

enum Status { CONTINUE, WON, LOST };

int rollDice(void); // The rollDice function prototype

int craps(int); // The craps function prototype
int promptWager(int); // The promptWager function prototype.

int main (void)
{
    // The variable to hold the bank balance.
    int bankBalance = 1000;

    // A loop that plays craps games until the user runs out of money.
    while (bankBalance != 0){
      // Runs the craps game by prompting the user continually and calculating the wager values.
      // If the wager is valid (i.e. promptWager returns a value, craps will be played with that wager value).
      bankBalance += craps(promptWager(bankBalance));
    }
}

// The function for prompting the user to enter a wager.
// This function works recursively. If the user does not enter a valid wager,
// The function will re-prompt them to enter another wager.
int promptWager(int bankBalance){
  // The value to store the wager inputted.
  int wager;

  // The prompt for the wager.
  printf("Enter a wager for the next game (Current Bank Balance: %d) : \n", bankBalance);
  // Reading the wager.
  scanf("%d", &wager);

  // Formatting for easier readability.
  puts(" ");

  // Checking if the wager is valid (i.e. if the user has enough money to wager that amount).
  if (bankBalance - wager < 0 || wager < 0){

    // A sassy statement that appears if the user tries to wager more than they have.
    printf("You can't wager that much! Nice try though!\n");

    // Formatting for easier readability.
    puts(" ");

    // Recalling the promptWager function in order to ask for a new wager.
    return promptWager(bankBalance);
  }
  else{
    // If the wager is valid, it is returned from this function.
    return wager;
  }
}

// The crap game function.
// This is copied from the textbook with the single change that if the user wins,
// the function returns a positive value of the wager, and if they lose, it returns
// a negative value of it. This is because in the main function, the return from this is added
// to the bankBalance value, thus calculating right away the new bankBalance with no need for extra code.
int craps(int wager){
  // randomize random number generator using current time
  srand(time(NULL));

  int myPoint; // player must make this point to win
  enum Status gameStatus; // can contain CONTINUE, WON, or LOST
  int sum = rollDice(); // first roll of the dice

  // determine game status based on sum of dice
  switch(sum) {
    // win on first roll
    case 7: // 7 is a winner
    case 11: // 11 is a winner
      gameStatus = WON;
      break;
    // lose on first roll
    case 2: // 2 is a loser
    case 3: // 3 is a loser
    case 12: // 12 is a loser
      gameStatus = LOST;
      break;
    // remember point
    default:
    gameStatus = CONTINUE; // player should keep rolling
    myPoint = sum; // remember the point
    printf("Point is %d\n", myPoint);
    break; // optional
  }

  // while game not complete
  while (CONTINUE == gameStatus) { // player should keep rolling
     sum = rollDice(); // roll dice again

    // determine game status
    if (sum == myPoint) { // win by making point
      gameStatus = WON;
    }
    else {

      if (7 == sum) { // lose by rolling 7
        gameStatus = LOST;
      }

    }
  }

  // display won or lost message
  if (WON == gameStatus) {
    puts("Player wins");

    // Returns positive wager.
    return wager;
  }
  else { // player lost
    puts("Player loses");

    // Returns negative wager.
    return -wager;
  }
}

//Rooll dice, calculate sum and display results.
int rollDice(void){
  int die1 = 1 + (rand() % 6);
  int die2 = 1 + (rand() % 6);

  //Display results of this roll.
  printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
  return die1 + die2;
}
