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
	int a[10] = {smithy, great_hall, gardens, minion, village, salvager, sea_hag, mine, feast, remodel};
	int numPlayers = 3;
	int seed = 42;

	initializeGame(numPlayers, a, seed, &Game);

	Game.hand[0][0] = salvager;
	Game.hand[0][1] = smithy;
	int startBuys = Game.numBuys;
	int startHandCount = numHandCards(&Game);
	int startCoins = Game.coins;

	if(playCard(0,1,0,0,&Game) != 0){
		printf("ERROR: card was not played\n");
		FailCheck = 1;
	}

	int endBuys = Game.numBuys;
	int endHandCount = numHandCards(&Game);
	int endCoins = Game.coins;

	//should gain 1 buy
	if(endBuys != startBuys +1){
		printf("ERROR: salvager did not add a buy.\n");
		FailCheck = 1;
	}
	printf("startcoins: %d endCoins: %d \n",startCoins,endCoins );
	
	//trash smithy which costs 4, should gain 4 coins
	if(endCoins != startCoins + 4){
		printf("ERROR: coins not added equal to trashed card's cost.\n");
		FailCheck = 1;
	}

	//hand should have 2 fewer cards
	if(endHandCount != startHandCount -2){
		printf("ERROR: cards not trashed or discarded correctly.\n");
		FailCheck = 1;
	}

	if(FailCheck == 0){
		printf("SUCCESS: salvager card played correctly.\n");
	}
	{
		/* code */
	}
	return 0;
	
}