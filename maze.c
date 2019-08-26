#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <unistd.h>

//Structure Defination
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

//Main starts here
int main()
{
  //Input about length and height taken
  int height, breadth;
  printf("Enter the length\n");
  scanf("%d", &height);
  printf("Enter the breadth\n");
  scanf("%d", &breadth);

  //Multidimension linked list is created through the below call
  struct Node* head = create(height, breadth);

  //Blocks(Walls) in the maze are put using the function call below
  block(height, breadth, &head);
  
  //The created maze is solved in the function
  solve(height, breadth, head);

  exit(0);
}

//The below function creates multidimension linked list
struct Node* create(int height, int breadth)
{
  int i, j;
  struct Node* mainhead;
  mainhead = (struct Node*)malloc(sizeof(struct Node));
  mainhead->left = NULL;
  mainhead->up = NULL;
  mainhead->item = 0;
  struct Node* trav = mainhead;
  for(j = 1; j < breadth; j++)
  {
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = trav;
    temp->item = 0;
    temp->down = NULL;
    trav->right = temp;
    trav = trav->right;
  }
  //topmost linked list is created

  struct Node* head1;
  struct Node* head2;
  //two linked list are taken with different heads
  head1 = mainhead;
  for(i = 1; i < height; i++)
  {
    head2 = createRow(breadth, i, height);
    head1 = joinRows(head1, head2);
  }
  //In the above for loop, a linked list is created and stored in head2. Head1 already has a linked list.
  //Now both the linked list are joined up and down thus creating a maze.The first row has up as NULL for all the
  //elements. First element of every elements has the left as NULL. Last element of every row has right as NULL.
  //Last row has down as NULL for all the elements.Finally the maze is created using multidimension linked list 
  //returned to main function.
  return mainhead;
}

//The below function creates a doubly linked list and returns the list to the call.
struct Node* createRow(int breadth, int i, int height)
{
  srand(time(NULL));
  int j;
  struct Node* head;
  head = (struct Node*)malloc(sizeof(struct Node));
  head->left = NULL;
  head->item = 0;
  if(i + 1 == height)
  {
    head->down = NULL;
    struct Node* trav = head;
    for(j = 1; j < breadth; j++)
    {
      struct Node* temp;
      temp = (struct Node*)malloc(sizeof(struct Node));
      temp->left = trav;
      temp->item = 0;
      temp->down = NULL;
      trav->right = temp;
      trav = trav->right;
    }
  }
  else
  {
    struct Node* trav = head;
    for(j = 1; j < breadth; j++)
    {
      struct Node* temp;
      temp = (struct Node*)malloc(sizeof(struct Node));
      temp->left = trav;
      temp->item = 0;
      trav->right = temp;
      trav = trav->right;
    }
  }
  return head;
}

//In the below function, two Doubly linked lists are join up and down.
struct Node* joinRows(struct Node *head1, struct Node *head2)
{
  struct Node* p1 = head1;
  struct Node* p2 = head2;
  while(p1 != NULL)
  {
    p1->down = p2;
    p2->up = p1;
    p1 = p1->right;
    p2 = p2->right;
  }
  return head2;
}

