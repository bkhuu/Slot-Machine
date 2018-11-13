// Brandon Khuu G00975967
// CS 262, Lab Section 207
// Project 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Call random() function for each reel and store the stop in pass by reference parameter
void SpinReels(int *a, int *b, int *c);

// Display the symbols on each reel based on a, b, c values
void DisplaySpin(int a, int b, int c);

// Calculate payout from amount bet and reel positions
unsigned int CalculatePayout(int bet, int a, int b, int c);

void SpinReels(int *a, int *b, int *c) {
   *a = random() % 40; // Set a to a random value between 0 and 40
   *b = random() % 40; // Set b to a random value between 0 and 40
   *c = random() % 40; // Set c to a random value between 0 and 40
}

void DisplaySpin(int a, int b, int c) {
   int reels[3] = {a, b, c};
   int i;
   for (i = 0; i < 3; i++) {
      if (reels[i] == 0) { // If reels[i] is 0, then the symbol will be the Cherry
	 if (i == 2) {
	    printf("CHERRY\n");
	 }
	 else {
            printf("CHERRY    \b");
	 }
      }
      else if (reels[i] > 0 && reels[i] < 4) { // If reels[i] is 1, 2, or 3, then the symbol will be the Double Bar
	 if (i == 2) {
	    printf("DOUBLE BAR\n");
	 }
	 else {
            printf("DOUBLE BAR    \b");
	 }
      }
      else if (reels[i] > 3 && reels[i] < 8) { // If reels[i] is 4, 5, 6, or 7, then the symbol will be the Single Bar
	 if (i == 2) {
	    printf("SINGLE BAR\n");
	 }
	 else {
            printf("SINGLE BAR    \b");
	 }
      }
      else { // If reels[i] is 8..39 inclusive, then the symbol will be the Blank
	 if (i == 2) {
	    printf("BLANK\n");
	 }
	 else {
            printf("BLANK    \b");
	 }
      }
   }
}

unsigned int CalculatePayout(int bet, int a, int b, int c) {
   unsigned int payout = 0;
   int symbols[3] = {a, b, c};
   // Add the multipliers if there is at least one Blank symbol
   if (a > 7 || b > 7 || c > 7) {
      int j;
      for (j = 0; j < 3; j++) {
         if (symbols[j] == 0) { // Cherry symbol is worth 3x
            payout += 3;
         }
         else if (symbols[j] > 0 && symbols[j] < 4) { // Double Bar symbol is worth 2x
            payout += 2; 
         }
         else if (symbols[j] > 3 && symbols[j] < 8) { // Single Bar symbol is worth 1x
            payout += 1;
         }
      }
   }
   // Multiply the multipliers if there are no Blank symbols
   else if (a < 8 && b < 8 && c < 8) {
      int k;
      for (k = 0; k < 3; k++) {
         if (symbols[k] == 0) { // Cherry symbol is worth 3x
            if (payout == 0) {
               payout += 3;
	    }
	    else {
               payout *= 3;
	    }
         }
         else if (symbols[k] > 0 && symbols[k] < 4) { // Double Bar symbol is worth 2x
            if (payout == 0) {
               payout += 2;
	    }
	    else {
               payout *= 2;
	    }
         }
      }
   }
   return (payout * bet);
}

int main()
{
   char input[20];  // A buffer to hold the input from the keyboard
   int seed = 0;   // A variable to hold the seed
   printf("Seed the random number generator -> "); // Prompt the user for a seed
   fgets(input, 20, stdin);  // Read the input from the keyboard and store it in the input variable
   sscanf(input, "%d", &seed);  // Extract the integer value from input and store it in seed
   srandom(seed);

   int on = 1; // Loop condition for the user to continue playing
   char answer = 0; // A variable to hold the answer
   int bet = 0; // A variable to hold the bet
   int bankroll = 100; // A variable to hold the bankroll
   int a = 0; // A variable to hold the value of the first reel
   int b = 0; // A variable to hold the value of the second reel
   int c = 0; // A variable to hold the value of the third reel
   
   // Loop until the user quits the game or runs out of money
   while (on) {

      int betcheck = 1; // Loop condition to check for valid bets
      int answercheck = 1; // Loop condition to check for valid answers

      printf("Current bankroll: $%d\n", bankroll);

      // Loop until the user enters a valid bet     
      while (betcheck) {
	 int maxbet = 10; // A variable to keep track of the maximum bet
	 // Adjust maxbet if bankroll falls below $10
	 if (bankroll < 10) {
            maxbet = bankroll;
	 }
         printf("Enter a bet between $1 and $%d -> ", maxbet); // Prompt the user for a bet amount
         fgets(input, 20, stdin);  // Read the input from the keyboard and store it in the input variable
         sscanf(input, "%d", &bet);  // Extract the integer value from input and store it in bet
         
	 // Check if a valid bet is entered
	 if (bet > 0 && bet < 11) {
	    if (bet > bankroll) {
               printf("Oops! Bet more than the bankroll...\n");
	    }
	    else {
               bankroll -= bet; // Decrease the bankroll by the amount bet
               betcheck = 0; // Exit the loop
	    }
	    // Exit the game if the user is out of money
	    if (bankroll == 0) {
               on = 0;
	       answercheck = 0;
            }
         }
	 else {
            printf("Not between $1 and $10...\n");
	 }
      }

      SpinReels(&a, &b, &c); // spin the reels

      printf("The reels are spinning!\n\n");

      DisplaySpin(a, b, c); // display the symbols

      printf("\n");

      printf("Payout: $%u\n", CalculatePayout(bet, a, b, c)); // display the payout

      bankroll += CalculatePayout(bet, a, b, c); // add the payout to the bankroll
      printf("Current bankroll: $%d\n", bankroll); 

      printf("\n");

      // Loop until the user enters a valid answer
      while (answercheck) {
         printf("Play again? (Y/N) -> "); // Ask if the user wants to continue playing
         fgets(input, 20, stdin);  // Read the input from the keyboard and store it in the input variable
         sscanf(input, "%c", &answer);  // Extract the character value from input and store it in answer

         if (answer == 'y' || answer == 'Y') {
	    answercheck = 0; // exit the loop
         }
         else if (answer == 'n' || answer == 'N') {
	    answercheck = 0;
            on = 0; // exit the game
         }	 
         else {
            printf("Not (Y/N)...\n");
         }
      }
   }
   printf("Thanks for playing! Final bankroll: $%d\n", bankroll);
   return 0;
}
