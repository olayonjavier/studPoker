/*============================================================================  
|  Source code: deck.c
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
/*---------------------------- deal ----------------------------
    |  Function deal(Cards *deckToDeal, int numOfCards, int numOfHands, Hands* playingHands)
    |
    |  Purpose: Deal numOfCards to numOfHands from deckToDeal, stores arrays 
	|			of cards in each hand for given number of hands (numOfHands).
	|			Enters initial values for Hands in the loop cycling through 
    |           the hands.
    |
    |  @param  Cards *deckToDeal, int numOfHands, int numOfCards, Hands* playingHands
    |
    |  @return  void
*-------------------------------------------------------------------*/
void deal(Cards *deckToDeal, int numOfCards, int numOfHands, Hands *playingHands){
	int currentHand = MIN_CARDS_HAND;
	int cardToDeal = MIN_CARDS_HAND;
	
    for(currentHand = MIN_CARDS_HAND; currentHand < numOfHands; currentHand++){
		for(cardToDeal = MIN_CARDS_HAND; cardToDeal < numOfCards; cardToDeal++){
			playingHands[currentHand].cardsInHand[cardToDeal].rank = deckToDeal[(currentHand * numOfCards) 
											+ cardToDeal + MIN_CARDS_DECK].rank;
			playingHands[currentHand].cardsInHand[cardToDeal].suit = deckToDeal[(currentHand * numOfCards) 
											+ cardToDeal + MIN_CARDS_DECK].suit;
			playingHands[currentHand].cardsInHand[cardToDeal].cardValue = deckToDeal[(currentHand * numOfCards) 
											+ cardToDeal + MIN_CARDS_DECK].cardValue;
		}/* End nestedfor loop */
		playingHands[currentHand].handSize = numOfCards;
		playingHands[currentHand].handScore = HAND_SCORE_INIT;
		playingHands[currentHand].totalHands = numOfHands;
		playingHands[currentHand].winner = FALSE;
    }/* End for loop */
	displayHands(playingHands);
}/* End deal */

/*---------------------------- displayDeck ----------------------------
    |  Function displayDeck(Cards *deckToDisplay)
    |
    |  Purpose: Cycles through an array of structures whose elements contain 
	|			a char and string for rank and suit respectively.
    |
    |  @param  Cards *deckToDisplay
    |
    |  @return  void
*-------------------------------------------------------------------*/
void displayDeck(Cards *deckToDisplay){
	int cardToDisplay = MIN_CARDS_DECK;
	int newLineCount = NEWLINE_INIT;
	for(cardToDisplay = MIN_CARDS_DECK; cardToDisplay <= MAX_CARDS_DECK; cardToDisplay++){
		printf("[%c-%s] ", deckToDisplay[cardToDisplay].rank, deckToDisplay[cardToDisplay].suit);
		newLineCount++;
		if(newLineCount % NEWLINE == NEWLINE_INIT){
			printf("\n");
		}/* End if */
	}/* End for loop */
}/* End displayDeck */

/*---------------------------- fillDeck ----------------------------
    |  Function fillDeck(Cards *deckToFill)
    |
    |  Purpose:  Accepts an empty array of structures and assigns values
	|			 to each element depending on it's index in the array
    |
    |  @param  Cards *deckToFill
    |
    |  @return  void
*-------------------------------------------------------------------*/
void fillDeck(Cards *deckToFill){
    int cardNum = MIN_CARDS_DECK;
    const char RANKS[] = "0A23456789TJQK";
	
    for(cardNum = MIN_CARDS_DECK; cardNum <= MAX_CARDS_DECK; cardNum++){
		/*Fill in ranks*/
		if(cardNum % RANK_DIVISOR == KING){
			deckToFill[cardNum].rank = RANKS[RANK_DIVISOR];
			deckToFill[cardNum].cardValue = RANK_DIVISOR;
		}/* End if */
		else if(cardNum % RANK_DIVISOR == ACE){
			deckToFill[cardNum].rank = RANKS[ACE];
			deckToFill[cardNum].cardValue = HIGH_ACE;
		}/* End else if */
		else{
			deckToFill[cardNum].rank = RANKS[cardNum % RANK_DIVISOR];
			deckToFill[cardNum].cardValue = cardNum % RANK_DIVISOR;
		}/* End else */
		
		/*Fill in Suits*/
		if(cardNum % SUIT_DIVISOR == HEARTS){
            deckToFill[cardNum].suit = HEART_SYMBOL;
        }/* End if */
        else if(cardNum % SUIT_DIVISOR == DIAMONDS){
            deckToFill[cardNum].suit = DIAMOND_SYMBOL;
        }/* End else if */
        else if(cardNum % SUIT_DIVISOR == CLUBS){
            deckToFill[cardNum].suit = CLUB_SYMBOL;
        }/* End else if */
        else{
            deckToFill[cardNum].suit = SPADE_SYMBOL;
        }/* End else */
    }/* End for loop */
}/* End fillDeck */

/*---------------------------- shuffleDeck ----------------------------
    |  Function shuffleDeck(Cards *deckToShuffle)
    |
    |  Purpose: Shuffles the passed array using the Fisher-Yates algorithm
	|			https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	|			
	|			Each card is placed in a tempCard variable then a card is
	|			replaces the original card and the tempCard is passed to the
	|			location of the card that replaced the original card. 
    |
    |  @param  Cards *deckToShuffle
    |
    |  @return  void
*-------------------------------------------------------------------*/
void shuffleDeck(Cards *deckToShuffle){
	int cardAt = MIN_CARDS_DECK;
    Cards tempCard;
    int cardPulled = rand() % MAX_CARDS_DECK + MIN_CARDS_DECK;
	
    for(cardAt = MIN_CARDS_DECK; cardAt <= MAX_CARDS_DECK; cardAt++){
        tempCard = deckToShuffle[cardAt];
        deckToShuffle[cardAt] = deckToShuffle[cardPulled];
        deckToShuffle[cardPulled] = tempCard;
        cardPulled = rand() % MAX_CARDS_DECK + MIN_CARDS_DECK;
    }/* End for loop */
}/* End shuffleDeck */

