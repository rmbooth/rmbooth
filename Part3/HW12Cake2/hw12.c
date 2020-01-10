// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hw12.h"

// DO NOT MODIFY this function --->>>
void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL)
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}
// <<<--- until here

// You MUST modify the following functions

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
ListNode * createList(int valn)
{
  ListNode * head = malloc(sizeof(ListNode));
  ListNode * currNode = head;
  //currNode ->next =NULL;
  int count = 0;
  currNode -> value = count;
  count++;
  while (count < valn)
  {
    currNode -> next = malloc(sizeof(ListNode));
    currNode = currNode -> next;
    currNode -> value = count;
    count++;
    currNode->next = NULL;

  }
  return head;
}
#endif

#ifdef TEST_ELIMINATE
// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk)
{
  ListNode * currNode = head;
  while (head != NULL)
  {
    for (int i = 1; i < valk; i++)
    {
      if (currNode -> next == NULL)
      {
        currNode = head;
      }
      else
      {
        currNode = currNode -> next;
      }
    }
    #ifdef DEBUG
      // this #ifdef ... #endif should be inside the condition *BEFORE* a
      // node' value is printed and it is deleted
      if ((head!= NULL) && (head->next != NULL))
      {
        ListNode * todelete = currNode;
        printListNode (todelete);
      }
    #endif
    printf("%d\n",currNode->value);
    ListNode * temp = head;
    if (currNode->next!=NULL)
    {
      temp = currNode -> next;
    }
    head = deleteNode(head,currNode);
    if(head == NULL)
    {
      currNode = NULL;
    }
    else
    {
      currNode = temp;
    }
  }
}
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns
//    NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete)
{
  if(head == NULL) //if head is null
  {
    return NULL;
  }
  if(todelete == NULL) //if todelete is null
  {
    return head;
  }

  if (head->value == todelete -> value)
  {
    if(head->next != NULL)
    {
      ListNode * temp = head -> next;
      free (head);
      head = temp;
      return head;
    }
    else
    {
      free(head);
      return NULL;
    }
  }

  if(head->next != NULL) //if the head next is null
  {
    ListNode * currNode = head;
    while(currNode->next->value != todelete->value)
    {
      if(currNode->next->next == NULL) //checking the next next term for NULL
      {
        return head; //return the head value
      }
      currNode = currNode -> next;
    }
    if(currNode->next->next==NULL) //checking the next next currNode for NULL
    {
      free(currNode->next);
      currNode -> next = NULL;
      return head;
    }
    ListNode * temp = currNode->next->next;
    free(currNode->next);
    currNode-> next = temp;
    return head;
  }
  else
  {
    if (head-> value == todelete->value) //if head value is equal to todelete value
    {
      free(head);
      head = NULL;
      return NULL;
    }
    return head;
  }
}
#endif


