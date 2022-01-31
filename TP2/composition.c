// File : composition.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "composition.h"

//===============================================
void Composition_InitEmpty(Composition * self)
{
// TO DO}

//===============================================
void Composition_Alloc(Composition * self, int capacity)
{
	assert (capacity > 0);

// TO DO

  assert(self->expressions != NULL);
}

//===============================================
void Composition_StoreFirstExpression(Composition * self, double number1, double number2, Operator oper)
{
	assert (self->capacity > 0);
// TO DO
}

//===============================================
void Composition_StoreExpression(Composition *self, double number, Operator oper)
{
	assert (self->capacity > self->length);
	assert (self->length > 0); 
// TO DO

}

//===============================================
void Composition_Print(Composition self)
{
// TO DO

}

//===============================================
void Composition_Destroy(Composition *self)
{
// TO DO

}
