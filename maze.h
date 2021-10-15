#ifndef __NODE__H
#define __NODE__H

//Structure Definition
typedef struct Node
{
  int item;
  char d;
  struct Node *up;
  struct Node *down;
  struct Node *left;
  struct Node *right;
} Node;

//Function Prototypes
struct Node * joinRows(struct Node * , struct Node * );
struct Node * createRow(int , int , int );
struct Node * create(int , int );
void printmaze(int , int , struct Node * , int);
void block(int, int, struct Node** );
void solve(int, int, struct Node *);

#endif