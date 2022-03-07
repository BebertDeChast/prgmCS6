// File : expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

typedef enum Operator {
ADD, SUB, MULT, DIV
} Operator;

char Operator_ToChar(Operator oper);
Operator Operator_CharTo(char * c);

typedef struct Expression {
  double number1, number2;
  Operator operator;
} Expression;

void Expression_Store(Expression * self, double number1, double number2, Operator oper);
double Expression_Solve(Expression self);
void Expression_Print(Expression self);

#endif
