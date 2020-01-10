// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#ifdef TEST_READLIST
// read line by line from the input file
// each line shorter than WORDLENGTH (including '\n' and '\0')
// arithlist should have memory to store head and tail
// If arithlist is NULL, return false
// If fopen fails, return false
// If a line is too long,
//    free memory of the list
//    fclose
//    return false
// If everything is fine
//    fclose
//    arithlist points to the head and tail of the list
//    return true
bool readList(char * filename, List * arithlist)
{
  if(arithlist == NULL)
  {
    return false;
  }
  FILE * fptr = fopen(filename,"r");
  if(fptr == NULL)
  {
    return false;
  }
  char newArr [WORDLENGTH];
  for(int a = 0;a< WORDLENGTH;a++)
  {
    newArr[a] = '\0';
  }
  int character = fgetc(fptr);
  while(character != EOF)
  {
    int counter = 0;
    while((character != '\n')&&(counter < WORDLENGTH - 1))
    {
      newArr[counter] = character;
      counter++;
      character = fgetc(fptr);
    }
    if(character != '\n')
    {
      deleteList(arithlist);
      fclose(fptr);
      return false;
    }
    newArr[counter] = character;
    addNode(arithlist,newArr);
    character = fgetc(fptr);
    for(int a = 0;a< WORDLENGTH;a++)
    {
      newArr[a] = '\0';
    }
  }
  fclose(fptr);
  return true;
}
#endif

#ifdef TEST_DELETELIST
// If arithlist is NULL, do nothing
// release the memory of every node in the list
// release the memory of the list
void deleteList(List * arithlist)
{
  if(arithlist == NULL)
  {
    return;
  }
  while(arithlist->head != NULL) //frees the head and redefines head down the list
  {
    ListNode * tempNode = arithlist->head;
    arithlist->head = arithlist->head->next; //might cause a problem with NULL being last term
    free(tempNode);
  }

  arithlist->head = NULL;
  arithlist->tail=NULL;
  free(arithlist);
  arithlist=NULL;
}
#endif

#ifdef TEST_ADDNODE
// Input:
// arithlist stores the addresses of head and tail
// If arithlist is NULL, do nothing
// word is the word to be added
//
// Output:
// a ListNode is added to the end (become tail)
//
// allocate memory for a new ListNode
// copy word to the word attribute of the new ListNode
// insert the ListNode to the list
void addNode(List * arithlist, char * word)
{
  if(arithlist == NULL)
  {
    return;
  }
  if((arithlist->head==NULL)||(arithlist->tail==NULL))
  {
    ListNode * currNode = malloc(sizeof(ListNode));
    arithlist->head=currNode;
    arithlist->tail=currNode;
    currNode->prev=NULL;
    currNode->next=NULL;
    memcpy(currNode->word, word, sizeof(char)*WORDLENGTH);
  }
  else
  {
    ListNode * currNode = arithlist->tail;
    ListNode * newNode = malloc(sizeof(ListNode));
    currNode->next=newNode;
    newNode->prev=currNode;
    newNode->next=NULL;
    arithlist->tail = newNode;
    memcpy(newNode->word, word, sizeof(char)*WORDLENGTH);
  }

}
#endif

#ifdef TEST_DELETENODE
//  Input:
// arithlist stores the addresses of head and tail
// If arithlist is NULL, return false
// If the list is empty (head and tail are NULL), return false
// ln is the node to be deleted
// If ln is not in the list, return false
//
// Output:
// arithlist stores the addresses of head and tail
//   after ln is deleted
// return true.
//
// Be careful about delete the first or the last node
bool deleteNode(List * arithlist, ListNode * ln)
{
  if (arithlist == NULL)
  {
    return false;
  }
  if ((arithlist->head == NULL)||(arithlist->tail == NULL))
  {
    return false;
  }
  ListNode * currNode = arithlist -> head;
  while ((currNode->next != NULL)&&(currNode != ln))
  {
    currNode = currNode ->next;
  }
  if (currNode == ln) //if the node to delete is present in the list
  {
    if(currNode == arithlist-> head) //if the first is to be deleted
    {
      if(arithlist->head == arithlist->tail) //if there is one element
      {
        free(currNode);
        arithlist->head = NULL;
        arithlist->tail = NULL;
        //free(arithlist);
        return true;
      }
      arithlist -> head = arithlist ->head-> next; //redefining head
      free(currNode);
      currNode = arithlist->head;
      currNode->prev = NULL;
      return true;
    }
    if(currNode == arithlist-> tail) //if the last is to be deleted
    {
      arithlist -> tail = arithlist ->tail-> prev; //redefining head
      free(currNode);
      currNode = arithlist->tail;
      currNode->next = NULL;
      return true;
    }
    else
    {
      currNode->prev->next = currNode->next;  //redefining pointers for List
      currNode->next->prev = currNode->prev;

      free(currNode); //deleting node
      currNode = NULL;
      return true;
    }
    return true;
  }
  else
  {
    return false;
  }
  return false;
}
#endif
