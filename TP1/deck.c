// File : deck.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "card.h"
#include "deck.h"

void Deck_InitEmpty (Deck * self)
{
  self->length = 0;
}

void Deck_AddCardAtEnd (Deck * self, Card card)
{
  assert (self->length <= DECK_CAPACITY);
  self->cards[self->length] = card;
  self->length++;
}

Card Deck_RemoveCardAtEnd (Deck * self)
{
  assert (self->length > 0);
  self->length--;
}

void Deck_InitFullSorted (Deck  * self)
{
  Deck_InitEmpty(self);
  // ? This shit went from 1 to 100 really quickly
  for (Suit i = 0; i < NB_SUITS; i++) { // * i is the card's color
    for (int j = 0; j < NB_RANKS; j++) { // * j is the card's rank
      // TODO : Fix my sanity
      Card card = Card_Make(i, j);
      Deck_AddCardAtEnd(self, card);
    }
  }
}

void Deck_Shuffle (Deck * self)
{
  int randomindex; 
  Card temporarycard;
  for (int i; i < DECK_CAPACITY; i++) {
    randomindex = rand() % DECK_CAPACITY;
    temporarycard = self->cards[i];
    self->cards[i] = self->cards[randomindex];
    self->cards[randomindex] = temporarycard;
  }
}