//In the below function, Maze is printed on the graphic window using initgraph.
void printmaze(int height, int breadth, struct Node *mainhead, int done)
{
  struct Node* head = mainhead;
  struct Node* trav = mainhead;
  int i, j;
  int left=10,top=30,right=25,bottom=45;

  for(i = 0; i < height; i++)
  {
    for(j = 0; j < breadth; j++)
    {
//this will print blue for open nodes.
      if(trav->item == 0)
      {
        setcolor(BLUE);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
//this will print green for visited nodes and first node.
      else if(trav->item == 2 || trav->item == 5)
      {
        setcolor(GREEN);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
//this will print light green for nodes visited and returned back.
      else if(trav->item == 3)
      {
        setcolor(LIGHTGREEN);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
//this will print cyan for destination node.
      else if(trav->item == 4)
      {
        setcolor(CYAN);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
//This will print black for current traversing node.
      else if(trav->item == 6)
      {
        setcolor(BLACK);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }
//this will print red for blocks.
      else
      {
        setcolor(RED);
        bar(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
        setcolor(WHITE);
        rectangle(left + (j * 15), top + (i * 15), right + (j * 15), bottom + (i * 15));
      }

      trav = trav->right;
    }
    printf("\n");
    head = head->down;
    trav = head;
  }

  if(done == 1)
  {
    outtextxy(left, 10, "PATH NOT FOUND");
    delay(8000);
  }
  else if(done == 2)
  {
    outtextxy(left, 10, "PATH FOUND");
    delay(8000);
  }
  else
  {
    outtextxy(left, 10, "PROCESSING..");
    delay(100);
  }

  cleardevice();
  return;
}

//The function below will block random node by using rand and srand functions in c
void block(int l, int b, struct Node** head)
{
  srand(time(NULL));
  int j, i;
  int blocks;
  printf("Enter the number of blocks\n");
  scanf("%d", &blocks);
  int len, bre;
  struct Node* h = *head;
  struct Node* trav = *head;

  for(i = 0; i < blocks; i++)
  {
    len = rand()%(l - 1);
    bre = rand()%(b - 1);
    for(j = 0; j < len; j++)
    {
      trav = trav->right;
    }

    for(j = 0; j < bre; j++)
    {
      trav = trav->down;
    }

    trav->item = 1;
    trav = h;
  }

  trav = h;
  h->item = 5;
  while(trav->right != NULL)
  {
    trav = trav->right;
  }
  while(trav->down != NULL)
  {
    trav = trav->down;
  }
  trav->item = 4;

  return ;
}

//This will solve the maze created and will print after each step taaken.
void solve(int h, int b, struct Node *head)
{
  int gd = DETECT,gm;
  initgraph(&gd,&gm,NULL);
  int r, l, u, d;
  struct Node* temp = head;
  int done = 0;

  while(done != 1)
  {
    printmaze(h, b, head, 0);


    if(temp->item == 5 &&(temp->down->item==3 || temp->down->item==1)&&(temp->right->item==3 || temp->right->item==1))
    {
      printmaze(h, b, head, 1);
      done = 1;
      closegraph();
      return;
    }
    if(temp->item == 4)
    {
      printmaze(h, b, head, 2);
      done = 1;
      closegraph();
      return;
    }

    if(temp->right != NULL)
    {
      r = temp->right->item;
      if(r == 0)
      {
        if(temp->item != 5)
        {
          temp->item = 2;
        }
        temp = temp->right;
        temp->item = 6;
        temp->d = 'r';
        continue;
      }
      if(r == 4)
      {
        temp->item = 2;
        temp = temp->right;
        temp->d = 'r';
        continue;
      }
      else if(r == 2)
      {
        if((temp->down==NULL || temp->down->item==1 || temp->down->item==2 || temp->down->item==3)&&(temp->left==NULL || temp->left->item==1 || temp->left->item==2 || temp->left->item==3)&&(temp->up == NULL || temp->up->item==1 || temp->up->item==2 || temp->up->item==3 || temp->up->item==5)&&(temp->d == 'l'))
        {
          temp->d = 'r';
          temp->item = 3;
          temp = temp->right;
          temp->item = 6;
          continue;
        }
      }
    }

    if(temp->down != NULL)
    {
      d = temp->down->item;
      if(d == 0)
      {
        if(temp->item != 5)
        {
          temp->item = 2;
        }
        temp = temp->down;
        temp->item = 6;
        temp->d = 'd';
        continue;
      }
      else if(d == 4)
      {
        temp->item = 2;
        temp = temp->down;
        temp->d = 'd';
        continue;
      }
      else if(d == 2)
      {
        if((temp->left==NULL || temp->left->item==1 || temp->left->item==2 || temp->left->item==3)&&(temp->up == NULL || temp->up->item==1 || temp->up->item==2 || temp->up->item==3 || temp->up->item==5)&&(temp->d == 'u'))
        {
          temp->d = 'd';
          temp->item = 3;
          temp = temp->down;
          temp->item = 6;
          continue;
        }
      }
    }

    if(temp->left != NULL)
    {
      l = temp->left->item;
      if(l == 0)
      {
        temp->item = 2;
        temp = temp->left;
        if(temp->item != 5)
        {
          temp->item = 6;
        }
        temp->d = 'l';
        continue;
      }
      else if(l == 5)
      {
        temp->item = 3;
        temp->d = 'l';
        temp = temp->left;
        continue;
      }
      else if(l == 2)
      {
        if((temp->up == NULL || temp->up->item==1 || temp->up->item==2 || temp->up->item==3)&&(temp->d == 'r'))
        {
          temp->d = 'l';
          temp->item = 3;
          temp = temp->left;
          temp->item = 6;
          continue;
        }
      }
    }

    if(temp->up != NULL)
    {
      u = temp->up->item;
      if(u == 0)
      {
        temp->item = 2;
        temp = temp->up;
        if(temp->item != 5)
        {
          temp->item = 6;
        }
        temp->d = 'u';
        continue;
      }
      else if(u == 5 && temp->d == 'd')
      {
        temp->item = 3;
        temp->d = 'u';
        temp = temp->up;
        continue;
      }
      else if(u == 2 && temp->d == 'd')
      {
        temp->d = 'u';
        temp->item = 3;
        temp = temp->up;
        temp->item = 6;
        continue;
      }
    }
  }
}
