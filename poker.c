/*============================================================================  
|  Source code: poker.c
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
/*---------------------------- displayHands ----------------------------
    |  Function displayHand(Hands* handsInPlay)
    |
    |  Purpose: Cycles through an array of structures which contain,
	|			an array of Structures (the cards in hand), the total
	|			number of hands in play, number of cards in each hand,
	|			the score of each hand, and if a hand is a winner.
	|			Elements are printed as needed.
    |
    |  @param  Hands* handsInPlay
    |
    |  @return  void
*-------------------------------------------------------------------*/
void displayHands(Hands* handsInPlay){
	int cardToDisplay = MIN_CARDS_HAND;
	int handToDisplay = MIN_HANDS;
	
	
	for(handToDisplay = MIN_HANDS; handToDisplay < handsInPlay->totalHands; handToDisplay++){
		printf("Player #%d: ", handToDisplay + MIN_PLAYERS);
		for(cardToDisplay = MIN_CARDS_HAND; cardToDisplay < handsInPlay->handSize; cardToDisplay++){
			printf("[%c-%s] ", handsInPlay[handToDisplay].cardsInHand[cardToDisplay].rank, handsInPlay[handToDisplay].cardsInHand[cardToDisplay].suit);
		}/* End for loop */
		
		displayRanks(handsInPlay[handToDisplay].handScore);
		
		if(handsInPlay[handToDisplay].winner == TRUE){
			printf(" - Winner! ");
		}/* End if */
		
		printf("\n");
	}/* End for loop */
}/* End displayHand */

/*---------------------------- displayRanks ----------------------------
    |  Function displayRanks(int rankOfHand)
    |
    |  Purpose: Accepts an int containing the numerical value of the
	|			hand.  Each hand rank is given a value as shown below.
	|			The function checks the incoming rank and prints the 
	|			appropriate rank.
	|		
	|			Straight Flush	- 22
	|			Four of a kind	- 21
	|			Full House		- 20 
	|			Flush			- 19
	|			Straight		- 18 
	|			Three of a kind	- 17
	|			Two Pairs		- 16
	|			Pair			- 15
	|			High Card		- value of highest rank (max = 14 for Ace)
    |
    |  @param  Hands* handsInPlay
    |
    |  @return  void
*-------------------------------------------------------------------*/
void displayRanks(int rankOfHand){
	if(rankOfHand == STRAIGHT_FLUSH){
		printf("- Straight Flush");
	}/* End if */
	else if(rankOfHand == FOUR_OF_A_KIND){
		printf("- Four of a kind");
	}/* End else if */
	else if(rankOfHand == FULL_HOUSE){
		printf("- Full House");
	}/* End else if */
	else if(rankOfHand == FLUSH){
		printf("- Flush");
	}/* End else if */
	else if(rankOfHand == STRAIGHT){
		printf("- Straight");
	}/* End else if */
	else if(rankOfHand == THREE_OF_A_KIND){
		printf("- Three of a kind");
	}/* End else if */
	else if(rankOfHand == TWO_PAIRS){
		printf("- Two Pairs");
	}/* End else if */
	else if(rankOfHand == PAIR){
		printf("- Pair");
	}/* End else if */
	else if(rankOfHand <= PAIR && rankOfHand > HAND_SCORE_INIT){
		printf("- High Card");
	}/* End else if */
	
}/* End displayRanks */

