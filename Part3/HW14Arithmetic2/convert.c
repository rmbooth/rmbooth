// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "convert.h"

// DO NOT MODIFY FROM HERE --->>>
const int Operations[] = {'+', '-', '*', '(', ')'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
// return 1 if the word contains '-'
// ...
int isOperator(char * word)
{
  int ind;
  int numop = sizeof(Operations) / sizeof(int);
  for (ind = 0; ind < numop; ind ++)
    {
    char *loc = strchr(word, Operations[ind]);
    if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the convert function
// ***
#ifdef TEST_CONVERT
bool convert(List * arithlist)
{
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist -> head) == NULL)
    {
      return true;
    }

  ListNode * currNode = arithlist->head;
  int numbers = 0;
  int operators = 0;
  int left = 0;
  int right = 0;
  while(currNode!=NULL) //checks for operator and operand errors
  {
    if (isOperator(currNode->word) == -1)
    {
      numbers++;
    }
    else if ((isOperator(currNode->word) == 0) || (isOperator(currNode->word) == 1) || (isOperator(currNode->word) == 2))
    {
      operators++;
    }
    else if((isOperator(currNode->word) == 3))
    {
      left++;
    }
    else if((isOperator(currNode->word) == 4))
    {
      right++;
    }
    currNode = currNode->next;
  }
  if (numbers - operators != 1)
  {
    return false;
  }
  if (left != right) //parethesis checker
  {
    return false;
  }
currNode = arithlist->head;
while(currNode != NULL) //checks for left and right parethesis errors
{
  if (isOperator(currNode->word) == 3)
  {
    if((currNode ->next == NULL) || (isOperator(currNode->next->word) != -1))
    {
      return false;
    }
  }
  if (isOperator(currNode->word) == 4)
  {
    if((currNode ->prev == NULL) || (isOperator(currNode->prev->word) != -1))
    {
      return false;
    }
  }
  currNode = currNode ->next;
}



List * operator = malloc(sizeof(List));
List * output = malloc (sizeof(List));
if(operator == NULL)
{
  return false;
}
if (output == NULL)
{
  return false;
}
output->head = NULL;
output->tail = NULL;
operator->head = NULL;
operator->tail = NULL;
currNode = arithlist->head;

while (currNode != NULL)
{
  int var = isOperator(currNode->word);
  switch (var)
  {
    case -1: //letter
      addNode(output, currNode->word);
      break;
    case 0: //+
      if (operator->tail == NULL)
      {
        addNode(operator, currNode->word);
        break;
      }
      if (var + 1 >= isOperator(operator ->tail->word))
      {
        addNode(output,operator->tail->word);
        deleteNode(operator,operator->tail);
        addNode(operator, currNode->word);
        break;
      }
      else if (var + 2 == isOperator(operator ->tail->word))
      {
        while((operator ->tail != NULL) && (isOperator(operator->tail->word) != 3))
        {
          addNode(output,operator->tail->word);
          deleteNode(operator,operator->tail);
        }
        addNode(operator, currNode->word);
        break;
      }
      else
      {
        addNode(operator, currNode->word);
        break;
      }
      break;
    case 1: //-
      if (operator->tail == NULL)
      {
        addNode(operator, currNode->word);
        break;
      }
      if (var >= isOperator(operator ->tail->word))
      {
        addNode(output,operator->tail->word);
        deleteNode(operator,operator->tail);
        addNode(operator, currNode->word);
        break;
      }
      else if (var + 1 == isOperator(operator ->tail->word))
      {
        while((isOperator(operator ->tail->word) != 3) && (operator ->tail != NULL))
        {
          addNode(output,operator->tail->word);
          deleteNode(operator,operator->tail);
        }
        addNode(operator, currNode->word);
        break;
      }
      else
      {
        addNode(operator, currNode->word);
        break;
      }
        break;
    case 2: //*
      if (operator->tail == NULL)
      {
        addNode(operator, currNode->word);
        break;
      }
      if (var == isOperator(operator ->tail->word))
      {
        addNode(output,operator->tail->word);
        deleteNode(operator,operator->tail);
        addNode(operator, currNode->word);
        break;
      }
      else
      {
        addNode(operator, currNode->word);
        break;
      }
      break;
    case 3: //(
      addNode(operator, currNode->word);
      break;
    case 4: //)
      while(isOperator(operator ->tail->word) != 3)
      {
        addNode(output,operator->tail->word);
        deleteNode(operator,operator->tail);
      }
      deleteNode(operator,operator->tail);
      break;
  }
  currNode = currNode ->next;
}
while((operator->tail) != NULL)
{
  addNode(output,operator->tail->word);
  deleteNode(operator,operator->tail);
}

ListNode * p = arithlist->head;
ListNode * q = arithlist->tail;

arithlist->head = output->head;
arithlist->tail = output->tail;

output->head = p;
output->tail=q;
deleteList(operator);
deleteList(output);

  return true;
}
#endif
