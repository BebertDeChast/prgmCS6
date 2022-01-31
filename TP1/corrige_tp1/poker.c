#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "hand.h"
#include "card.h"
#include "deck.h"
#include "handtest.h"
#include "cardtest.h"
#include "decktest.h"

extern char *handname[];
//-----------------------------------------------------------------------------

long wikiTotal= 2598960L;

long wikiHits [HAND_COUNT]= {  
  4L + 36L, 624L, 3744L,
  5108L, 10200L, 54912L,
  123552L,  1098240L, 1302540L
};

//-----------------------------------------------------------------------------

int main () { 
  CardTest_RunAll();
  DeckTest_RunAll();
  HandTest_RunAll();

  srand(time(NULL));  
  int hits[HAND_COUNT]= { 0 };
  int deal_count= 900000;
  
  for (int k= 0; k < deal_count; k++) {
    Deck deck;
    Deck_InitFullSorted (& deck);
    Deck_Shuffle (& deck);

    Hand hand;
		Hand_GetFullHand(&hand, &deck);
		HandType handtype = Hand_Is(hand);
    hits[handtype]++;

    if (((k+1) % 10000) == 0) {    
			Hand_Print(hand);
			for (int h= 0; h < HAND_COUNT; h++) {
      	double percent=  100.0 * hits    [h] / (k+1);
      	double expected= 100.0 * wikiHits[h] / wikiTotal;
      	printf ("%15s: %8d / %8d = %8.4f %% (%+.4f)\n",
              handname[h], hits[h], k+1, percent, percent-expected);
    	}
		}
  }
  
  
  return 0;
}
