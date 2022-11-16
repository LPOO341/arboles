#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode *left;
  struct BinaryTreeNode *right;
};

struct Queue{
  struct BinaryTreeNode *node;
  struct Queue *next;
};

struct Stack{
  struct BinaryTreeNode *node;
  struct Stack *next;
};

typedef struct BinaryTreeNode TreeNode; // synonym for struct treeNode
typedef TreeNode *TreeNodePtr; // synonym for TreeNode *

//prototypes
void insertNode(TreeNodePtr *treePtr, int value);
void inOrder(TreeNodePtr treePtr);
void preOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);
void PreOrderNonRecursive(TreeNodePtr treePtr);
void InOrderNonRecursive(TreeNodePtr treePtr);
void PostOrderNonRecursive(TreeNodePtr treePtr);
void LevelOrder(TreeNodePtr treePtr);
struct Stack *CreateStack();
void Push(struct Stack *S, TreeNodePtr node);
TreeNodePtr Pop(struct Stack *S);
TreeNodePtr Top(struct Stack *S);
int IsEmptyStack(struct Stack *stack);
void DeleteStack(struct Stack *S);
struct Queue *CreateQueue();
void Enqueue(struct Queue *Q, TreeNodePtr node);
TreeNodePtr Dequeue(struct Queue *Q);
int IsEmptyQueue(struct Queue *Q);
void DeleteQueue(struct Queue *Q);




int main()
{
  TreeNodePtr rootPtr = NULL; // tree initially empty
  srand(time(NULL));
  puts("The numbers being placed in the tree are:");// insert random values between 0 and 14 in the tree
  for(int i = 1; i<=10;++ i){
    int item = rand() % 15;
    printf("%3d", item);
    insertNode(&rootPtr, item);   
  }
  // traverse the tree preOrder
  puts("\n\nThe preOrder traversal recursive is:");
  preOrder(rootPtr);
  puts("\n\nThe preOrder traversal no recursive is:");
  PreOrderNonRecursive(rootPtr);
  // traverse the tree inOrder
  puts("\n\nThe inOrder traversal recursive is:");
  inOrder(rootPtr);
  puts("\n\nThe inOrder traversal no recursive is:");
  InOrderNonRecursive(rootPtr);
  // traverse the tree postOrder
  puts("\n\nThe postOrder traversal recursive is:");
  postOrder(rootPtr);
  puts("\n\nThe postOrder traversal no recursive is:");
  PostOrderNonRecursive(rootPtr);
  // traverse the tree levelOrder
  puts("\n\nThe levelOrder traversal is:");
  LevelOrder(rootPtr);
  return 0;
}

// insert node into tree
void insertNode(TreeNodePtr *treePtr, int value) {
  if(*treePtr == NULL) { // if tree is empty
    *treePtr = malloc(sizeof(TreeNode));
    if (*treePtr != NULL) { // if memory was allocated, then assign data 
      (*treePtr)->data = value;
      (*treePtr)->left = NULL;
      (*treePtr)->right = NULL;
    }
    else {
      printf("%d not inserted. No memory available.\n", value);
    }
  }
  else { // tree is not empty
    if(value < (*treePtr)->data) { // value goes in left subtree
      insertNode(&((*treePtr)->left), value);
    }
    else if(value > (*treePtr)->data){
      insertNode(&((*treePtr)->right), value);
    }
    else { // duplicate data value ignored
      printf("%s","dup");
    }
  }
}

void preOrder(TreeNodePtr treePtr) {
  if(treePtr != NULL) {
    printf("%3d", treePtr->data);
    preOrder(treePtr->left);
    preOrder(treePtr->right);
  }
}

void inOrder(TreeNodePtr treePtr) {
  if(treePtr != NULL) {
    inOrder(treePtr->left);
    printf("%3d", treePtr->data);
    inOrder(treePtr->right);
  }
}

