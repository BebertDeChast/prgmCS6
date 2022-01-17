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

// TO DO
}
