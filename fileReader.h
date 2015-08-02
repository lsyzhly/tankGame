#include <stdio.h>
#include "all.h"
//read map
void readFile(char *path);
//new a couple of unmoveSuqare and return
char *newMuchSquare(int x,int y,int size,unmoveType type,int state);
//add the Suqare to the MainControl
void addSqares(char *a,bool isTop=false);
void ChooseLevel(int level);
