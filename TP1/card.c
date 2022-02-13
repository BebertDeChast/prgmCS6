// File : card.c
#include <stdio.h>
#include <assert.h>
#include "card.h"

char *suitname[] = {"club", "diamond", "heart", "spade"};

char const *Suit_ToString(Suit suit)
{
  assert(suit < NB_SUITS);
  return (suitname[suit]);
}

Card Card_Make(Suit _suit, int _rank)
{
  Card card;
  card.rank = _rank;
  card.suit = _suit;
  return card;
}

void Card_Print(Card card)
{
  printf("%d %d", card.rank, card.suit);
}
