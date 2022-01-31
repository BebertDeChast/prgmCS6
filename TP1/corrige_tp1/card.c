// File : card.c
#include <stdio.h>
#include <assert.h>
#include "card.h"

char *suitname[]={"club", "diamon", "heart", "spade"};

char const * Suit_ToString(Suit suit)
{
  assert (suit < NB_SUITS);

  return suitname[suit];
}

Card Card_Make(Suit _suit, int _rank)
{
 return (Card) { .suit=_suit, .rank=_rank };
}

void Card_Print(Card card){
  printf("%d %s", card.rank, Suit_ToString(card.suit));
}
