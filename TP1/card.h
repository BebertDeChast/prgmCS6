// File : card.h
#ifndef CARD_H
#define CARD_H

#define NB_SUITS 4
#define NB_RANKS 13

typedef enum Suit
{
  CLUB,
  DIAMOND,
  HEART,
  SPADE
} Suit; // ! entier à cause de énum

char const *Suit_ToString(Suit self);

typedef struct Card
{
  Suit suit;
  int rank;
} Card;

Card Card_Make(Suit _suit, int _rank);
void Card_Print(Card self);
#endif
