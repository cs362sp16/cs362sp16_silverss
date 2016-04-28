#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


#define DEBUG 0
#define NOISY_TEST 1

int main(){

	struct gameState Game;
	int FailCheck = 0;
	int a[10] = {smithy, great_hall, gardens, minion, village, adventurer, sea_hag, mine, feast, remodel};
	int numPlayers = 3;
	int seed = 42;
	//setup a game so the card to be tested can be played
	initializeGame(numPlayers, a, seed, &Game);

	Game.hand[0][0] = village;
	int startActions = Game.numActions;
	int startHandCount = numHandCards(&Game);

	if(playCard(0,0,0,0,&Game) != 0){
		printf("ERROR: card was not played\n");
		FailCheck = 1;
	}

	int endActions = Game.numActions;
	int endHandCount = numHandCards(&Game);

	//check number cards in hand, village gives +1 but then is discarded, giving a net 0
	if(endHandCount != startHandCount){
		printf("ERROR: smithy drew the wrong number of cards, or was not discarded\n");
		FailCheck = 1;
	}
	//village gains 2 actions, but spends 1 being played, net +1
	if(endActions != startActions +1){
		printf("ERROR: number of actions after play is not correct.\n");
		FailCheck = 1;
	}

	if(FailCheck == 0){
		printf("SUCCESS: village card executes correctly.\n");
	}
	return 0;
	
}