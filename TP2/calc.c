#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "composition.h"




int main(int argc, char *argv[]) {
  if (argc < 4){
    printf ("Usage :  calc number_1 operator number_2 operator .. number_n\n");
    printf ("         where operator is \(+, -, *, \\)\n");
    exit(EXIT_FAILURE);
  } else if (argc%2 == 1) {
    printf ("ERNO2: Syntax Error.\n");
    exit(EXIT_FAILURE);
  }
  // * Getting the composition
  Composition c;
  Composition_InitEmpty(& c);
  Composition_Alloc(&c, 1 + (argc - 4)/2); // ? Source : tkt
  char * trash_bin;
  Composition_StoreFirstExpression(&c, strtod(argv[1], &trash_bin),strtod(argv[3], &trash_bin),Operator_CharTo(argv[2]));
  for (int i = 4; i < argc; i += 2) {
    Composition_StoreExpression(&c, strtod(argv[i + 1], &trash_bin),Operator_CharTo(argv[i]));
  }

  // * Computing & displaying expressions results
  for (int i = 0; i < c.capacity; i++) {
    Expression_Print(c.expressions[i]);
  }
  Composition_Destroy(&c);
}



