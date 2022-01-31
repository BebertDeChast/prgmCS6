// File : expression.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "expression.h"

//===============================================
char Operator_ToChar(Operator oper)
{
// TO DO
}

//===============================================
Operator Operator_CharTo(char * c)
{
  assert(c[1] == '\0');

// TO DO

  assert(false);
}

//===============================================
void Expression_Store(Expression * self, double number1, double number2, Operator oper)
{
// TO DO
}

//===============================================
double Expression_Solve(Expression self)
{
// TO DO
}

//===============================================
void Expression_Print(Expression self)
{
  printf ("%f %c %f = %f\n", self.number1, Operator_ToChar(self.operator), self.number2, Expression_Solve(self));
}

