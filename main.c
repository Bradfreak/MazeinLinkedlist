#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <graphics.h>
#include "maze.h"

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