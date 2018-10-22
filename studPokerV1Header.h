/*============================================================================  
|  Source code: studPokerV1Header.h
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
#include <stdio.h>
#include <time.h> /* To seed srand() */ 
#include <string.h> /* To compare strings */

/* Error Handling*/
#define ERROR 1
#define ERROR_CODE 0 
#define NO_ERROR 0

/* Input Handling */
#define INPUT_CARDS 1
#define INPUT_HANDS 2 
#define MIN_INPUTS 3

/* Deck Initializes */
#define CARD_RANK_INIT 0
#define KING 0 
#define MAX_CARDS_DECK 52
#define MIN_CARDS_DECK 1



/* Hand Initializes */
#define MAX_CARDS_HAND 13
#define MAX_HANDS 7
#define MIN_CARDS_HAND 0
#define MIN_HANDS 0
#define MIN_PLAYERS 1
#define OVER_RIDE_CARDS_HAND 5

/* Output formatting */
#define NEWLINE 13
#define NEWLINE_INIT 0
#define RANK_DIVISOR 13
#define SUIT_DIVISOR 4

/* Hand Score */
#define ACE 1
#define CARD_ONE 0
#define CARD_TWO 1
#define CARD_THREE 2
#define CARD_FOUR 3
#define CARD_FIVE 4
#define FIVE_CHECK 5 
#define HAND_SCORE_INIT 0
#define HIGH_ACE 14
#define PAIR_COMP 1
#define PAIR_COUNT_INIT 0
#define SORT_COMP 1
#define SUIT_CHECK 0 
#define THREE_KIND_COMP 2 
#define TWO_PAIR_CHECK 2
#define WIN_HANDS_INIT 1

/* Test Cases */
#define INPUT_VALUES 3
#define TEST_HANDS 9


/* Boolean */
#define FALSE 0
#define TRUE 1

/* Unix uses UTF-8 encoding */
#define SPADE_SYMBOL   "\xE2\x99\xA0"
#define CLUB_SYMBOL    "\xE2\x99\xA3"
#define HEART_SYMBOL   "\xE2\x99\xA5"
#define DIAMOND_SYMBOL "\xE2\x99\xA6"

/* enums */
enum SUIT{HEARTS, DIAMONDS, CLUBS, SPADES};
enum HAND_RANKS{PAIR = 15, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

/* Structures */
typedef struct card{
	char rank;
	const char* suit;
	int cardValue;
}Cards;

typedef struct hand{
	Cards cardsInHand[MAX_CARDS_HAND];
	int handSize;
	int handScore;
	int totalHands;
	int winner;
}Hands;

/* mainHands Function Prototypes */
void inputValidation(int*);

/* deck Function Prototypes */
void deal(Cards*, int, int, Hands*);
void displayDeck(Cards*);
void fillDeck(Cards*);
void shuffleDeck(Cards*);

/* poker Function Prototypes */
void displayHands(Hands*);
void displayRanks(int);
void rankHands(Hands*);
void sortHands(Hands*);
void tiebreaker(Hands*, Hands*);
void winningHand(Hands*);

/* poker Function: Hand Ranking Prototypes */
int isStraightFlush(Cards*);
int isFourOfKind(Cards*);
int isFullHouse(Cards*);
int isFlush(Cards*);
int isStraight(Cards*);
int isThreeOfKind(Cards*);
int isTwoPairs(Cards*);
int isPair(Cards*);
int isHighCard(Hands);

/* testCases Function Prototypes */
void testCases();
