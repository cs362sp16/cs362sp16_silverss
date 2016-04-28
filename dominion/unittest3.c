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
	int a[] = {9,8,7,6,5,4,3,2,1,0};
	int n;
	int numErrors = 0;
	int* listOfKingdomCards = kingdomCards(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]);
	for(n = 0; n <10; n++){
		if(listOfKingdomCards[n] != a[n]){
			printf("Kingdomcard: %d produced an error\n",n );
			FailCheck = 1;
			numErrors++;
		}
	}


	if(FailCheck == 0){
		printf("No errors found in Kingdomcards function\n");
	}
	else
		printf("Number of errors found: %d \n",numErrors);



	return 0;
	
}