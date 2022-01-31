// File : cardtest.c
#include <stdio.h>
#include <assert.h>
#include "card.h"
#include "cardtest.h"

//===============================================
void CardTest_Make()
{
  Card card = Card_Make (CLUB, 2);
  assert (card.rank == 2);
  assert (card.suit == CLUB);

	card = Card_Make (DIAMOND, 8);
  assert (card.rank == 8);
  assert (card.suit == DIAMOND);

	card = Card_Make (HEART, 10);
  assert (card.rank == 10);
  assert (card.suit == HEART);

	card = Card_Make (SPADE, 1);
  assert (card.rank == 1);
  assert (card.suit == SPADE);
}

//===============================================
void CardTest_RunAll()
{
	CardTest_Make();
}
