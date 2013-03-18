#include <stdio.h>
#include <stdlib.h>
#include "code_to_html.h"

static char * str[] = 
{
  "使用方式: code_to_html source-file-path html-file-path"
};

int main(int argc, char *argv[])
{ 
  if(argc != 3)
  {
     fprintf(stderr, "%s\n", str[0]);
     system("pause");
     return 1;
  } 
  else
  {
      code_to_html(argv[1], argv[2]);
  }
  system("PAUSE");
  return 0;
}
