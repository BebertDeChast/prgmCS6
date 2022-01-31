// File : composition.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "composition.h"

//===============================================
void Composition_InitEmpty(Composition * self){
	self->length = 0;
	self-> capacity = 0;
}

//===============================================
void Composition_Alloc(Composition * self, int capacity){
	assert (capacity > 0);
	self->capacity = capacity;
	self->expressions = malloc(capacity * sizeof * self->expressions);
	assert(self->expressions != NULL);
}

//===============================================
void Composition_StoreFirstExpression(Composition * self, double number1, double number2, Operator oper) {
	assert (self->capacity > 0);
	Expression e;
	Expression_Store(&e, number1, number2, oper);
	self->expressions[0] = e;
	self->length = 1;
}

//===============================================
void Composition_StoreExpression(Composition *self, double number, Operator oper) {
	assert (self->capacity > self->length);
	assert (self->length > 0); 
	Expression e;
	Expression_Store(&e, Expression_Solve(self->expressions[self->length - 1]), number, oper);
	self->expressions[self->length] = e;
	self->length++;
}

//===============================================
void Composition_Print(Composition self) {
	for (int i = 0; i < self.length; i++) {
		Expression_Print(self.expressions[i]);
	}
}

//===============================================
void Composition_Destroy(Composition *self) {
	free(self->expressions);
}
