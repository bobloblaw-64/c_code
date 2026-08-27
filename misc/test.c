#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(void)

{

char line[]="hello";
printf("%zu\n", strlen(line));

line[0] = line[strlen(line)];
printf("%zu\n", strlen(line));

return 0;
}