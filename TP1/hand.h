// File : hand.h
#ifndef HAND_H
#define HAND_H
#include <stdbool.h>
#include "card.h"
#include "deck.h"

#define NB_CARDS 5
#define HAND_COUNT 9

typedef enum HandType
{
  STRAIGHT_FLUSH,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  FLUSH,
  STRAIGHT,
  THREE_OF_A_KIND,
  TWO_PAIRS,
  ONE_PAIR,
  HIGH_CARD
} HandType;

typedef struct Hand
{
  int length;
  Card cards[NB_CARDS];
} Hand;

void Hand_InitEmpty(Hand *self);
void Hand_AddCard(Hand *self, Card card);
bool Hand_ContainsCard(Hand self, Card card);
int Hand_GetCardIndex(Hand self, Card card);
void Hand_RemoveCard(Hand *self, Card card);
void Hand_DrawFromDeck(Hand *self, Deck *deck);
void Hand_GetFullHand(Hand *self, Deck *deck);
void Hand_Sort(Hand *self);
int Hand_CountNumberOf(Hand self, int rank);

bool Hand_IsStraightFlush(Hand self);
bool Hand_IsFourOfAKind(Hand self);
bool Hand_IsFullHouse(Hand self);
bool Hand_IsFlush(Hand self);
bool Hand_IsStraight(Hand self);
bool Hand_IsThreeOfAKind(Hand self);
bool Hand_IsTwoPairs(Hand self);
bool Hand_IsOnePair(Hand self);
Card Hand_GetHighCard(Hand self);

HandType Hand_Is(Hand self);

char const *Hand_ToString(Hand self);

void Hand_Print(Hand self);

#endif
