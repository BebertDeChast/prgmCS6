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

long wikiTotal= 2598960L; // * The L at the end is for the long type

long wikiHits [HAND_COUNT]= {  
  4L + 36L, 624L, 3744L,
  5108L, 10200L, 54912L,
  123552L,  1098240L, 1302540L
};

Hand Hand_generate() {
  Deck d;
  Hand h;
  Deck_InitEmpty(& d);
  Deck_InitFullSorted(& d);
  Deck_Shuffle(& d);
  Hand_GetFullHand(& h, & d);
  return h;
}

//-----------------------------------------------------------------------------

int main () { 
  CardTest_RunAll();
  DeckTest_RunAll();
  HandTest_RunAll();

  long combine_counter[9] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
  for (int i = 0; i < wikiTotal; i++) {
    Hand h = Hand_generate();
    HandType result = Hand_Is(h);
    combine_counter[result]++;
  }

  for (int i = 0; i < 9; i++) {
    printf("Practical : %ld | Theorical : %ld", combine_counter[i]/wikiTotal, wikiHits[i]/wikiTotal);
  }
    
}
