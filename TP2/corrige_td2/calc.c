#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "composition.h"

int main(int argc, char *argv[])
{
  if (argc < 4){
    printf ("Usage :  calc number_1 operator number_2 operator .. number_n\n");
    printf ("         where operator is \(+, -, *, \\)\n");
    exit(EXIT_FAILURE);
  }

  int numberOfExpressions = (argc-1)/2;

  Composition composition;
  Composition_Alloc(& composition, numberOfExpressions);

  double number1 = strtod(argv[1], NULL);
  double number2 = strtod(argv[3], NULL);
  Operator oper = Operator_CharTo(argv[2]);

  Composition_StoreFirstExpression(& composition, number1, number2, oper);

  for (int i=2; i<=numberOfExpressions; i++){
    number2 = strtod(argv[i*2+1], NULL);
    oper = Operator_CharTo(argv[i*2]);
    Composition_StoreExpression(& composition, number2, oper);
  }

  Composition_Print(composition);
  Composition_Destroy(& composition);
  exit(EXIT_SUCCESS);
}



