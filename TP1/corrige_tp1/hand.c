// File : hand.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "card.h"
#include "hand.h"
#include "deck.h"


char *handname[]={ "Straight Flush", "Four of a kind", "Full house", "Flush", "Straight", "Three of a kind", "Two pairs", "One pair", "High card" };

void Hand_InitEmpty (Hand * self)
{
  self->length = 0;
}

void Hand_AddCard (Hand * self, Card card)
{
  assert (self->length < NB_CARDS);

  self->cards[self->length] = card;
  self->length++;
}

bool Hand_ContainsCard(Hand self, Card card)
{
  for (int i=0; i<self.length; i++){
    if ((self.cards[i].rank == card.rank) && (self.cards[i].suit == card.suit))
      return true;
  }
  return false;
}

int Hand_GetCardIndex(Hand self, Card card)
{
  for (int i=0; i<self.length; i++){
    if ((self.cards[i].rank == card.rank) && (self.cards[i].suit == card.suit))
      return i;
  }
  return -1;
}

void Hand_RemoveCard (Hand * self, Card card)
{
  assert (Hand_ContainsCard(*self, card));

  for (int i=Hand_GetCardIndex(*self, card); i<self->length-1; i++){
    self->cards[i] = self->cards[i+1];
  }
  self->length--;
}

void Hand_DrawFromDeck (Hand * self, Deck * deck)
{
  Card card = Deck_RemoveCardAtEnd(deck);
  Hand_AddCard(self, card);
}

void Hand_GetFullHand (Hand * self, Deck * deck)
{
  Hand_InitEmpty(self);
  for (int i=0; i<NB_CARDS; i++)
    Hand_DrawFromDeck(self, deck);
}

void Hand_Sort(Hand * self)
{
  Card swapcard;
  for (int i=1; i<self->length; i++){
    for (int j=0; j<self->length-i; j++){
      if (self->cards[j].rank > self->cards[j+1].rank){
        swapcard = self->cards[j];
        self->cards[j] = self->cards[j+1];
        self->cards[j+1] = swapcard;
      }
    }
  }
}

int  Hand_CountNumberOf(Hand self, int rank)
{
  int count = 0;
  for (int i=0; i<self.length; i++)
    if (self.cards[i].rank == rank)
      count++;

  return count;
}

bool Hand_IsStraightFlush(Hand self)
{
  if (Hand_IsStraight(self) && Hand_IsFlush(self))
    return true;

  return false;
}

bool Hand_IsFourOfAKind(Hand self)
{
  for (int i=1; i<=NB_RANKS; i++)
    if (Hand_CountNumberOf(self, i) == 4)
      return true;

  return false;
}

bool Hand_IsFullHouse(Hand self)
{
  if (Hand_IsThreeOfAKind(self) && Hand_IsOnePair(self))
    return true;

  return false;
}

bool Hand_IsFlush(Hand self)
{
  for(int i=0; i<self.length-1; i++){
    if (self.cards[i].suit != self.cards[i+1].suit)
      return false;
  }

  return true;
}

bool Hand_IsStraight(Hand self)
{
  Hand sorted = self;

	Hand_Sort(& sorted);

  for(int i=0; i<sorted.length-1; i++)
    if (sorted.cards[i].rank+1 != (sorted.cards[i+1].rank))
      return false;

  return true;
}

bool Hand_IsThreeOfAKind(Hand self)
{
  for (int i=1; i<=NB_RANKS; i++)
    if (Hand_CountNumberOf(self, i) == 3)
      return true;

  return false;
}

bool Hand_IsTwoPairs(Hand self)
{
  int indexoffirstpair = -1;

  for (int i=1; i<=NB_RANKS; i++)
    if (Hand_CountNumberOf(self, i) == 2)
      indexoffirstpair = i;

  for (int i=1; i<=NB_RANKS; i++)
    if ((Hand_CountNumberOf(self, i) == 2) && (i != indexoffirstpair))
      return true;

  return false;
}

bool Hand_IsOnePair(Hand self)
{
	if (!Hand_IsTwoPairs(self)){
	  for (int i=1; i<=NB_RANKS; i++)
  	  if (Hand_CountNumberOf(self, i) == 2)
  	    return true;
	}
  return false;
}

Card Hand_GetHighCard(Hand self)
{
  Card highest = self.cards[0];

  for(int i=0; i<self.length; i++)
    if (self.cards[i].rank > highest.rank)
      highest = self.cards[i];

  return highest;
}

HandType Hand_Is(Hand self){
	  if (Hand_IsStraightFlush(self))
    return STRAIGHT_FLUSH;
  if (Hand_IsFourOfAKind(self))
    return FOUR_OF_A_KIND;
  if (Hand_IsFullHouse(self))
    return FULL_HOUSE;
  if (Hand_IsFlush(self))
    return FLUSH;
  if (Hand_IsStraight(self))
    return STRAIGHT;
  if (Hand_IsThreeOfAKind(self))
    return THREE_OF_A_KIND;
  if (Hand_IsTwoPairs(self))
    return TWO_PAIRS;
  if (Hand_IsOnePair(self))
    return ONE_PAIR;

  return HIGH_CARD;
}

char const * Hand_ToString(Hand self)
{
  return handname[Hand_Is(self)];
}



void Hand_Print (Hand self)
{
  for (int i=0; i<self.length; i++){
    Card_Print(self.cards[i]);
    printf (" - ");
  }
  printf("\n");
}
