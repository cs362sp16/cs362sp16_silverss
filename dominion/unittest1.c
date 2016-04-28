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
	int n;
	struct gameState Game;

	//should fail, because 6 is greater than MAX_PLAYERS, whoseTurn does not check for this
	for(n = 0; n < 6; n++){
		Game.whoseTurn = n;
		if(whoseTurn(&Game) != n){
			printf("whoseTurn produced an error with 6 players.\n");
			FailCheck = -1;
		}



	}


	for(n = 0; n < 3; n++){
		Game.whoseTurn = n;
		if(whoseTurn(&Game) != n){
			printf("whoseTurn produced an error with 3 players.\n");
			FailCheck = -1;
		}



	}
	if(FailCheck == 0){
		printf("No errors found in whoseTurn function\n");
	}




	return 0;
	
}