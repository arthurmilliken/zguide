#include<stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;;
  printf("Total number of command Line Arguments = %d \n",argc);
  for(i = 0; i < argc; i++)
  {
    printf("Argument index = %d , Argument = %s\n",i, argv[i]);
  }
  return 0;
}
