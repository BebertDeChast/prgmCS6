// File : composition.h
#ifndef COMPOSITION_H
#define COMPOSITION_H
#include "expression.h"

typedef struct Composition
{
    Expression *expressions;
    int capacity;
    int length;
} Composition;

void Composition_InitEmpty(Composition *self);
void Composition_Alloc(Composition *self, int length);
void Composition_StoreFirstExpression(Composition *self, double number1, double number2, Operator oper);
void Composition_StoreExpression(Composition *self, double number, Operator oper);
void Composition_Print(Composition self);
void Composition_Destroy(Composition *self);

#endif