/*---------------------------- rankHands ----------------------------
    |  Function rankHand(Hands* handsToRank)
    |
    |  Purpose: Calls on functions to check the hand in the array for
	|			the ranking of said hand.  If the function called
	|			returns TRUE (1) then a set value is set for the 
	|			handScore variable of the structure. 
	|		
    |			Straight Flush	- 22
	|			Four of a kind	- 21
	|			Full House		- 20 
	|			Flush			- 19
	|			Straight		- 18 
	|			Three of a kind	- 17
	|			Two Pairs		- 16
	|			Pair			- 15
	|			High Card		- value of highest rank (max = 14 for Ace)
    |  @param  Hands* handsToRank
    |
    |  @return  void
*-------------------------------------------------------------------*/
void rankHands(Hands* handsToRank){
	int currentHand = MIN_CARDS_HAND;
	
	for(currentHand = MIN_CARDS_HAND; currentHand < handsToRank->totalHands; currentHand++){
		if(isStraightFlush(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = STRAIGHT_FLUSH;
		}/* End if - Check Four Of a Kind */
		else if(isFourOfKind(handsToRank[currentHand].cardsInHand) == TRUE){
				handsToRank[currentHand].handScore = FOUR_OF_A_KIND;
		}/* End else if - Check is Full House */
		else if(isFullHouse(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = FULL_HOUSE;
		}/* End else if - Check Flush */
		else if(isFlush(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = FLUSH;
		}/* End else if - Check Straight */
		else if(isStraight(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = STRAIGHT;
		}/* End else if - Check Three Of a Kind */
		else if(isThreeOfKind(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = THREE_OF_A_KIND;
		}/* End else if - check Two Pairs */
		else if(isTwoPairs(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = TWO_PAIRS;
		}/* End else if - check Pair */
		else if(isPair(handsToRank[currentHand].cardsInHand) == TRUE){
			handsToRank[currentHand].handScore = PAIR;
		}/* End else if - check high card */
		else if(isHighCard(handsToRank[currentHand]) == TRUE){
			handsToRank[currentHand].handScore = handsToRank[currentHand].cardsInHand[CARD_FIVE].cardValue;
		}/* End else if */
	}/* End for loop */
}/* End rankHands */

/*---------------------------- sortHands ----------------------------
    |  Function sortHands(Hands* handsToSort)
    |
    |  Purpose: Cycles through the array of hands, each hand cycles
	|			through the array of cards to sort the hands.
	|			An implementation of bubble sort is used.  
	|			Each card(Card 1) is compared to every card(Card 2) and is 
	|			swapped if Card 2 is less than Card 1.  More information
	|			on the sort and it's implementation can be found here:
	|			https://www.geeksforgeeks.org/bubble-sort/
	|
	|
    |  @param  Hands* handsToSort
    |
    |  @return  void
*-------------------------------------------------------------------*/
void sortHands(Hands* handsToSort){
	int compareCard = MIN_CARDS_HAND;
	int handInQuestion = MIN_HANDS;
	int cardInQuestion = MIN_CARDS_HAND;
	Cards tempCard;
	
	for(handInQuestion = MIN_HANDS; handInQuestion < handsToSort->totalHands; handInQuestion++){
		for(cardInQuestion = MIN_CARDS_HAND; cardInQuestion < handsToSort->handSize - SORT_COMP; cardInQuestion++){
			for(compareCard = MIN_CARDS_HAND; compareCard < handsToSort->handSize - cardInQuestion - SORT_COMP; compareCard++){
				if(handsToSort[handInQuestion].cardsInHand[compareCard].cardValue > handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].cardValue){
					/* Set tempCard (original card) */
					tempCard.rank = handsToSort[handInQuestion].cardsInHand[compareCard].rank;
					tempCard.suit = handsToSort[handInQuestion].cardsInHand[compareCard].suit;
					tempCard.cardValue = handsToSort[handInQuestion].cardsInHand[compareCard].cardValue;
					/* Set smaller card to original card */
					handsToSort[handInQuestion].cardsInHand[compareCard].rank = handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].rank;
					handsToSort[handInQuestion].cardsInHand[compareCard].suit = handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].suit;
					handsToSort[handInQuestion].cardsInHand[compareCard].cardValue = handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].cardValue;
					/* Set larger card to original card + SORT_COMP*/
					handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].rank = tempCard.rank;
					handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].suit = tempCard.suit;
					handsToSort[handInQuestion].cardsInHand[compareCard + SORT_COMP].cardValue = tempCard.cardValue;
				}/* End if */
			}/* End for loop */
		}/* End for loop */
	}/* End for loop */
	displayHands(handsToSort);
}/* End sortHand */

/*---------------------------- tiebreaker ----------------------------
    |  Function tiebreaker(Hands* handOne, Hands* winner)
    |
    |  Purpose: If a tie is found in determining a winner
	|			both hands are declared winners and the winning hand
	|			is swapped to the new hand. 
	|
    |  @param  Hands* handOne, Hands* winner
    |
    |  @return  void
*-------------------------------------------------------------------*/
void tiebreaker(Hands* handOne, Hands* winner){
	handOne->winner = TRUE;
	winner = handOne;
}/* End tiebreaker */

