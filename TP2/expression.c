// File : expression.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "expression.h"

//===============================================
char Operator_ToChar(Operator oper) {
switch (oper) {
  case (ADD):
    return "+"; // * No break because the return stop the function anyway
  case (SUB):
    return "-";
  case (MULT):
    return "*";
  case (DIV):
    return "/";
  }
}

//===============================================
Operator Operator_CharTo(char * c)
{
  assert(c[1] == '\0'); // * Basically we first check that the string has only 1 letter
  if (c == "+") {
    return ADD;
  } else if (c == "-") {
    return SUB;
  } else if (c == "*") {
    return MULT;
  } else if (c == "/") {
    return DIV;
  }
  assert(false);
}

//===============================================
void Expression_Store(Expression * self, double number1, double number2, Operator oper) {
  self->x = number1;
  self->y = number2;
  self->op = oper;
}

//===============================================
double Expression_Solve(Expression self) {
  switch (self.op) {
  case (ADD):
    return self.x + self.y;
  case (SUB):
    return self.x-self.y;
  case (MULT):
    return self.x * self.y;
  case (DIV):
    return self.x/self.y;
  }
}

//===============================================
void Expression_Print(Expression self)
{
  printf ("%f %c %f = %f\n", self.x, Operator_ToChar(self.op), self.y, Expression_Solve(self));
}

