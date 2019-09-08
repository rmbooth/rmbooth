// ***
// *** You MUST modify this file.
// ***

#include <stdio.h>
#include <stdbool.h>

#ifdef TEST_ADDFILE
bool addFile(char * filename, int * sum)
{
  *sum = 0;
  int var = 0;
  int fun = 0;

  FILE * ftpr = fopen(filename, "r");
  if (ftpr == NULL)
  {
    return false;
  }
  var = fscanf(ftpr,"%d",&fun);
  while (var != EOF)
  {
    *sum = fun + *sum;
    var = fscanf(ftpr,"%d",&fun);
  }



  fclose(ftpr);
  return true;
}
#endif


#ifdef TEST_WRITESUM
bool writeSum(char * filename, int sum)
{
  FILE * ftpr = fopen(filename, "w");
  if (ftpr == NULL)
  {
    return false;
  }
 fprintf(ftpr,"%d\n",sum);
 fclose(ftpr);

  return true;
}
#endif
