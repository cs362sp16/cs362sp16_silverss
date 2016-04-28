#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


#define DEBUG 0
#define NOISY_TEST 1

int main(){
	int FailCheck = 0;
	int supplyPos = 5;
	struct gameState Game;
	Game.supplyCount[supplyPos] = 5; // results in a card cost of 3, determined by commented-out printf statements below
	Game.coins = 10;
	Game.numBuys = 1;
	//printf("supplyPos value: %d\n",Game.supplyCount[supplyPos] );
	//printf("card cost value: %d\n",getCost(supplyPos) );

	if(buyCard(supplyPos, &Game) != 0){
		printf("buyCard failed on first buy attempt\n");
		FailCheck = 1;
	}

	//check to see if game will allow second buy
	if(buyCard(supplyPos, &Game) != -1){
		printf("buyCard allowed a second buy attempt\n");
		FailCheck = 1;
	}

	//see if can buy without enough coins
	Game.coins = 0;
	Game.numBuys =1;

	if(buyCard(supplyPos, &Game) != -1){
		printf("buyCard allowed buy without enough coin\n");
		FailCheck = 1;
	}
	if(FailCheck == 0){
		printf("No errors found in buyCard function\n");
	}




	return 0;
	
}