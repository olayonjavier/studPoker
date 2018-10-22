/*============================================================================  
|  Source code: testCases.c
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


/*---------------------------- testCases ----------------------------
    |  Function testCases()
    |
    |  Purpose: Opens a text file which contains a series of "cards
	|			reads the file, and assigns the values to cards in
	|			hands.  Then calls to display the hand, as well as
	|			rank the hands.
	|
    |  @param  none
    |
    |  @return  void
*-------------------------------------------------------------------*/
void testCases(){
	Hands testCases[TEST_HANDS];
	int handToTest = MIN_HANDS;
	int cardToInput = MIN_CARDS_HAND;
	FILE *fp;
	fp = fopen("testCases.txt", "r");
	char inputRank;
	char inputSuit;
	int inputCardValue;
	
	for(handToTest = MIN_HANDS; handToTest < TEST_HANDS; handToTest++){
		testCases[handToTest].totalHands = TEST_HANDS;
		testCases[handToTest].handSize = OVER_RIDE_CARDS_HAND;
		testCases[handToTest].handScore = HAND_SCORE_INIT;
		testCases[handToTest].winner = FALSE;
	}/* End for */
	
	handToTest = MIN_HANDS;
	
	if(fp == NULL){
		printf("No file exists");
	}/* End if */
	while(fscanf(fp, "%c %c %d ", &inputRank, &inputSuit, &inputCardValue) == INPUT_VALUES){
		/* Input ranks */
		testCases[handToTest].cardsInHand[cardToInput].rank = inputRank;
		
		/*Input suits*/
		if(inputSuit == 'H'){
            testCases[handToTest].cardsInHand[cardToInput].suit = HEART_SYMBOL;
        }/* End if */
        else if(inputSuit == 'D'){
            testCases[handToTest].cardsInHand[cardToInput].suit = DIAMOND_SYMBOL;
        }/* End else if */
        else if(inputSuit == 'C'){
            testCases[handToTest].cardsInHand[cardToInput].suit = CLUB_SYMBOL;
        }/* End else if */
        else{
            testCases[handToTest].cardsInHand[cardToInput].suit = SPADE_SYMBOL;
        }/* End else */
		
		/* Input card values */
		testCases[handToTest].cardsInHand[cardToInput].cardValue = inputCardValue;
		
		/* Hand Management */
		cardToInput++;
		if(cardToInput == testCases[handToTest].handSize){
			handToTest++;
			cardToInput = MIN_CARDS_HAND;
		}/* End if */
	}/* End while */
	fclose(fp);
	
	rankHands(testCases);
	displayHands(testCases);
}/* End testCases Function */