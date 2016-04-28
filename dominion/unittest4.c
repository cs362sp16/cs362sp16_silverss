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
	struct gameState Game;
	int testCard = 7;

	Game.supplyCount[testCard] =12;

	if(supplyCount(testCard, &Game) != 12){
		printf("Error in supplyCount function\n");
	}
	if(FailCheck == 0){
		printf("No errors found in supplyCount function\n");
	}

	return 0;
}