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
  return self->cards[self->length];
}

void Deck_InitFullSorted (Deck  * self)
{
  Deck_InitEmpty(self);

  for (int s=0; s<NB_SUITS; s++){
    for (int r=1; r<=NB_RANKS; r++)
      Deck_AddCardAtEnd(self, Card_Make(s, r));
  }
}

void Deck_Shuffle (Deck * self)
{
  int randomindex;
  Card temporarycard;

  for (int i=0; i<self->length; i++){
    randomindex = rand() % self->length;
    temporarycard = self->cards[randomindex];
    self->cards[randomindex] = self->cards[i];
    self->cards[i] = temporarycard;
  }

}
