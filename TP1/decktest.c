// File : decktest.c
#include <stdio.h>
#include <assert.h>
#include "deck.h"
#include "decktest.h"

//===============================================
void DeckTest_InitEmpty ()
{
	Deck d; 
	Deck_InitEmpty (& d);
  assert (d.length == 0);
}

//===============================================
void DeckTest_AddCardAtEnd ()
{
	Deck d;
	Deck_InitEmpty(&d);
	Card c = {.rank = 1, .suit = 2};
	Deck_AddCardAtEnd(&d, c);
	assert(d.length == 1);
	assert(d.cards[0].rank == 1 && d.cards[0].suit == 2);
}

//===============================================
void DeckTest_RemoveCardAtEnd ()
{
	Deck d;
	Deck_InitEmpty (& d);
	
	Deck_AddCardAtEnd(& d, Card_Make(CLUB, 2));
	Deck_AddCardAtEnd(& d, Card_Make(DIAMOND, 5));	
	Deck_AddCardAtEnd(& d, Card_Make(HEART, 1));
	assert (d.length == 3);

	Card c = Deck_RemoveCardAtEnd(&d);
	assert (d.length == 2);
	assert ((c.suit == HEART) && (c.rank == 1));
	c = Deck_RemoveCardAtEnd(&d);
	assert (d.length == 1);
	assert ((c.suit == DIAMOND) && (c.rank == 5));
	c = Deck_RemoveCardAtEnd(&d);
	assert (d.length == 0);
	assert ((c.suit == CLUB) && (c.rank == 2));
}

//===============================================
void DeckTest_InitFullSorted ()
{
	Deck d;
	Deck_InitFullSorted(&d);
  	for (Suit i = 0; i < NB_SUITS; i++) { // * i is the card's color
    	for (int j = 1; j < NB_RANKS; j++) { // * j is the card's rank
      		assert(d.cards[(i * NB_RANKS) + j].rank == d.cards[(i * NB_RANKS) + j - 1].rank + 1 && d.cards[(i * NB_RANKS) + j].suit == d.cards[(i * NB_RANKS) + j - 1].suit);
		}
	}
}

//===============================================
void DeckTest_Shuffle ()
{
  Deck d; 
	Deck_InitFullSorted (& d);
	Deck_Shuffle(& d);

	int i=0;	
	for (int s=0; s<NB_SUITS; s++){
    for (int r=1; r<=NB_RANKS; r++){
			assert ((d.cards[i].suit != (unsigned) s) || (d.cards[i].rank != r));
			i++;
		}
	}
}

//===============================================
void DeckTest_RunAll ()
{
	DeckTest_InitEmpty();
	DeckTest_AddCardAtEnd();
	DeckTest_RemoveCardAtEnd ();
	DeckTest_InitFullSorted ();
	DeckTest_Shuffle ();
}
