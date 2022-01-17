// File : handtest.c
#include <stdio.h>
#include <assert.h>
#include "hand.h"
#include "handtest.h"

//===============================================
void HandTest_InitEmpty()
{
	Hand h; 
	Hand_InitEmpty (& h);
  assert (h.length == 0);
}

//===============================================
void HandTest_AddCard()
{
	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	assert (h.length == 1);
	Hand_AddCard(& h, Card_Make(DIAMOND, 5));	
	assert (h.length == 2);
	Hand_AddCard(& h, Card_Make(HEART, 1));
	assert (h.length == 3);

	assert ((h.cards[0].suit == CLUB) && (h.cards[0].rank == 2));
	assert ((h.cards[1].suit == DIAMOND) && (h.cards[1].rank == 5));
	assert ((h.cards[2].suit == HEART) && (h.cards[2].rank == 1));
}

//===============================================
void HandTest_ContainsCard()
{
// TO DO
}

//===============================================
void HandTest_GetCardIndex()
{
	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	Hand_AddCard(& h, Card_Make(DIAMOND, 5));	
	Hand_AddCard(& h, Card_Make(HEART, 1));

	
	assert (Hand_GetCardIndex(h, Card_Make(DIAMOND, 5)) == 1);
	assert (Hand_GetCardIndex(h, Card_Make(SPADE, 1)) == -1);

}

//===============================================
void HandTest_RemoveCard()
{
	// TO DO
}

//===============================================
void HandTest_DrawFromDeck()
{
  Deck d; 
	Deck_InitFullSorted (& d);
 
	Hand h;
	Hand_InitEmpty(& h);
	Hand_DrawFromDeck (& h, & d);

	assert (h.length == 1);
	assert (d.length == (DECK_CAPACITY-1));

	Hand_DrawFromDeck (& h, & d);

	assert (h.length == 2);
	assert (d.length == (DECK_CAPACITY-2));
}

//===============================================
void HandTest_GetFullHand()
{
// TO DO

}

//===============================================
void HandTest_Sort()
{
	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	Hand_AddCard(& h, Card_Make(DIAMOND, 5));	
	Hand_AddCard(& h, Card_Make(HEART, 1));
	Hand_AddCard(& h, Card_Make(SPADE, 8));
	Hand_AddCard(& h, Card_Make(HEART, 3));

	Hand_Sort(& h);

	// TO COMPLETE

}

//===============================================
void HandTest_CountNumberOf()
{

	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	Hand_AddCard(& h, Card_Make(DIAMOND, 5));	
	Hand_AddCard(& h, Card_Make(HEART, 2));
	Hand_AddCard(& h, Card_Make(SPADE, 8));
	Hand_AddCard(& h, Card_Make(HEART, 3));

	assert (Hand_CountNumberOf(h, 2) == 2);
	assert (Hand_CountNumberOf(h, 5) == 1);
	assert (Hand_CountNumberOf(h, 1) == 0);
}

//===============================================
void HandTest_IsStraightFlush()
{

	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 7));
	Hand_AddCard(& h, Card_Make(CLUB, 4));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 3));

	assert(Hand_IsStraightFlush(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 4));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsStraightFlush(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 1));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsStraightFlush(h));
}

//===============================================
void HandTest_IsFourOfAKind()
{
  // TO DO
}

//===============================================
void HandTest_IsFullHouse()
{
	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	Hand_AddCard(& h, Card_Make(DIAMOND, 2));	
	Hand_AddCard(& h, Card_Make(HEART, 2));
	Hand_AddCard(& h, Card_Make(SPADE, 3));
	Hand_AddCard(& h, Card_Make(HEART, 3));

	assert(Hand_IsFullHouse(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 4));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsFullHouse(h));
}

//===============================================
void HandTest_IsFlush()
{
	Hand h;
	Hand_InitEmpty (& h);
	
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 4));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsFlush(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 1));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(Hand_IsFlush(h));
}

//===============================================
void HandTest_IsStraight()
{
	// TO DO 
}

//===============================================
void HandTest_IsThreeOfAKind()
{

	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(Hand_IsThreeOfAKind(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 1));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsThreeOfAKind(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 3));
	Hand_AddCard(& h, Card_Make(SPADE, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsThreeOfAKind(h));
}

//===============================================
void HandTest_IsTwoPairs()
{

	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(Hand_IsTwoPairs(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 1));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsTwoPairs(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 6));
	Hand_AddCard(& h, Card_Make(SPADE, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 6));

	assert(!Hand_IsTwoPairs(h));
}

//===============================================
void HandTest_IsOnePair()
{

	Hand h;
	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(Hand_IsOnePair(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(CLUB, 1));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	assert(!Hand_IsOnePair(h));

	Hand_InitEmpty (& h);
	
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 3));	
	Hand_AddCard(& h, Card_Make(HEART, 6));
	Hand_AddCard(& h, Card_Make(SPADE, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 4));

	assert(!Hand_IsOnePair(h));
}

//===============================================
void HandTest_GetHighCard()
{
	Hand h;
	Hand_InitEmpty (& h);

	Hand_AddCard(& h, Card_Make(CLUB, 3));
	Hand_AddCard(& h, Card_Make(DIAMOND, 8));	
	Hand_AddCard(& h, Card_Make(HEART, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 7));

	Card c = Hand_GetHighCard(h);
	assert(c.rank == 8);
	assert(c.rank != 7);
}

//===============================================
void HandTest_Is()
{
	Hand h;

	Hand_InitEmpty (& h);
	Hand_AddCard(& h, Card_Make(CLUB, 7));
	Hand_AddCard(& h, Card_Make(CLUB, 4));	
	Hand_AddCard(& h, Card_Make(CLUB, 5));
	Hand_AddCard(& h, Card_Make(CLUB, 6));
	Hand_AddCard(& h, Card_Make(CLUB, 3));
	assert (Hand_Is(h) == STRAIGHT_FLUSH);

	Hand_InitEmpty (& h);
	Hand_AddCard(& h, Card_Make(CLUB, 2));
	Hand_AddCard(& h, Card_Make(DIAMOND, 2));	
	Hand_AddCard(& h, Card_Make(HEART, 2));
	Hand_AddCard(& h, Card_Make(SPADE, 2));
	Hand_AddCard(& h, Card_Make(HEART, 3));
	assert (Hand_Is(h) == FOUR_OF_A_KIND);

	// TO COMPLETE
}

//===============================================
void HandTest_RunAll()
{
	HandTest_InitEmpty ();
	HandTest_AddCard ();
	HandTest_ContainsCard();
	HandTest_GetCardIndex();
	HandTest_RemoveCard ();
	HandTest_DrawFromDeck ();
	HandTest_GetFullHand ();
	HandTest_Sort();
	HandTest_CountNumberOf();

	HandTest_IsStraightFlush();
	HandTest_IsFourOfAKind();
	HandTest_IsFullHouse();
	HandTest_IsFlush();
	HandTest_IsStraight();
	HandTest_IsThreeOfAKind();
	HandTest_IsTwoPairs();
	HandTest_IsOnePair();
	HandTest_GetHighCard();
	HandTest_Is();

}