/*---------------------------- winningHand ----------------------------
    |  Function winningHand(Hands* rankedHands)
    |
    |  Purpose: Cycles through an array of hands and compares the 
	|			handScore which equates to a hand ranking to determine
	|			the largest score or winning hand.  If a tie is found
	|			the two hands are sent to a tiebreaking function.  Else
	|			a set winningHand is compared to each hand and at the
	|			end the winningHand is declared the winner. 
	|
	|			Straight Flush	- 22
	|			Four of a kind	- 21
	|			Full House		- 20 
	|			Flush			- 19
	|			Straight		- 18 
	|			Three of a kind	- 17
	|			Two Pairs		- 16
	|			Pair			- 15
	|			High Card		- value of highest rank (max = 14 for Ace)
	|
    |  @param  Hands* rankedHands
    |
    |  @return  void
*-------------------------------------------------------------------*/
void winningHand(Hands* rankedHands){
	Hands *winningHand = &rankedHands[MIN_HANDS];
	int handToCompare = WIN_HANDS_INIT;
	int recheckHands = WIN_HANDS_INIT;
	
	for(handToCompare = WIN_HANDS_INIT; handToCompare < rankedHands->handSize; handToCompare++){
		if(rankedHands[handToCompare].handScore == winningHand->handScore){
			tiebreaker(&rankedHands[handToCompare], winningHand);
		}/* End if */
		else if(rankedHands[handToCompare].handScore > winningHand->handScore){
			for(recheckHands = WIN_HANDS_INIT; recheckHands < handToCompare; recheckHands++){
				if(rankedHands[recheckHands].handScore == winningHand->handScore){
					rankedHands[recheckHands].winner = FALSE;
				}/* End if */
			}/* End for loop */
			winningHand->winner = FALSE;
			winningHand = &rankedHands[handToCompare];
		}/* End else if */
	}/* End for loop */
	winningHand->winner = TRUE;
}/* End winningHand */

/*---------------------------- isStraightFlush ----------------------------
    |  Function isStraightFlush(Cards* cardsInHand)
    |
    |  Purpose: Calls isStraight and isFlush and if both return TRUE
	|			then the hand is a Straight Flush
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isStraightFlush(Cards* cardsInHand){
	if(isStraight(cardsInHand) == TRUE && isFlush(cardsInHand) == TRUE){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isStraightFlush */

/*---------------------------- isFourOfKind ----------------------------
    |  Function isFourOfKind(Cards* cardsInHand)
    |
    |  Purpose: Checks if the rank of card one the same as the rank card four 
	|			or if the rank of card two is the same as the rank of card five
	|			 and if either of these are true then the hand is a four of a kind.
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isFourOfKind(Cards* cardsInHand){
	if((cardsInHand[CARD_ONE].cardValue == cardsInHand[CARD_FOUR].cardValue) || (cardsInHand[CARD_TWO].cardValue == cardsInHand[CARD_FIVE].cardValue)){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isFourOfKind */

/*---------------------------- isFullHouse ----------------------------
    |  Function isFullHouse(Cards* cardsInHand)
    |
    |  Purpose: Checks if the rank of card 1 is equal to the rank of card three 
	|			(3 of a kind) and if the rank of card four is equal to the rank 
	|			of card five (pair) or if the rank of card three is equal to the rank
	|			of card five (3 of a kind) and the rank of card one is equal to 
	|			the rank of card two (pair). If either of these are true then 
	|			the hand is a full house.
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isFullHouse(Cards* cardsInHand){
	if(((cardsInHand[CARD_ONE].cardValue == cardsInHand[CARD_THREE].cardValue) && (cardsInHand[CARD_FOUR].cardValue == cardsInHand[CARD_FIVE].cardValue)) || 
	   ((cardsInHand[CARD_THREE].cardValue == cardsInHand[CARD_FIVE].cardValue) && (cardsInHand[CARD_ONE].cardValue == cardsInHand[CARD_TWO].cardValue))){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isFullHouse */

