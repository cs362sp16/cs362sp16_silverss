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

	initializeGame(numPlayers, a, seed, &Game);

	Game.hand[0][0] = sea_hag;
	int startHandCount = numHandCards(&Game);
	int startActions = Game.numActions;
	if(playCard(0,0,0,0,&Game) != 0){
		printf("ERROR: card was not played\n");
		FailCheck = 1;
	}

	int endHandCount = numHandCards(&Game);
	int endActions = Game.numActions;
	//should have one less card
	if(endHandCount != startHandCount -1){
		printf("ERROR: sea_hag was not discarded.\n");
		FailCheck = 1;
	}

	if(endActions != startActions -1){
		printf("ERROR: did not use an action.\n");
		FailCheck = 1;
	}

	int curseCheck = 0;
	int i;
	//see if top cards of other players' decks are curses
	for(i=0;i<3;i++){
		if(i != Game.whoseTurn){
			printf("top card: %d\n",Game.deck[i][Game.deckCount[i]-1]);
			if(Game.deck[i][Game.deckCount[i]-1] != 0){
				curseCheck = 1;
			}
	}
	}
	if(curseCheck ==1){
		printf("ERROR: curses not added to opponent's decks.\n");
	}

	if(FailCheck == 0 && curseCheck == 0){
		printf("SUCCESS: sea_hag played correctly.\n");
	}
	return 0;
	
}