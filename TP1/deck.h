// File : deck.h
#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_CAPACITY (NB_SUITS * NB_RANKS)

typedef struct Deck
{
  int length;
  Card cards[DECK_CAPACITY];
} Deck;

void Deck_InitEmpty(Deck *self);
void Deck_AddCardAtEnd(Deck *self, Card card);
Card Deck_RemoveCardAtEnd(Deck *self);
void Deck_InitFullSorted(Deck *self);
void Deck_Shuffle(Deck *self);

#endif
