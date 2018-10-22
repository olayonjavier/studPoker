/*============================================================================  
|  Source code: mainHands.c
|       Author: Javier Olayon 
|   Student ID: 5683255  
|   Assignment: Program #4 - Stud Poker
|  
|       Course: COP4338 Programming 3  
|      Section: U04  
|   Instructor: William Feild  
|     Due Date: 3/20/18, at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|  
|     Language: C 
|  Compile/Run: With makefile: 
|				make
|				./poker.out cards hands 
|				where cards = number of cards per hand (will always override to 5)
|				and hands = number of hands 1-7
|				Ex: ./poker.out asd 5
|				Without makefile:
|				gcc mainHands.c deck.c poker.c -o poker.out
|               ./poker.out 5 5 
|  +-------------------------------------------------------------------------  
|  
|  Description: Create a deck, display the deck, shuffle the deck, display the
|               shuffled deck, accept command line arguments, fully validate
|				the input, deal the user defined amount of cards from the top
|				of the shuffled deck to the user defined amount of hands, sort
|				the cards in each hand, determine the hand ranking and determine
|				a winner for the poker game.
|
|                  
|        Input: Command Line inputs 2 integers, the first integer defines the 
|               number of cards per hand, the second integer defines the 
|               number of hands to deal to.  
|               
|               Input is validated to ensure it's within the range [1-7], 
|               ensure the data type is correct, and ensure the product of the
|               number of cards and number hands does not go over 52.  Errors 
|               will be pushed to the user to explain why the input was 
|               incorrect.
|  
|       Output: The original ordered deck is displayed as well as the shuffled
|				deck, followed by the user defined number of hands and user 
|				defined amount of cards per hand.  The sorted hands will be
|				displayed after, followed by the ranking of the hand, then 
|				the winner will be determined followed by test hands to show
|				that the ranking system works.
|  
|     Process:	An array of card structures is created in main and passed 
|				to fillDeck	here each element of the array is filled with a 
|				char, string, and int.  The char is the visual rank of the card
|				the string is the Suit and the int is the numerical rank of the
|				card.  The ordered deck is displayed then the same array is 
|				passed to shuffleDeck which shuffles using the Fisher-Yates 
|				algorithm.  Command line arguments are validated then they are 
|				passed to deal.  Deal loops for the number of hands which is an 
|				array of size cards per	hand.  Hands are structures that  contain
|				an array or cards, handSize, handRank, winner, and totalHands. 
|				DisplayHands uses the same algorithm as displayDeck but is fine 
|				tuned to print hands.  Hands are sorted using a bubble sort, a
|				series of if statements that call functions are used to determine
|				the hand rank and a value is assigned based on the rank.  The rank
|				determines the winner.   
|				
|   Required Features Not Included:  
|				
|  
|   Known Bugs: 
|  *======================================================================*/
#include "studPokerV1Header.h"


int main(int argc, char* argv[]){
	srand(time(NULL));
	
	if(argc != MIN_INPUTS){
		printf("Exactly two values must be inputed.\n");
		return ERROR;
	}/* End if */
	int inputedValues[MIN_INPUTS];
    sscanf(argv[INPUT_CARDS], "%d", &inputedValues[INPUT_CARDS]);
    sscanf(argv[INPUT_HANDS], "%d", &inputedValues[INPUT_HANDS]);
    inputValidation(inputedValues);
    const int inputCards = OVER_RIDE_CARDS_HAND;
	const int inputHands = inputedValues[INPUT_HANDS];
	
	
    /* Check command line values*/
    if(inputedValues[ERROR_CODE] == ERROR){
		return ERROR;
    }/* End if */

	Cards deck[MAX_CARDS_DECK];
	Hands players[inputHands];
	
	printf("Original Ordered Deck:\n");
	fillDeck(deck);
	displayDeck(deck);
	
	printf("\nRandomly Shuffled Deck:\n");
	shuffleDeck(deck);
	displayDeck(deck);
	
	printf("\nPlayer Hands: (dealt from top/front of deck)\n");
	deal(deck, inputCards, inputHands, players);
	printf("\nPlayer Hands: Sorted\n");
	sortHands(players);
	printf("\nPlayer Hands: Ranked\n");
	rankHands(players);
	displayHands(players);
	
	printf("\nPlayer Hands: Winner\n");
	winningHand(players);
	displayHands(players);
	
	printf("\nPoker Hands: test\n");
	testCases();
	
	return (NO_ERROR);
}/* End main function */

/*---------------------------- inputValidation ----------------------------
    |  Function inputValidation(int *inputedValues)
    |
    |  Purpose: Accepts elements of argv passed through variables,
	|			numOfInnputs and inputedValues in order to validate the
	|			command line arguments and ensure they are within ranges,
	|			and the correct data type.  
	|			
	|			OVERRIDE:
	|			No matter the input for cards, 5 cards are passed.
    |
    |  @param  int *inputedValues
    |
    |  @return  void
*-------------------------------------------------------------------*/
void inputValidation(int* inputedValues){
    /*int numOfCards = inputedValues[INPUT_CARDS];*/
    int numOfHands = inputedValues[INPUT_HANDS];
	
    /*if(numOfCards < MIN_CARDS_DECK || numOfCards > MAX_CARDS_HAND){
		printf("Values for cards must be between %d and %d.\n", 
				MIN_CARDS_DECK, MAX_CARDS_HAND);
		inputedValues[ERROR_CODE] = ERROR;
    }/* End if */
    if(numOfHands < MIN_PLAYERS || numOfHands > MAX_HANDS){
		printf("Values for hands must be between %d and %d.\n", 
				MIN_PLAYERS, MAX_HANDS);
		inputedValues[ERROR_CODE] = ERROR;
    }/* End else if */
    /*else if((numOfCards * numOfHands) > MAX_CARDS_DECK){
		printf("Not enough cards to deal %d cards to %d hands.\n", 
				numOfCards, numOfHands);
		inputedValues[ERROR_CODE] = ERROR;
    }/* End else if */
    else{
		inputedValues[ERROR_CODE] = NO_ERROR;
    }/* End else */
}/* End inputValidation */

