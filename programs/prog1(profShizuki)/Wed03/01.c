#include <stdio.h>

void main(){
  int year;

  printf("年（西暦）を入力してください: ");
  scanf("%d", &year);

  if(year % 4 == 0 && !(year % 100 == 0)){
    printf("%dはうるう年です\n", year);
  }
  else if(year % 400 == 0){
    printf("%dはうるう年です\n", year);
  }
  else{
    printf("%dはうるう年ではないです\n", year);
  }



}
