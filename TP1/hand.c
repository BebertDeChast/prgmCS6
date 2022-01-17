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
  for(int i = 0; i<self.length; i++){
    if (self.cards[i].rank == card.rank && self.cards[i].suit == card.suit){
      return true;
    }
  return false;
  }
}

int Hand_GetCardIndex(Hand self, Card card)
{
for(int i = 0; i<self.length; i++){
    if (self.cards[i].rank == card.rank && self.cards[i].suit == card.suit){
      return i;
    }
  return -1;
  }
}

void Hand_RemoveCard (Hand * self, Card card)
{
  assert (Hand_ContainsCard(*self, card));
  int index = Hand_GetCardIndex(*self,card);
  self->length--;
  for (int i = index; i < self->length; i++ ){
    self->cards[i + 1] = self->cards[i];
  }
}

void Hand_DrawFromDeck (Hand * self, Deck * deck) // * Fonction pioche
{
  assert(deck->length > 0);
  int index = deck->length - 1;
  Card transferredCard = deck->cards[index];
  Deck_RemoveCardAtEnd(deck);
  Hand_AddCard(self, transferredCard);
}

void Hand_GetFullHand (Hand * self, Deck * deck)
{
  Hand_InitEmpty(self);
  while(self->length < NB_CARDS)
// TO DO
}

void Hand_Sort(Hand * self)
{
  Card swapcard;

// TO DO
}

int  Hand_CountNumberOf(Hand self, int rank)
{
  int count = 0;

// TO DO
}

bool Hand_IsStraightFlush(Hand self)
{
// TO DO
}

bool Hand_IsFourOfAKind(Hand self)
{
// TO DO
}

bool Hand_IsFullHouse(Hand self)
{
	// TO DO
}

bool Hand_IsFlush(Hand self)
{
// TO DO
}

bool Hand_IsStraight(Hand self)
{
// TO DO
}

bool Hand_IsThreeOfAKind(Hand self)
{
// TO DO
}

bool Hand_IsTwoPairs(Hand self)
{
// TO DO
}

bool Hand_IsOnePair(Hand self)
{
// TO DO
}

Card Hand_GetHighCard(Hand self)
{
// TO DO
}

HandType Hand_Is(Hand self){
// TO DO
}

char const * Hand_ToString(Hand self)
{
// TO DO
}



void Hand_Print (Hand self)
{
  for (int i=0; i<self.length; i++){
    Card_Print(self.cards[i]);
    printf (" - ");
  }
  printf("\n");
}
