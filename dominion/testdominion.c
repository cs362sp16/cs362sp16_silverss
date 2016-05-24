#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"


//helper function to randomize items in array
void kingShuffle(int *array, size_t n){
	if (n > 1){
		size_t i;
		for(i = 0; i < n-1; i++){
			size_t j = i + rand() / (RAND_MAX / (n-i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}


}

//this function counts the number of treasure cards in the player's hand
int HandTreasure(struct gameState *game, int player){
	int card;
	int x = 0;
	//iterate through players hand to see how many treasure cards they have
	for(int i=0; i<game->handCount[player]; i++){
		card = game->hand[player][i];
		if(card == copper){
			x++;
		}
		if(card == silver){
			x = x+2;
		}
		if(card == gold){
			x = x+3;
		}
	}
	return x;
}

//function to buy a card with error handling
int customBuy(int cardToBuy, struct gameState *state){
	//check if card is available
	if(supplyCount(cardToBuy, state) < 1){
		//printf("card couldn't be bought, supplyCount < 1\n");
		return -1;
	}

	if(!buyCard(cardToBuy, state)){
		printf("Card was successfully bought\n");
	}
	else
		printf("Failed to buy card\n");
	return 0;
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

	//setup game
	int testSeed = argv[1];
	struct gameState game;
	srand(testSeed);
	//get 10 random kingdom cards
	int allKingCards[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
	kingShuffle(allKingCards, 20);

	int k[10];

	for(int i = 0; i < 10; i++){
		k[i] = allKingCards[i];
	}

	//get random number of players between 2 and MAX_PLAYERS
	int players = (rand() % MAX_PLAYERS);
	if(players < 2){
			players = players + 2;
	}
	srand(testSeed);
	int gameSeed = rand();

	//initialize game
	initializeGame(players, k, gameSeed, &game);

	//loop until game is finished
	while(!isGameOver(&game)){
		int currentPlayer = whoseTurn(&game);
		printf("player: %d begins their turn\n",currentPlayer );
		//action phase
		int playResult = 0;
		while(game.numActions > 0){

			int numActionCards = 0;
			//make sure there is an action card in hand
			for(int i=0; i <numHandCards(&game); i++){
				if(game.hand[currentPlayer][i] >= adventurer && game.hand[currentPlayer][i] <= treasure_map){
					numActionCards++;
				}
			}

			//if no action cards in hand break loop
			if(numActionCards == 0){
				printf("no action cards in hand\n");
				break;
			}
			int handPos = rand() % game.handCount[currentPlayer];
			int cardPlay = game.hand[currentPlayer][handPos];
			//check if selected card is kingdom card
			if(cardPlay >= adventurer && cardPlay <= treasure_map){
				playResult = playCard(handPos,0,0,0,&game);
			}
			//check result of playCard
			if(playResult != 0){
				printf("Could not play card\n");
			}
			else
				printf("Card was successfully played\n");
			//1 in 10 chance to not use an action
			if(rand() % 10 == 0)
				break;
		}

		//buy phase
		while(game.numBuys > 0){
			//count the value of treasure in player's hand
			updateCoins(currentPlayer, &game, 0);
			int treasureAvailable = HandTreasure(&game, currentPlayer);

			//for buying cards, I seperated possible cards to buy into tiers based on cost
			//this is less about game strategy and more about trying to get good coverage of cards
			if(treasureAvailable >= 8){
				customBuy(province, &game);
				treasureAvailable = HandTreasure(&game, currentPlayer);
			}

			if(treasureAvailable >= 6){
				if(rand() % 1)
					customBuy(gold, &game);
				
				else
					customBuy(adventurer, &game);

				treasureAvailable = HandTreasure(&game, currentPlayer);
			}

			if(treasureAvailable >= 5){
				switch(rand() % 6){
					case 4:
						customBuy(minion, &game);
						break;
					case 3:
						customBuy(mine, &game);
						break;
					case 2:
						customBuy(council_room, &game);
						break;
					case 1:
						customBuy(duchy, &game);
						break;
					case 0:
						customBuy(outpost, &game);
						break;
					default:
						customBuy(tribute, &game);
						break;

				}
				treasureAvailable = HandTreasure(&game, currentPlayer);
			}

			if(treasureAvailable >= 4){
				switch(rand() % 9){
					case 7:
						customBuy(feast, &game);
						break;
					case 6:
						customBuy(gardens, &game);
						break;
					case 5:
						customBuy(salvager, &game);
						break;
					case 4:
						customBuy(treasure_map, &game);
						break;
					case 3:
						customBuy(sea_hag, &game);
						break;
					case 2:
						customBuy(cutpurse, &game);
					case 1:
						customBuy(remodel, &game);
						break;
					case 0:
						customBuy(smithy, &game);
						break;
					default:
						customBuy(baron, &game);
						break;
				}
				treasureAvailable = HandTreasure(&game, currentPlayer);
			}

			if(treasureAvailable >= 3){
				switch(rand() % 5){
					case 3:
						customBuy(steward, &game);
						break;
					case 2:
						customBuy(ambassador, &game);
						break;
					case 1:
						customBuy(great_hall, &game);
						break;
					case 0:
						customBuy(silver, &game);
						break;
					default:
						customBuy(village, &game);
						break;
				}
				treasureAvailable = HandTreasure(&game, currentPlayer);
			}

			if(treasureAvailable >= 2){
				if(rand() % 1)
					customBuy(estate, &game);
				
				else
					customBuy(embargo, &game);

				treasureAvailable = HandTreasure(&game, currentPlayer);
			}
			else
				customBuy(copper, &game);
				break;

		}//end buy loop

		//cleanup phase
		printf("player: %d ends their turn\n",currentPlayer );
		endTurn(&game);

	}//game loop

	printf("game is finished.\n");
	printf("Game results:\n");
	for(int i = 0; i < players; i++){
		printf("Player: %d Score: %d\n",i,scoreFor(i, &game));
	}

	int winners[5];
	getWinners(winners, &game);




	return 1;
}