/*---------------------------- isFlush ----------------------------
    |  Function isFlush(Cards* cardsInHand)
    |
    |  Purpose: Cycles through the array of cards and compares the
	|			suit of each card using strcmp since I have the 
	|			symbol codes for suits in place of the variables.
	|			If all 5 cards have the same suit then the hand is
	|			a Flush.
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isFlush(Cards* cardsInHand){
	int suitCount = SUIT_CHECK;
	int cardNum = MIN_CARDS_HAND;
	
	for(cardNum = MIN_CARDS_HAND; cardNum < OVER_RIDE_CARDS_HAND; cardNum++){
		if(strcmp(cardsInHand[CARD_ONE].suit, cardsInHand[cardNum].suit) == SUIT_CHECK){
			suitCount++;
		}/* End if */
	}/* End for loop */
	if(suitCount == OVER_RIDE_CARDS_HAND){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isFlush */

/*---------------------------- isStraight ----------------------------
    |  Function isStraight(Cards* cardsInHand)
    |
    |  Purpose: Since the array of Cards are sorted, to check if 
	|			a hand is consecutive can be accomplished by adding 
	|			4 to card 1 and checking to ensure a three of a kind
	|			and a pair is not in the hand.  If these conditions 
	|			are met then the hand is a Straight.  Also allows an
	|			Ace to be high card if it would cause a straight. 
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isStraight(Cards* cardsInHand){
	if(cardsInHand[CARD_FIVE].cardValue == HIGH_ACE && cardsInHand[CARD_FOUR].cardValue == FIVE_CHECK){
		if(ACE + cardsInHand[CARD_THREE].cardValue == cardsInHand[CARD_FOUR].cardValue && isThreeOfKind(cardsInHand) == FALSE && isPair(cardsInHand) == FALSE){
			return TRUE;
		}/* End nested if */
		else{
			return FALSE;
		}/* End else */
	}/* End if */
	if(cardsInHand[CARD_ONE].cardValue + CARD_FIVE == cardsInHand[CARD_FIVE].cardValue && isThreeOfKind(cardsInHand) == FALSE && isPair(cardsInHand) == FALSE){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isStraight */

/*---------------------------- isThreeOfKind ----------------------------
    |  Function isThreeOfKind(Cards* cardsInHand)
    |
    |  Purpose: Cycles through the array of cards and compares the
	|			card in the array with the card two indexes ahead,
	|			if the cards are the same rank then the hand is a
	|			three of a kind.		
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isThreeOfKind(Cards* cardsInHand){
	int cardToCompare = MIN_CARDS_HAND;
	
	for(cardToCompare = MIN_CARDS_HAND; cardToCompare < OVER_RIDE_CARDS_HAND - THREE_KIND_COMP; cardToCompare++){
		if(cardsInHand[cardToCompare].cardValue == cardsInHand[cardToCompare + THREE_KIND_COMP].cardValue){
			return TRUE;
		}/* End if */
	}/* End for loop */
	return FALSE;
}/* End isThreeOfKind */

/*---------------------------- isTwoPairs ----------------------------
    |  Function isTwoPairs(Cards* cardsInHand)
    |
    |  Purpose: Cycles through the array of cards and compares the
	|			rank of each card to the rank of the next card.
	|			If a pair is found then a counter is incremented.
	|			Outside the loop the counter is checked, if the 
	|			counter reads two, the hand has two pairs.
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isTwoPairs(Cards* cardsInHand){
	int pairCount = PAIR_COUNT_INIT;
	int cardToCompare = MIN_CARDS_HAND;
	
	for(cardToCompare = MIN_CARDS_HAND; cardToCompare < OVER_RIDE_CARDS_HAND - PAIR_COMP; cardToCompare++){
		if(cardsInHand[cardToCompare].cardValue == cardsInHand[cardToCompare + PAIR_COMP].cardValue){
			pairCount++;
		}/* End if */
	}/* End for loop */
	if(pairCount == TWO_PAIR_CHECK){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isTwoPairs */

/*---------------------------- isPair ----------------------------
    |  Function isPair(Cards* cardsInHand)
    |
    |  Purpose: Cycles through the array of cards and compares the
	|			rank of each card to the rank of the next card.
	|			If there is a pair then the hand contains a pair.
	|
    |  @param  Cards* cardsInHand
    |
    |  @return  int
*-------------------------------------------------------------------*/	
int isPair(Cards* cardsInHand){
	int cardToCompare = MIN_CARDS_HAND;
	
	for(cardToCompare = MIN_CARDS_HAND; cardToCompare < OVER_RIDE_CARDS_HAND - PAIR_COMP; cardToCompare++){
		if((cardsInHand[cardToCompare].cardValue == cardsInHand[cardToCompare + PAIR_COMP].cardValue)){
			return TRUE;
		}/* End if */
	}/* End for loop */
	return FALSE;
}/* End isPair */

/*---------------------------- isHighCard ----------------------------
    |  Function isHighCard(Hands handCheck)
    |
    |  Purpose: If a the handScore has not been changed then the 
	|			hand rank is High Card.
	|
    |  @param  Hands handCheck
    |
    |  @return  int
*-------------------------------------------------------------------*/
int isHighCard(Hands handCheck){
	if(handCheck.handScore == HAND_SCORE_INIT){
		return TRUE;
	}/* End if */
	else{
		return FALSE;
	}/* End else */
}/* End isHighCard */ 
