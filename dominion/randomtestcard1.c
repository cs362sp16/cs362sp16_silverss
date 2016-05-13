#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"


#define MAX_TESTS 500

int main(int argc, char *argv[]){

	//make sure correct number of arguments are provided
	if(argc > 2){
		printf("Too many arguments, only one expected.\n");
		return -1;
	}
	if(argc < 2){
		printf("Not enough arguments, need a random seed.\n");
		return -1;
	}

	//select kingdom cards
	int k[10] = {adventurer, gardens, village, smithy, sea_hag, mine, minion, great_hall, embargo, cutpurse};

	//store user provided seed
	int seed = argv[1];
	struct gameState game;

	//loop for multiple tests
	for(int i=0; i<MAX_TESTS;i++){

		//get random number of players between 2 and MAX_PLAYERS
		int players = (rand() % MAX_PLAYERS);
		if(players < 2){
			players = players + 2;
		}
		//initialize game
		initializeGame(players, k, seed, &game);

		for(int p = 0; p < players; p++){

			//give the players decks, hands and discard counts
			game.deckCount[p] = rand() % MAX_DECK;
			game.handCount[p] = rand() % MAX_HAND;
			game.discardCount[p] = rand() % MAX_DECK;

			//1 in 4 chance to have an empty deck to see function behavior 
			int oneInFour = rand() % 4;
			if(oneInFour == 0){
				game.deckCount[p] = 0;
			}

			//put smithy card in player's hand
			game.hand[p][0] = smithy;
			//count number of cards in hand and deck
			int handSize = numHandCards(&game);
			int deckSize = game.deckCount[p] + game.discardCount[p];

			//play the smithy card and save the return value
			int returnCheck = playCard(0, 0, 0, 0, &game);

			//compare values to ensure success
			if(returnCheck != 0){
				printf("Test number: %d player: %d returned bad value for playcard.\n",i,p );
			}
			//make sure player drew 3 cards if able to
			if(numHandCards(&game) != handSize + 2 && deckSize >= 3){
				printf("Test: %d Player: %d did not draw 3 cards\n",i,p );
			}

			endTurn(&game);

		}


	}
	return 0;
}