void postOrder(TreeNodePtr treePtr) {
  if(treePtr != NULL) {
    postOrder(treePtr->left);
    postOrder(treePtr->right);
    printf("%3d", treePtr->data);
  }
}

void PreOrderNonRecursive(TreeNodePtr treePtr){
  struct Stack *S = CreateStack();
  while(1){
    while(treePtr){
      printf("%3d", treePtr->data);
      Push(S, treePtr);
      treePtr = treePtr->left;
    }
    if(IsEmptyStack(S))
      break;
    treePtr = Pop(S);
    treePtr = treePtr->right;
  }  
  DeleteStack(S);
}

void InOrderNonRecursive(TreeNodePtr treePtr){
  struct Stack *S = CreateStack();
  while(1){
    while(treePtr){
      Push(S, treePtr);
      treePtr = treePtr->left;
    }
    if(IsEmptyStack(S))
      break;
    treePtr = Pop(S);
    printf("%3d", treePtr->data);
    treePtr = treePtr->right;
  }  
  DeleteStack(S);
}

void PostOrderNonRecursive(TreeNodePtr treePtr){
  struct Stack *S = CreateStack();
  TreeNodePtr lastVisited = NULL;
  while(1){
    while(treePtr){
      Push(S, treePtr);
      treePtr = treePtr->left;
    }
    if(IsEmptyStack(S))
      break;
    treePtr = Top(S);
    if(treePtr->right == NULL || treePtr->right == lastVisited){
      printf("%3d", treePtr->data);
      Pop(S);
      lastVisited = treePtr;
      treePtr = NULL;
    }
    else{
      treePtr = treePtr->right;
    }
  }  
  DeleteStack(S);
}

void LevelOrder(TreeNodePtr treePtr){
  struct Queue *Q = CreateQueue();
  if(treePtr == NULL)
    return;
  Enqueue(Q, treePtr);
  while(!IsEmptyQueue(Q)){
    treePtr = Dequeue(Q);
    printf("%3d", treePtr->data);
    if(treePtr->left)
      Enqueue(Q, treePtr->left);
    if(treePtr->right)
      Enqueue(Q, treePtr->right);
  }
  DeleteQueue(Q);
}

struct Stack *CreateStack(){
  struct Stack *S = (struct Stack *)malloc(sizeof(struct Stack));
  S->next = NULL;
  return S;
}

void Push(struct Stack *S, TreeNodePtr node){
  struct Stack *temp = (struct Stack *)malloc(sizeof(struct Stack));
  temp->node = node;
  temp->next = S->next;
  S->next = temp;
}

TreeNodePtr Pop(struct Stack *S){
  struct Stack *temp = S->next;
  TreeNodePtr node = temp->node;
  S->next = temp->next;
  free(temp);
  return node;
}

TreeNodePtr Top(struct Stack *S){
  return S->next->node;
}

int IsEmptyStack(struct Stack *S){
  return S->next == NULL;
}

void DeleteStack(struct Stack *S){
  struct Stack *temp;
  while(S){
    temp = S;
    S = S->next;
    free(temp);
  }
}

struct Queue *CreateQueue(){
  struct Queue *temp = (struct Queue *)malloc(sizeof(struct Queue));
  temp->node = NULL;
  temp->next = NULL;
  return temp;
}

void Enqueue(struct Queue *Q, TreeNodePtr node){
  struct Queue *temp = (struct Queue *)malloc(sizeof(struct Queue));
  temp->node = node;
  temp->next = NULL;
  while(Q->next)
    Q = Q->next;
  Q->next = temp;
}

TreeNodePtr Dequeue(struct Queue *Q){
  struct Queue *temp = Q->next;
  TreeNodePtr node = temp->node;
  Q->next = temp->next;
  free(temp);
  return node;
}

int IsEmptyQueue(struct Queue *Q){
  return Q->next == NULL;
}

void DeleteQueue(struct Queue *Q){
  struct Queue *temp;
  while(Q){
    temp = Q;
    Q = Q->next;
    free(temp);
  }
}

