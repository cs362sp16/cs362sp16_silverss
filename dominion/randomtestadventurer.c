#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"


#define MAX_TESTS 500

//this function counts the number of treasure cards in the player's hand
int HandTreasure(struct gameState *game, int player){
	int card;
	int x = 0;
	//iterate through players hand to see how many treasure cards they have
	for(int i=0; i<game->handCount[player]; i++){
		card = game->hand[player][i];
		if(card == gold || card == silver || card == copper){
			x++;
		}
	}
	return x;
}


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


		//
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

			//put adventurer card in player's hand
			game.hand[p][0] = adventurer;

			//see how many treasures the player possesses
			int totTreasureStart = fullDeckCount(p, gold, &game) + fullDeckCount(p, silver, &game) + fullDeckCount(p, copper, &game); 

			//in hand treasure count
			int handTreasureStart = HandTreasure(&game, p);
			int deckTreasure = totTreasureStart - handTreasureStart;
			//play the adventurer card and save the return value
			int returnCheck = playCard(0, 0, 0, 0, &game);

			//total number of treasure after playing card
			int totTreasureEnd = fullDeckCount(p, gold, &game) + fullDeckCount(p, silver, &game) + fullDeckCount(p, copper, &game); 
			int handTreasureEnd =  HandTreasure(&game, p);


			//compare values to ensure success
			if(returnCheck != 0){
				printf("Test number: %d player: %d returned bad value for playcard.\n",i,p );
			}
			if(totTreasureStart != totTreasureEnd){
				printf("Test number: %d player: %d didn't have matching total treasure counts\n",i, p );
			}
			//only triggers if deck had 2 or mroe treasures to draw and doesn't do so
			if(handTreasureEnd != handTreasureStart + 2 && deckTreasure >=2){
				printf("Test number: %d player: %d didn't add two treasures to hand\n",i,p );
			}

			endTurn(&game);

		}
	}
	return 0;
}