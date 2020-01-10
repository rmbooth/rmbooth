// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculate.h"

// DO NOT MODIFY FROM HERE --->>>
const int Operations[] = {'+', '-', '*'};

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
      char *loc = strchr(word,Operations[ind]);
      if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the calculate function
// ***
#ifdef TEST_CALCULATE
// if arithlist is NULL, return true
// if arithlist -> head is NULL, return true
// if the input list is invalid, return false
bool calculate(List * arithlist)
{
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist -> head) == NULL)
    {
      return true;
    }
  // go through the list until there is only node in the list
  // find the next operator
  // If no operator can be found, return false
  // If an operator is found, find the two previous nodes as operands
  // If cannot find previous two operands, return false
  // If two operands can be found, perform the arithmetic operation
  // Be careful, subtraction is no commutative: 4 2 - means 4 - 2,
  //    not 2 - 4
  // After the operation,
  //     put the result back to the list
  //     remove the two nodes used to store the two operands
  // After going through the entire list and performing the operations,
  //     the list should have exactly one node left. If this is not
  //     true, return false
  // If the input is valud, return true
  ListNode * currNode = arithlist->head;
  int numbers = 0;
  int operators = 0;
  while(currNode!=NULL)
  {
    if (isOperator(currNode->word) == -1)
    {
      numbers++;
    }
    else
    {
      operators++;
    }
    currNode = currNode->next;
  }
  if ((operators == 0)&&(numbers ==1))
  {
    return true;
  }
  if ((operators < 1)&&(numbers < 2))
  {
    return false;
  }
  if (numbers - operators != 1)
  {
    return false;
  }
  currNode = arithlist->head;
  List * stack = malloc(sizeof(List));
  stack->head = NULL;
  stack->tail = NULL;

  while((stack->head != stack -> tail)||(stack->head == NULL))
  {
    while(isOperator(currNode->word) == -1 )
    {
      addNode(stack,currNode->word);
      currNode = currNode->next;
    }
    char *trash;
    int tail = strtol(stack->tail->word,&trash,10);
    int tailPrev = strtol(stack->tail->prev->word,&trash,10);
    int var;
    if(isOperator(currNode->word) == 0)
    {
      var = tailPrev + tail;
    }
    if(isOperator(currNode->word) == 1)
    {
      var = tailPrev - tail;
    }
    if(isOperator(currNode->word) == 2)
    {
      var = tailPrev * tail;
    }
    deleteNode(stack,stack->tail);
    deleteNode(stack,stack->tail);
    char temp[WORDLENGTH];
    sprintf (temp,"%d\n",var); //convert value to string
    addNode(stack,temp);
    if(currNode->next!= NULL)
    {
      currNode = currNode->next;
    }
  }
  ListNode * p = arithlist->head;
  ListNode * q = arithlist->tail;

  arithlist->head = stack->head;
  arithlist->tail = stack->tail;

  stack->head = p;
  stack->tail=q;
  deleteList(stack);
  // if more than one node left, return false

  // if the remaining node is an operator, return false

  // if everything is OK, return true
  return true;
}
#endif
