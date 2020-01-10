// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}

static void preOrderNode(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    {
      return;
    }
  fprintf(fptr, "%d\n", tn -> value);
  preOrderNode(tn -> left, fptr);
  preOrderNode(tn -> right, fptr);
}

void preOrder(Tree * tr, char * filename)
{
  if (tr == NULL)
    {
      return;
    }
  FILE * fptr = fopen(filename, "w");
  preOrderNode(tr -> root, fptr);
  fclose (fptr);
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***

#ifdef TEST_BUILDTREE
// Consider the algorithm posted on
// https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/

Tree * buildTree(int * inArray, int * postArray, int size)
{
   if (size == 0)
   {
     return NULL;
   }
   if (inArray == NULL)
   {
     return NULL;
   }
   if (postArray == NULL)
   {
     return NULL;
   }

   Tree * head = malloc (sizeof(Tree));
   if (head == NULL)
   {
     return NULL;
   }
   head->root = NULL;

   TreeNode * treeArr = malloc(sizeof(TreeNode));
   if (treeArr == NULL)
   {
     return NULL;
   }
   int newSize;
   head -> root = treeArr;
   treeArr -> value  = postArray[size - 1];
   treeArr -> left = NULL;
   treeArr -> right = NULL;

   if (size == 1)
   {
     return head;
   }
   for(int i = 0; i < size; i++)
   {
     if (inArray[i] == treeArr -> value)
     {
       newSize = i;
     }
   }

   int * newPostArry = malloc(sizeof(int)*newSize);
   int countLeft = 0;
   for (int i = 0; i < size; i++)
   {
     for (int a = 0; a < newSize;a++)
     {
       if (inArray[a] == postArray[i])
       {
         newPostArry[countLeft] = postArray[i];
         countLeft++;
       }
     }
   }
   Tree * left = buildTree(inArray,newPostArry,newSize);

   if (left == NULL)
   {
     head->root -> left = NULL;
   }
   else
   {
     head -> root ->left= left->root;
     free(left);
   }
   free(newPostArry);

   int * newRightPostArry = malloc(sizeof(int)*(size-newSize-1));
   int countRight = 0;
   for (int i = 0; i < size; i++)
   {
     for (int a = newSize+1; a < size;a++)
     {
       if (inArray[a] == postArray[i])
       {
         newRightPostArry[countRight] = postArray[i];
         countRight++;
       }
     }
   }
   Tree * right = buildTree(inArray + newSize + 1,newRightPostArry, size - newSize-1);
   if (right == NULL)
   {
     head->root -> right = NULL;
   }
   else
   {
     head -> root ->right= right->root;
     free(right);
   }
   free(newRightPostArry);

   return head;


}
#endif
