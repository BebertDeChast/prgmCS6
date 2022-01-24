// File : hand.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "card.h"
#include "hand.h"
#include "deck.h"


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
  while(self->length < NB_CARDS) {
    Hand_DrawFromDeck(self, deck);
  }
}

void Hand_Sort(Hand * self)
{
  Card swapcard;
  for (int i = 0; i < self->length; i++) {
    for (int j = 1; j < self->length; j++) {
      if (self->cards[j].rank < self->cards[j - 1].rank) {
        swapcard = self->cards[j];
        self->cards[j] = self->cards[j - 1];
        self->cards[j - 1] = swapcard;
      }
    }
  }
}

int  Hand_CountNumberOf(Hand self, int rank)
{
  int count = 0;
  for (int i = 0; i < self.length; i++){
    if (rank == self.cards[i].rank) {
      count++;
    }
  }
  return count;
}

bool Hand_IsStraightFlush(Hand self)
{
  int begin = self.cards[0].rank;
  int color = self.cards[0].suit;
  for (int i = 1; i < self.length; i++) {
    begin++;
    if (!(begin == self.cards[i].rank && color == self.cards[i].suit)) {
      return false;
    }
  }
  return true;
}

bool Hand_IsFourOfAKind(Hand self)
{
  int four; 
  for (int i = 0; i < self.length; i++) {
    four = Hand_CountNumberOf(self, self.cards[i].rank);
    if (four == 4) {
      return true;
    }
  }
  return false;
}

bool Hand_IsFullHouse(Hand self)
{
	int counter;
  bool is_triple = false;
  bool is_pair = false;
  for (int i = 0; i < self.length; i++) {
    counter = Hand_CountNumberOf(self, self.cards[i].rank);
    if (counter == 3) {
      is_triple = true;
    } else if (counter == 2) {
      is_pair = true;
    }
  }
  if (is_triple && is_pair) {
    return true;
  }
  return false;
}

bool Hand_IsFlush(Hand self)
{
  int color = self.cards[0].suit;
  for (int i = 1; i < self.length; i++) {
    if (color != self.cards[i].suit) {
      return false;
    };
  }
  return true;
}

bool Hand_IsStraight(Hand self)
{
  int begin = self.cards[0].rank;
  for (int i = 1; i < self.length; i++) {
    begin++;
    if (!(begin == self.cards[i].rank)) {
      return false;
    }
  }
  return true;
}

bool Hand_IsThreeOfAKind(Hand self)
{
	int counter;
  for (int i = 0; i < self.length; i++) {
    counter = Hand_CountNumberOf(self, self.cards[i].rank);
    if (counter == 3) {
      return true;
    }
  }
  return false;
}

bool Hand_IsTwoPairs(Hand self)
{
  int counter_of_counter = 0;
  int counter;
  for (int i = 0; i < self.length; i++) {
    counter = Hand_CountNumberOf(self, self.cards[i].rank);
    if (counter == 2) {
      counter_of_counter++;
    }
  }
  if (counter_of_counter == 4) {
    return true;
  }
  return false;
}

bool Hand_IsOnePair(Hand self)
{
  int t;
  for (int i = 0;i<self.length;i++) {
    t = Hand_CountNumberOf(self,self.cards[i].rank);
    if (t == 2) {
      return true;
    }
  }
  return false;
}

Card Hand_GetHighCard(Hand self)
{
  int max_rank = self.cards[0].rank;
  int current_index = 0;
  for (int i = 1; i < self.length; i++) {
    if (max_rank < self.cards[i].rank) {
      max_rank = self.cards[i].rank;
      current_index = i;
    }
  }
  return self.cards[current_index];
}

HandType Hand_Is(Hand self){
  Hand_Sort(&self);
  if (Hand_IsStraightFlush(self)) {
    return STRAIGHT_FLUSH;
  } else if (Hand_IsFourOfAKind(self)) {
    return FOUR_OF_A_KIND;
  } else if (Hand_IsFullHouse(self)) {
    return FULL_HOUSE;
  } else if (Hand_IsFlush(self)) {
    return FLUSH;
  } else if (Hand_IsStraight(self)) {
    return STRAIGHT;
  } else if (Hand_IsThreeOfAKind(self)) {
    return THREE_OF_A_KIND;
  } else if (Hand_IsTwoPairs(self)) {
    return TWO_PAIRS;
  } else if (Hand_IsOnePair(self)) {
    return ONE_PAIR;
  }
  return HIGH_CARD;
}

char const * Hand_ToString(Hand self)
{
  return output[Hand_Is(self)];
}

void Hand_Print (Hand self)
{
  for (int i=0; i<self.length; i++){
    Card_Print(self.cards[i]);
    printf (" - ");
  }
  printf("\n");
}
