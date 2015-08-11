#include "square.h"
#include "control.h"
#include "assert.h"
namespace item{
pos::pos(int x,int y)
{
    this->x=x;
    this->y=x;
}

square::square(int x, int y, int size,view::Show *draw,int level)
{
    this->x = x;
    this->y = y;
    this->size = size;
    this->draw = draw;
    draw->move(x, y,0);
    isBump=true;
    this->level=level;
    squareSet.insert(this);
}

std::set<square*> square::squareSet;

posSet *square::getRange()
{
    posSet &pos_set=*new posSet();
    if(isBump)
    {
        for (int i = 0; i < size; i++)
        {
            pos_set.push_back(pos(x + i, y));
            pos_set.push_back(pos(x + i, y + size - 1));
        }
        for (int i = 0; i < size; i++)
        {
            pos_set.push_back(pos(x, y + i));
            pos_set.push_back(pos(x + size - 1, y + i));
        }
    }
    return &pos_set;
}
void square::rePaint(){
    for(square *a:squareSet){
        a->draw->Repaint();
    }
}

void square::deleteAll(){
    for(square *a:squareSet){
        delete a;
    }
    squareSet.clear();
}

void square::reShow()
{
    draw->move(x, y,0);
}
square::~square()
{
    squareSet.erase(this);
    if(draw) delete draw;
}
moveSquare::moveSquare(int x, int y, int size,view::Show *draw, direct drt, int speed,int level) :square(x,y,size,draw,level)
{
    this->drt = drt;
    this->speed = speed;
    this->control = 0;
    draw->move(-1,-1,MOVESETDIRECT|drt);
}
void moveSquare::move(direct drt,int size)
{
    switch (drt){
    case left:
        x-=size;
    case right:
        x+=size;
    case up:
        y-=size;
    case down:
        y+=size;
    default:
        assert(1);
    }
}
void moveSquare::reShow()
{
    square::reShow();
    draw->move(-1,-1,MOVESETDIRECT|drt);
}
moveSquare::~moveSquare()
{
    if(control) delete control;
}
}
