#include <stdio.h>

int main(){

  int n = 5;
  
  for (int i=5; i>=0; i--){

    for (int j=1; j<=i; j++)
      printf("%d", j);

    putchar('\n');
  }

  return 0;
}
