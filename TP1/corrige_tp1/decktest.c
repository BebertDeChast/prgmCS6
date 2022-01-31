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
	Deck_InitEmpty (& d);
	
	Deck_AddCardAtEnd(& d, Card_Make(CLUB, 2));
	assert (d.length == 1);
	Deck_AddCardAtEnd(& d, Card_Make(DIAMOND, 5));	
	assert (d.length == 2);
	Deck_AddCardAtEnd(& d, Card_Make(HEART, 1));
	assert (d.length == 3);

	assert ((d.cards[0].suit == CLUB) && (d.cards[0].rank == 2));
	assert ((d.cards[1].suit == DIAMOND) && (d.cards[1].rank == 5));
	assert ((d.cards[2].suit == HEART) && (d.cards[2].rank == 1));
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
	Deck_InitFullSorted (& d);
  assert (d.length == DECK_CAPACITY);

	int i=0;	
	for (int s=0; s<NB_SUITS; s++){
    for (int r=1; r<=NB_RANKS; r++){
			assert ((d.cards[i].suit == (unsigned) s) && (d.cards[i].rank == r));
			i++;
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
  DeckTest_RemoveCardAtEnd();
	DeckTest_InitFullSorted();
	DeckTest_Shuffle();
}
