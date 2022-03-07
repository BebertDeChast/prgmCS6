// File : expression.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "expression.h"

//===============================================
char Operator_ToChar(Operator oper)
{
  switch(oper){
    case ADD : return '+';
    case SUB : return '-';
    case MULT: return '*';
    case DIV : return '/';
  }
}

//===============================================
Operator Operator_CharTo(char * c)
{
  assert(c[1] == '\0');

  switch(c[0]){
    case '+' : return ADD;
    case '-' : return SUB;
    case '*' : return MULT;
    case '/' : return DIV;
  }

  assert(false);
}

//===============================================
void Expression_Store(Expression * self, double number1, double number2, Operator oper)
{
  self->number1 = number1;
  self->number2 = number2;
  self->operator = oper;
}

//===============================================
double Expression_Solve(Expression self)
{
  switch(self.operator){
    case ADD : return (self.number1 + self.number2);
    case SUB : return (self.number1 - self.number2);
    case MULT: return (self.number1 * self.number2);
    case DIV : assert(self.number2 != 0.0);
               return (self.number1 /self.number2);
  }
}

//===============================================
void Expression_Print(Expression self)
{
  printf ("%f %c %f = %f\n", self.number1, Operator_ToChar(self.operator), self.number2, Expression_Solve(self));
}

